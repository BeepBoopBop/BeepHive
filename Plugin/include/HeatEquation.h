#ifndef HEATEQUATION_H
#define HEATEQUATION_H 

#include "BeepHive.h"
#include "BoundaryValues.h"
#include "Dealii.h"
#include "EnvObject.h"
#include "InitialValues.h"
#include "RightHandSide.h"

/*! 
 *
 *
 */

template<int dim>
class HeatEquation
{

public:
  HeatEquation<dim>();
  virtual ~HeatEquation<dim>();
  void run();
  void addSource( EnvObject *newSource );

  double getValue( double x, double y );

private:
  
  double time;
  double time_step;
  unsigned int timestep_number;
  const double theta;
  unsigned int initial_global_refinement;
  unsigned int n_adaptive_pre_refinement_steps;
  unsigned int pre_refinement_step;
  bool initialized;
  bool start_time_iteration;

  void setup_system();
  void solve_time_step();
  void output_results() const;
  void refine_mesh (const unsigned int min_grid_level,
  const unsigned int max_grid_level);

  dealii::Triangulation<dim> triangulation;
  dealii::FE_Q<dim> fe;
  dealii::DoFHandler<dim> dof_handler;
  dealii::ConstraintMatrix constraints;
  dealii::SparsityPattern sparsity_pattern;

  dealii::SparseMatrix<double> mass_matrix;
  dealii::SparseMatrix<double> laplace_matrix;
  dealii::SparseMatrix<double> system_matrix;

  dealii::Vector<double> solution;
  dealii::Vector<double> old_solution;
  dealii::Vector<double> system_rhs;
  dealii::Vector<double> tmp;
  dealii::Vector<double> forcing_terms;
  
  RightHandSide<dim> rhs_function;
  InitialValues<dim> init_function;

};

template<int dim>
HeatEquation<dim>::HeatEquation ():
fe(1),
dof_handler(triangulation),
time_step(1. / 100),
theta(0.5),
initialized(false),
start_time_iteration(false)
{}

template<int dim>
HeatEquation<dim>::~HeatEquation (){}

template<int dim>
void HeatEquation<dim>::setup_system()
{
  dof_handler.distribute_dofs(fe);

  std::cout << std::endl
            << "==========================================="
            << std::endl
            << "Number of active cells: " << triangulation.n_active_cells()
            << std::endl
            << "Number of degrees of freedom: " << dof_handler.n_dofs()
            << std::endl
            << std::endl;

  constraints.clear ();
  dealii::DoFTools::make_hanging_node_constraints (dof_handler,
                                           constraints);
  constraints.close();

  dealii::CompressedSparsityPattern c_sparsity(dof_handler.n_dofs());
  dealii::DoFTools::make_sparsity_pattern(dof_handler,
                                  c_sparsity,
                                  constraints,
                                  /*keep_constrained_dofs = */ true);
  sparsity_pattern.copy_from(c_sparsity);

  mass_matrix.reinit(sparsity_pattern);
  laplace_matrix.reinit(sparsity_pattern);
  system_matrix.reinit(sparsity_pattern);

  dealii::MatrixCreator::create_mass_matrix(dof_handler,
                                    dealii::QGauss<dim>(fe.degree+1),
                                    mass_matrix,
                                    (const dealii::Function<dim> *)0,
                                    constraints);
  dealii::MatrixCreator::create_laplace_matrix(dof_handler,
                                       dealii::QGauss<dim>(fe.degree+1),
                                       laplace_matrix,
                                       (const dealii::Function<dim> *)0,
                                       constraints);

  solution.reinit(dof_handler.n_dofs());
  old_solution.reinit(dof_handler.n_dofs());
  system_rhs.reinit(dof_handler.n_dofs());
}

template<int dim>
void HeatEquation<dim>::solve_time_step()
{
  dealii::SolverControl solver_control(1000, 1e-8 * system_rhs.l2_norm());
  dealii::SolverCG<> cg(solver_control);

  dealii::PreconditionSSOR<> preconditioner;
  preconditioner.initialize(system_matrix, 1.0);

  cg.solve(system_matrix, solution, system_rhs,
           preconditioner);

  constraints.distribute(solution);

  std::cout << "     " << solver_control.last_step()
            << " CG iterations." << std::endl;
}

template <int dim>
void HeatEquation<dim>::refine_mesh (const unsigned int min_grid_level,
                                     const unsigned int max_grid_level)
{
  dealii::Vector<float> estimated_error_per_cell (triangulation.n_active_cells());

  dealii::KellyErrorEstimator<dim>::estimate (dof_handler,
                                      dealii::QGauss<dim-1>(fe.degree+1),
                                      typename dealii::FunctionMap<dim>::type(),
                                      solution,
                                      estimated_error_per_cell);

  dealii::GridRefinement::refine_and_coarsen_fixed_fraction (triangulation,
                                                     estimated_error_per_cell,
                                                     0.6, 0.4);

  if (triangulation.n_levels() > max_grid_level)
    for (typename dealii::Triangulation<dim>::active_cell_iterator
         cell = triangulation.begin_active(max_grid_level);
         cell != triangulation.end(); ++cell)
      cell->clear_refine_flag ();
  for (typename dealii::Triangulation<dim>::active_cell_iterator
       cell = triangulation.begin_active(min_grid_level);
       cell != triangulation.end_active(min_grid_level); ++cell)
    cell->clear_coarsen_flag ();


  dealii::SolutionTransfer<dim> solution_trans(dof_handler);

  dealii::Vector<double> previous_solution;
  previous_solution = solution;
  triangulation.prepare_coarsening_and_refinement();
  solution_trans.prepare_for_coarsening_and_refinement(previous_solution);

  triangulation.execute_coarsening_and_refinement ();
  setup_system ();

  solution_trans.interpolate(previous_solution, solution);
}

