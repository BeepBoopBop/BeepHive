#ifndef HEATEQUATION_H
#define HEATEQUATION_H 

#include "Dealii.h"
#include "BeepHive.h"
#include "BoundaryValues.h"
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
  void setup_system();
  void solve_time_step();
  void getValue( int x, int y, int z );

private:
  
  double time;
  double time_step;
  unsigned int timestep_number;
  const double theta;

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

  

};

template<int dim>
HeatEquation<dim>::HeatEquation ():
fe(1),
dof_handler(triangulation),
time_step(1. / 500),
theta(0.5)
{}

template<int dim>
HeatEquation<dim>::~HeatEquation (){}

/*! 
 *
 *
 */

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

/*! 
 *
 *
 */

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

/*! 
 *
 *
 */

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


    // As part of mesh refinement we need to transfer the solution vectors
    // from the old mesh to the new one. To this end we use the
    // SolutionTransfer class and we have to prepare the solution vectors that
    // should be transferred to the new grid (we will lose the old grid once
    // we have done the refinement so the transfer has to happen concurrently
    // with refinement). At the point where we call this function, we will
    // have just computed the solution, so we no longer need the old_solution
    // variable (it will be overwritten by the solution just after the mesh
    // may have been refined, i.e., at the end of the time step; see below).
    // In other words, we only need the one solution vector, and we copy it
    // to a temporary object where it is safe from being reset when we further
    // down below call <code>setup_system()</code>.
    //
    // Consequently, we initialize a SolutionTransfer object by attaching
    // it to the old DoF handler. We then prepare the triangulation and the
    // data vector for refinement (in this order).
    dealii::SolutionTransfer<dim> solution_trans(dof_handler);

    dealii::Vector<double> previous_solution;
    previous_solution = solution;
    triangulation.prepare_coarsening_and_refinement();
    solution_trans.prepare_for_coarsening_and_refinement(previous_solution);

    // Now everything is ready, so do the refinement and recreate the dof
    // structure on the new grid, and initialize the matrix structures and the
    // new vectors in the <code>setup_system</code> function. Next, we actually
    // perform the interpolation of the solution from old to new grid.
    triangulation.execute_coarsening_and_refinement ();
    setup_system ();

    solution_trans.interpolate(previous_solution, solution);
  }
#endif
