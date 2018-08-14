#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <math.h>
#include<iostream>
#include<fstream>
// Controllers
#include "../CONTROLLERS/controller.h"
#include "../CONTROLLERS/ctrnn3Layers.h"
#include "../CONTROLLERS/ctrnn3LayersHebb.h"
#include "../CONTROLLERS/ctrnnFullyRecurrent.h"
#include "../CONTROLLERS/perceptron.h"
#include "../CONTROLLERS/simple3Layers.h"
#include "../CONTROLLERS/elman.h"
#include "../ROB_SENSORS_OBJS/world_entity.h"
#include "../ROB_SENSORS_OBJS/simple_objects.h"
#include "../ROB_SENSORS_OBJS/icub.h"
#include "../MOEA/General.h"    // For general functions
#include "../EXP/RENDERING/render.h"
#include "../ROB_SENSORS_OBJS/gl_camera.h"
#include "../ROB_SENSORS_OBJS/Artificial_Eye.h"
#define ITER_START_FITNESS_COUNT 50
#define MAX_STEPS_OUT_OF_IMAGES 3
#define MAX_STEPS_FOR_NO_EYE_MOVEMENT 3
#define MAX_STEPS_FOR_OUT_OF_EYE_VIEW 3
#define object_noise_lower_bound -0.1
#define object_noise_range 0.2
#define rotation_lower_bound -10.0
#define rotation_range 20.0
#define category_nodes 4
 #define motor_nodes 2

#ifdef _GRAPHICS_
#include "./RENDERING/viewer.h"
#endif

class Parameters;

class Experiment
{
protected:
  /* --------------- JUST FOR THIS EXP --------------- */
  vector <double> r_shoulder;
  vector <double> r_elbow;
  vector <double> r_eye;
  vector <double> l_eye;
  double m_max_eye_tilt_step;
  double m_max_eye_pan_step;
  //static constexpr double joint_step = ONE_PI*10.0;
  /* ------------------------------------------------- */

  /* --------------- FIXED MEMBERS --------------- */
  unsigned int  m_iteration;       //Count the num. of iterations
  unsigned int  m_maxEvaluation;      // Limit of evaluation
  unsigned int  m_maxIteration;       // LImit of iterations

  bool m_evolution;
  bool m_viewing;
  bool m_reEvaluation;

  std::vector< Controller* > m_networks;
  std::vector< SIMPLE_Objects* > m_objects;
  std::vector< MyIcub* > m_agents;
  //#ifdef _GRAPHICS_
  std::vector< GL_Camera* > gl_camera;
  //#endif
  std::string m_typeOfController;
  /* --------------------------------------------- */
  
  /* ------------- Experiement Fitness computing tools ----------------- */
  unsigned int m_nbObjectives;
  std::vector<double> m_total_fitness;                // Final Fitness to assign for a chromosome
  std::vector<double> m_fitness_for_each_eval;
  /* ------------------------------------------------------------------ */
  
  std::vector < std::vector < double > > m_genes;  // Genes of the chromosome that we compute fitness
  std::vector < std::vector < double > > inputs;      // Inputs (genes values) for connections in the neural network
  std::vector < std::vector < double > > outputs;     // Outputs generated, used to move robots
  double *camera_readings;
  //std::vector<double> camera_readings;
 int counter_for_out_of_image_view;
 int counter_for_no_eye_movement;
int  counter_for_out_of_eye_view;
  // Members functions
  void copy(const Experiment& other);
  void destroy();
  
  // Init Functions
  void initControllers(Parameters* params);
  void initObjects(Parameters* params);
  void initAgents(Parameters* params);
  //#ifdef _GRAPHICS_
  void initGLCamera( int argc, char** argv );
  //#endif
   
 private:
 double scale, rotate;
 public:
  /* --------------- FIXED FUNCTIONS --------------- */
  Experiment(Parameters* params, int argc, char** argv);
  Experiment(const Experiment& other);
  virtual ~Experiment();
  
  virtual void init_local_variables(Parameters* params, int argc, char** argv);
  virtual void init_evaluations_loop(void);
  virtual int init_single_evaluation(void);
  
  virtual void finalise_single_evaluation(void);
  virtual void finalise_evolutionary_run(void);
  virtual void finalise_evaluation_loop (void);
  
  bool stop_iterations_loop(void);
  bool stop_evaluations_loop(void);
  
  virtual void compute_fitness(void);
  
  void update_sensors(void);
  void update_controllers(void);
  void update_world(void);
  void manage_collisions (void);
  void adv (void);
  
  void from_genome_to_controllers(vector < vector <chromosome_type> > &genes, const int which_genotype);
  void init_agents_positions( int r );
  void init_artificial_eye(int);
  
  /* ----------------------------------------------- */
   unsigned int  m_evaluation;      //Count the num. of evaluation
  //double *camera_readings;
 Artificial_Eye *eye;

  // Accessors
  inline std::vector<double> getFitness() const { return m_total_fitness; }
  inline int getEvaluationCounter() const { return m_evaluation; }
  inline unsigned int getNbObjects() const { return m_objects.size(); }
  inline SIMPLE_Objects* getObject(const unsigned int index) { return m_objects[index]; }
  inline vector <SIMPLE_Objects*> getObject( void ) { return m_objects; }
  inline unsigned int getNbAgents() const { return m_agents.size(); }
  inline MyIcub* getAgent(const unsigned int index) { return m_agents[index]; }
  inline vector <MyIcub*> getAgent( void ) { return m_agents; }
  inline unsigned int getNetworksNbGenes() const { return m_networks[0]->get_genotype_length(); }
  /* --------------------------------------------------------------------------------- */
  
  // Setters
  inline void setGenes(const unsigned int index, const std::vector<double>& genes) { 
    m_genes[index] = genes; 
  }
#ifdef _GRAPHICS_
  Viewer *viewer_;  
#endif

  Experiment& operator=(const Experiment &other);
};

#endif // EXPERIMENT_H