template <int dim>
double HeatEquation<dim>::getValue( double x, double y )
{

  dealii::Point<2> p = dealii::Point<2>( x, y );

  return dealii::VectorTools::point_value (dof_handler,
                                           solution, p);
}

template<int dim>
void HeatEquation<dim>::run()
{
  if(!initialized){
    initial_global_refinement = 2;
    n_adaptive_pre_refinement_steps = 4;

    dealii::GridGenerator::hyper_cube (triangulation, 0, 1024);
    triangulation.refine_global (initial_global_refinement);

    setup_system();

    pre_refinement_step = 0;
 
    initialized = true; 
    start_time_iteration = true;
  }

  if( start_time_iteration ){

    tmp.reinit (solution.size());
    forcing_terms.reinit (solution.size());


    dealii::VectorTools::interpolate(dof_handler,
                             init_function,
                             old_solution);
    solution = old_solution;

    timestep_number = 0;
    time = 0;

    output_results();
    start_time_iteration = false;

  }
  // Then we start the main loop until the computed time exceeds our
  // end time of 0.5. The first task is to build the right hand
  // side of the linear system we need to solve in each time step.
  // Recall that it contains the term $MU^{n-1}-(1-\theta)k_n AU^{n-1}$.
  // We put these terms into the variable system_rhs, with the
  // help of a temporary vector:

    time += time_step;
    ++timestep_number;

    std::cout << "Time step " << timestep_number << " at t=" << time
              << std::endl;

    mass_matrix.vmult(system_rhs, old_solution);

    laplace_matrix.vmult(tmp, old_solution);
    system_rhs.add(-(1 - theta) * time_step, tmp);

    // The second piece is to compute the contributions of the source
    // terms. This corresponds to the term $k_n
    // \left[ (1-\theta)F^{n-1} + \theta F^n \right]$. The following
    // code calls VectorTools::create_right_hand_side to compute the
    // vectors $F$, where we set the time of the right hand side
    // (source) function before we evaluate it. The result of this
    // all ends up in the forcing_terms variable:

    rhs_function.set_time(time);
    dealii::VectorTools::create_right_hand_side(dof_handler,
                                        dealii::QGauss<dim>(fe.degree+1),
                                        rhs_function,
                                        tmp);
    forcing_terms = tmp;
    forcing_terms *= time_step * theta;

    rhs_function.set_time(time - time_step);

    dealii::VectorTools::create_right_hand_side(dof_handler,
                                        QGauss<dim>(fe.degree+1),
                                        rhs_function,
                                        tmp);

    forcing_terms.add(time_step * (1 - theta), tmp);

    // Next, we add the forcing terms to the ones that
    // come from the time stepping, and also build the matrix
    // $M+k_n\theta A$ that we have to invert in each time step.
    // The final piece of these operations is to eliminate
    // hanging node constrained degrees of freedom from the
    // linear system:
    system_rhs += forcing_terms;

    system_matrix.copy_from(mass_matrix);
    system_matrix.add(theta * time_step, laplace_matrix);

    constraints.condense (system_matrix, system_rhs);

    // There is one more operation we need to do before we
    // can solve it: boundary values. To this end, we create
    // a boundary value object, set the proper time to the one
    // of the current time step, and evaluate it as we have
    // done many times before. The result is used to also
    // set the correct boundary values in the linear system:
    {
      BoundaryValues<dim> boundary_values_function;
      boundary_values_function.set_time(time);

      std::map<types::global_dof_index, double> boundary_values;
      dealii::VectorTools::interpolate_boundary_values(dof_handler,
                                               0,
                                               boundary_values_function,
                                               boundary_values);

      dealii::MatrixTools::apply_boundary_values(boundary_values,
                                         system_matrix,
                                         solution,
                                         system_rhs);
    }

    // With this out of the way, all we have to do is solve the
    // system, generate graphical data, and...
    solve_time_step();


    // ...take care of mesh refinement. Here, what we want to do is
    // (i) refine the requested number of times at the very beginning
    // of the solution procedure, after which we jump to the top to
    // restart the time iteration, (ii) refine every fifth time
    // step after that.
    //
    // The time loop and, indeed, the main part of the program ends
    // with starting into the next time step by setting old_solution
    // to the solution we have just computed.
    if ((timestep_number == 1) &&
        (pre_refinement_step < n_adaptive_pre_refinement_steps))
      {
        refine_mesh (initial_global_refinement,
                     initial_global_refinement +  n_adaptive_pre_refinement_steps);
        ++pre_refinement_step;

        tmp.reinit (solution.size());
        forcing_terms.reinit (solution.size());

        std::cout << std::endl;

        start_time_iteration = true;
      }
    else if ((timestep_number > 0) && (timestep_number % 5 == 0))
      {
        refine_mesh (initial_global_refinement,
                     initial_global_refinement + n_adaptive_pre_refinement_steps);

        tmp.reinit (solution.size());
        forcing_terms.reinit (solution.size());
      }

    old_solution = solution;
 
}
template<int dim>
void HeatEquation<dim>::output_results() const
{
  DataOut<dim> data_out;

  data_out.attach_dof_handler(dof_handler);
  data_out.add_data_vector(solution, "U");

  data_out.build_patches();

  const std::string filename = "solution-"
                               + Utilities::int_to_string(timestep_number, 3) +
                               ".vtk";
  std::ofstream output(filename.c_str());
  data_out.write_vtk(output);
}

template<int dim>
void HeatEquation<dim>::addSource( EnvObject *newSource )
{
  rhs_function.addObject(newSource);
}

#endif
