#ifndef HEATEQUATION_H
#define HEATEQUATION_H 

#include "Dealii.h"
#include "BeepHive.h"

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
#endif

template<int dim>
HeatEquation<dim>::HeatEquation ():
fe(1),
dof_handler(triangulation),
time_step(1. / 500),
theta(0.5)
{}

template<int dim>
HeatEquation<dim>::~HeatEquation (){}
