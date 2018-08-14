#include "firstexp.h"
#include "../MISC/parameters.h"

/* ---------------------------------------------------------------------------------------- */

FirstExp::FirstExp(Parameters* params, int argc, char** argv)
  : Experiment(params, argc, argv)
{
  init_local_variables(params);
}

/* ---------------------------------------------------------------------------------------- */

FirstExp::FirstExp(const FirstExp& other)
  : Experiment(other)
{
  copy(other);
}

/* ---------------------------------------------------------------------------------------- */

FirstExp::~FirstExp( )
{
  destroy();
}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::copy(const FirstExp& other)
{
  
}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::destroy()
{
  
}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::init_local_variables(Parameters *params)
{
  
  // Init Fitness Variables
  // Number of problem objectives
  if( m_evolution )
    {
#ifdef _MOEA_
      m_nbObjectives = 2;
#else
      m_nbObjectives = 1;
#endif
    }
  else if( m_reEvaluation ){
    //m_nbObjectives = ;
  }
  
  m_total_fitness.assign(m_nbObjectives, 0.0);
}

/* ---------------------------------------------------------------------------------------- */

int FirstExp::init_single_evaluation(void)
{
  
  return Experiment::init_single_evaluation();
}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::compute_fitness(void)
{

}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::finalise_single_evaluation (void)
{ 
  
}

/* ---------------------------------------------------------------------------------------- */

void FirstExp::finalise_evaluation_loop (void)
{
  //Compute m_total_fitness[0] relative to the group perfomace
  for(int eval =0; eval < m_maxEvaluation; eval++){
    m_total_fitness[0] += 0.0;
  }
  m_total_fitness[0] /= (double)(m_maxEvaluation);
}
 
/* ---------------------------------------------------------------------------------------- */

void FirstExp::finalise_evolutionary_run(void){}

/* ---------------------------------------------------------------------------------------- */

FirstExp& FirstExp::operator=(const FirstExp &other)
{
    Experiment::operator=(other);
    if(this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
