#ifndef FIRSTEXP_H
#define FIRSTEXP_H

#include "experiment.h"

class FirstExp
        : public Experiment
{
 protected:
  /* ------------------------------------------------------------------ */
  // Use to compute fitness for one iteration

  /* ------------------------------------------------------------------ */
  
  // Members functions
  void copy(const FirstExp& other);
  void destroy();
  
public:
  /* --------------- FIXED FUNCTIONS --------------- */
  FirstExp(Parameters* params, int argc, char** argv);
  FirstExp(const FirstExp& other);
  virtual ~FirstExp();
  
  virtual void init_local_variables(Parameters* params);
  virtual int init_single_evaluation(void);
  
  virtual void finalise_single_evaluation(void);
  virtual void finalise_evolutionary_run(void);
  virtual void finalise_evaluation_loop (void);
  
  virtual void compute_fitness(void);
  
  FirstExp& operator=(const FirstExp &other);
  /* ----------------------------------------------- */
};

#endif // FIRSTEXP_H
