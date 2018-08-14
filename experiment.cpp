#include "experiment.h"
#include "../MISC/parameters.h"

/* ---------------------------------------------------------------------------------------- */

Experiment::Experiment(Parameters* params, int argc, char** argv)
{
// std::cout << "get to init experi constructor..." << std::endl << std::endl;
  init_local_variables(params, argc, argv);
 //std::cout << "end init experi constructor..." << std::endl << std::endl;  

}

/* ---------------------------------------------------------------------------------------- */

Experiment::Experiment(const Experiment& other)
{
    copy(other);
}

/* ---------------------------------------------------------------------------------------- */

Experiment::~Experiment( )
{
    destroy();
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::copy(const Experiment& other)
{
 
  m_evaluation        = other.m_evaluation;
  m_iteration         = other.m_iteration;
  m_maxEvaluation     = other.m_maxEvaluation;
  m_maxIteration      = other.m_maxIteration;

  m_evolution        = other.m_evolution;
  m_viewing          = other.m_viewing;
  m_reEvaluation     = other.m_reEvaluation;
  m_nbObjectives     = other.m_nbObjectives;
  m_genes            = other.m_genes;
  
  inputs             = other.inputs;
  outputs            = other.outputs;
  m_typeOfController = other.m_typeOfController;
  
  if ( m_typeOfController == "ctrnn_three_layers" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new Ctrnn3Layers());
    }
  else if ( m_typeOfController == "ctrnn_three_layers_hebb" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new Ctrnn3LayersHebb());
    }
  else if ( m_typeOfController == "simple_three_layers" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new Simple3Layers());
    }
  else if ( m_typeOfController == "perceptron" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new Perceptron());
    }
  else if ( m_typeOfController == "elman" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new Elman());
    }
  else if ( m_typeOfController == "ctrnn_fully_recurrent" )
    {
      for(int r = 0 ; r < other.m_networks.size() ; r++)
	m_networks.push_back(new CtrnnFullyRecurrent());
    }
  
  for (unsigned int i = 0 ; i < other.m_objects.size() ; i++)
    {
      SIMPLE_Brick* brick = dynamic_cast<SIMPLE_Brick*>(other.m_objects[i]);
      if (brick)
        {
	  SIMPLE_Brick* brickToPush = new SIMPLE_Brick(*brick);
	  m_objects.push_back(brickToPush);
	  continue;
        }
      
      SIMPLE_Cylinder* cylinder = dynamic_cast<SIMPLE_Cylinder*>(other.m_objects[i]);
      if (cylinder)
        {
	  SIMPLE_Cylinder* cylinderToPush = new SIMPLE_Cylinder(*cylinder);
	  m_objects.push_back(cylinderToPush);
	  continue;
        }
      
      SIMPLE_Sphere* sphere = dynamic_cast<SIMPLE_Sphere*>(other.m_objects[i]);
      if (sphere)
        {
	  SIMPLE_Sphere* sphereToPush = new SIMPLE_Sphere(*sphere);
	  m_objects.push_back(sphereToPush);
	  continue;
        }
      
      SIMPLE_Light* light = dynamic_cast<SIMPLE_Light*>(other.m_objects[i]);
      if (light)
        {
	  SIMPLE_Light* lightToPush = new SIMPLE_Light(*light);
	  m_objects.push_back(lightToPush);
	  continue;
        }
    }
  
  for (unsigned int i = 0 ; i < other.m_agents.size() ; i++)
    m_agents.push_back( new MyIcub(*(other.m_agents[i])) );
  
    m_genes.resize(m_agents.size());
  
  m_total_fitness = other.m_total_fitness;
   m_fitness_for_each_eval = other.m_fitness_for_each_eval;

  /* ------------------------------------------------- */
  r_shoulder = other.r_shoulder;
  r_elbow = other.r_elbow;
  r_eye = other.r_eye;
  l_eye = other.l_eye;
  m_max_eye_tilt_step = other.m_max_eye_tilt_step;
  m_max_eye_pan_step  = other.m_max_eye_pan_step;
  //#ifdef _GRAPHICS_
  for (unsigned int i = 0 ; i < other.gl_camera.size(); i++){
    gl_camera.push_back( new GL_Camera(*(other.gl_camera[i])) );
  }
  //#endif
//cout<<"get to copy"<<endl;  
  for (unsigned int i = 0 ; i < other.gl_camera.size(); i++){
    camera_readings = new double [other.gl_camera[i]->get_num_pixels()];
     //camera_readings=other.camera_readings;
  }

    
     
 
//cout<<"end copy"<<endl;
  /* ------------------------------------------------- */
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::destroy()
{
  inputs.clear();
  outputs.clear();
  m_total_fitness.clear();
    m_fitness_for_each_eval.clear();
  // Delete network objects
  for(int n = 0; n < m_networks.size() ; n++)
    delete m_networks[n];
  m_networks.clear();
  
  // Delete agents objects
  for (int a = 0; a < m_agents.size(); a++)
    delete m_agents[a];
  m_agents.clear();
  
  // Delete objects
  for (int o = 0; o < m_objects.size(); o++)
    delete m_objects[o];
  m_objects.clear();
  
  m_genes.clear();

  //#ifdef _GRAPHICS_
  // Delete openGL camera objects
  //for (int a = 0; a < gl_camera.size(); a++)
  //delete gl_camera[a];
  gl_camera.clear();
  //#endif

  delete[] camera_readings;
  delete eye;  

#ifdef _GRAPHICS_
  if( m_viewing )
    delete[] viewer_;
#endif
  
  r_shoulder.clear();
  r_elbow.clear();
  r_eye.clear();
  l_eye.clear();


}

/* ---------------------------------------------------------------------------------------- */

void Experiment::init_local_variables(Parameters *params, int argc, char** argv)
{
  // Init Variables used to compute fitness /*numeric_limits<double>::max()*/ 
//cout<<"get to int local"<<endl; 
  //In this function you have to create your objects like agents,
  //sensors, obstables world characteristics etc.
  m_evolution     = params->getEvolution();
  m_viewing       = params->getViewing();
  m_reEvaluation  = params->getReEvolution();
  m_evaluation    = 0;   //This is the counter for the evaluation
  m_iteration     = 0;    //This is the counter for the iterations
  m_maxEvaluation = params->getNbMaxEvaluations();
  m_maxIteration  = params->getNbMaxIterations();
  m_max_eye_tilt_step = ONE_PI * 5;
  m_max_eye_pan_step  = ONE_PI * 5;

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
  m_fitness_for_each_eval.assign(m_maxEvaluation, 0.0); 


  /* --------------- JUST FOR THIS EXP --------------- */
  // INIT ARM POSITION
  r_shoulder.assign (3, 0.0);
  r_elbow.assign    (1, 0.0);
  r_eye.assign    (2, 0.0);
  l_eye.assign    (2, 0.0);

  r_shoulder[0] = -(ONE_PI*95.0);
  r_shoulder[1] =  (ONE_PI* 5.0);
  r_shoulder[2] = -(ONE_PI*35.0);
  r_elbow[0]    =  (ONE_PI*15.0);
  /* ------------------------------------------------- */


  //This is to init the network controller
  initControllers(params);
  initObjects(params);
  initAgents(params);
  initGLCamera( argc, argv );

  m_genes.resize( params->getNbAgents() );
  
  //Resize and init the input and output array for each robot
  inputs.resize( m_agents.size() );
  outputs.resize( m_agents.size() );

  vector <double> dim_one;
  dim_one.assign(3,0.0);
  dim_one[0]= m_objects[1]->get_dim(0)[0]+1.5;
 m_objects[1]->set_dim( 0, dim_one ); 
  for (int r = 0; r < m_agents.size(); r++)
    {
      inputs[r].assign  ( m_networks[r]->get_num_input(),  0.0 );
      outputs[r].assign ( m_networks[r]->get_num_output(), 0.0 );
      camera_readings = new double [gl_camera[r]->get_num_pixels()];
      
      init_artificial_eye(gl_camera[r]->get_num_pixels());
      
      init_agents_positions( r );

    }


}

/* ---------------------------------------------------------------------------------------- */
//#ifdef _GRAPHICS_
void Experiment::initGLCamera( int argc, char** argv ){
    //cout<<"get init camera here"<<endl;
  int camera_mode = 3; // 0 for Red, 1 for Green, 2 for Blue , 3 mean you get grey scale readings, 4 you get R, G, and B
   scale=0.0, rotate=0.0;
  if( m_viewing )
    gl_camera.push_back(new GL_Camera(m_evaluation,scale,rotate, m_agents, m_objects, true, camera_mode, argc, argv )); 
  else if ( m_evolution)
    gl_camera.push_back(new GL_Camera( m_evaluation,scale, rotate,  m_agents, m_objects, false, camera_mode, argc, argv )); 
      //cout<<"leave init camera here"<<endl;
}
//#endif

/* ---------------------------------------------------------------------------------------- */

void Experiment::init_artificial_eye( int receptive_field_size){

eye = new Artificial_Eye (receptive_field_size);

}



void Experiment::initControllers(Parameters *params)
{
  m_typeOfController = params->getTypeOfController();
  if ( m_typeOfController == "ctrnn_three_layers" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new Ctrnn3Layers());
    }
  else if ( m_typeOfController == "ctrnn_three_layers_hebb" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new Ctrnn3LayersHebb());
    }
  else if ( m_typeOfController == "simple_three_layers" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new Simple3Layers());
    }
  else if ( m_typeOfController == "perceptron" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new Perceptron());
    }
  else if ( m_typeOfController == "elman" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new Elman());
    }
  else if ( m_typeOfController == "ctrnn_fully_recurrent" )
    {
      for(int r = 0; r < params->getNbAgents() ; r++)
	m_networks.push_back(new CtrnnFullyRecurrent());
    }
  else
    {
      cerr << "In Experiment::initControllers - Controller type not found " << endl;
      exit(EXIT_FAILURE);
    }
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::initObjects(Parameters* params)
{
  if(params->getNbObjects())
    {
      unsigned int count = 0, ob = 0;
      while( count < params->getNbBricks() && ob < params->getNbObjects() )
        {
	  m_objects.push_back( new SIMPLE_Brick( params->getObjectsDatas()[ob] ) );
	  ob++;
	  count++;
        }
      count = 0;
      while( count < params->getNbCylinders() && ob < params->getNbObjects() )
        {
	  m_objects.push_back( new SIMPLE_Cylinder ( params->getObjectsDatas()[ob] ) );
	  ob++;
	  count++;
        }
      count = 0;
      while( count < params->getNbSpheres() && ob < params->getNbObjects() )
        {
	  m_objects.push_back( new SIMPLE_Sphere ( params->getObjectsDatas()[ob] ) );
	  ob++;
	  count++;
        }
      count = 0;
      while( count < params->getNbLights() && ob < params->getNbObjects() )
        {
	  m_objects.push_back( new SIMPLE_Light ( params->getObjectsDatas()[ob] ) );
	  ob++;
	  count++;
        }
    }
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::initAgents(Parameters* params)
{
  for (int r = 0 ; r < params->getNbAgents() ; r++)
    {
      /* --------------- JUST FOR THIS EXP --------------- */
      m_agents.push_back( new MyIcub ( ) );
      /* ------------------------------------------------- */
    }
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::init_agents_positions( int r ){
  
//cout<<"get init here agents postn"<<endl;
  //Robot init position
  std::vector <double> pos;
  pos.assign(3, 0.0);
  pos[2] = 30.0;

  m_agents[r]->set_pos( TORSO, pos );
  m_agents[r]->set_rot( R_ELBOW, r_elbow );
  m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
  //r_eye[1]=0.436332;
  // m_agents[r]->set_pos( R_EYE, pos );
   m_agents[r]->set_rot( R_EYE, r_eye );
   // m_agents[r]->set_pos( L_EYE, pos );
   m_agents[r]->set_rot( L_EYE, l_eye);

  vector <double> position;
  position.assign(16, 0.0);  
  

}

/* ---------------------------------------------------------------------------------------- */

void Experiment::init_evaluations_loop(void)
{
  // Before starting evaluations, reset total fitness, and init network
  // There are various thing you want to do here
  // eg: resetting the fitness to zero (const vector <double> & FINAL_FITNESS)
  // init the agent position, etc
  m_evaluation = 0;   //This is the counter for the evalutions
  
  for(int i = 0; i < m_total_fitness.size(); i++)
    {
      m_total_fitness[i] = 0.0;
    }
  
  if( m_evolution )
    {
      // Initialize network for each agents with solution genes
      for(int r = 0; r < m_agents.size(); r++)
	{
	  m_networks[r]->init( m_genes[0] );
	}
    }
}

/* ---------------------------------------------------------------------------------------- */

int Experiment::init_single_evaluation(void)
{
//cout<<"get init here single eval"<<endl;
  // For each evaluation

 scale=(double)(((gsl_rng_uniform_pos( GSL_randon_generator::r_rand ) * object_noise_range) + object_noise_lower_bound));
 rotate=(double)(((gsl_rng_uniform_pos( GSL_randon_generator::r_rand ) * rotation_range) + rotation_lower_bound));
  m_fitness_for_each_eval[m_evaluation]=0.0;
 
//counter_for_no_eye_movement=0;
 counter_for_out_of_eye_view=0;

  m_iteration= 0;
  
  
  //int rest = (m_evaluation % 4);
  /*if( rest == 0 ){
    r_eye[0] = 18.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * 18.0) * ONE_PI;
    r_eye[1] = 30.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * 20.0) * ONE_PI;

    
  }
  else if( rest == 1){
    r_eye[0]  = -38.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * -38.0) * ONE_PI;
    r_eye[1] = 30.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * 20.0) * ONE_PI;
          //cout<<"r_eye[0]="<<-38.0 * ONE_PI<<endl;
     //cout<<"r_eye[1]="<<30.0 * ONE_PI<<endl;
  }
  else if( rest == 2){
    r_eye[0]  = -38.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * -38.0) * ONE_PI;
    r_eye[1] = -30.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * -20.0) * ONE_PI;
  }
  else if( rest == 3){
    r_eye[0]  = 18.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) * 18.0) * ONE_PI;
    r_eye[1] = -30.0 * ONE_PI;//(gsl_rng_uniform( GSL_randon_generator::r_rand ) *  -20.0) * ONE_PI;
  }*/


  for(int r = 0; r < m_agents.size(); r++){
     m_agents[r]->set_rot( R_EYE, r_eye );
    //reset network
    m_networks[r]->reset();
    init_agents_positions( r );
  }
  //cout<<"end init here single eval"<<endl;
  return m_evaluation+1;  // Index evaluation
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::from_genome_to_controllers( vector < vector <chromosome_type> > &genes, const int which_genotype )
{
  for(int r=0; r < m_agents.size(); r++)
    {
      m_networks[r]->set_genotype_length ( genes[which_genotype].size() );
      m_networks[r]->init( genes[which_genotype] );
    }
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::adv (void)
{
  
  if( m_viewing )
    stop_iterations_loop( );
  
  update_sensors( );
  
  update_controllers ( );
  
  update_world();
  
  compute_fitness();
  
  m_iteration++;
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::update_sensors(void) 
{
//cout<<"get to update sensor"<<endl;
  for(int r=0; r < m_agents.size(); r++)
    {

//cout<<"get to update sensor2"<<endl;
 
      inputs[r][0] = ( m_agents[r]->get_r_eye_joints_rotation()[0] - m_agents[r]->l_r_eye_tilt)/(m_agents[r]->h_r_eye_tilt - m_agents[r]->l_r_eye_tilt);
           if(  inputs[r][0]>1){inputs[r][0]=1;}else if(  inputs[r][0]<0){inputs[r][0]=0;}   
   inputs[r][1] = ( m_agents[r]->get_r_eye_joints_rotation()[1] - m_agents[r]->l_r_eye_pan)/(m_agents[r]->h_r_eye_pan - m_agents[r]->l_r_eye_pan);
            if(  inputs[r][1]>1){inputs[r][1]=1;}else if(  inputs[r][1]<0){inputs[r][1]=0;}
     // #ifdef _GRAPHICS_
      gl_camera[r]->draw(r, m_evaluation,scale,rotate);

      gl_camera[r]->get_readings(camera_readings);
#ifdef preprocessing 
            double*retina_features=eye->Get_HOG_Features(camera_readings);
           for(int i=0;i< eye->hog_feature_size;i++){
//cerr << " " << retina_features[i];
   inputs[r][i+motor_nodes]=retina_features[i];        
         }
//cerr<< endl;
#else
      eye->read_pixels(camera_readings); 
       //eye->read_fovea_pixels();   
   double*average=eye->average_pixels();
   //double*average_fovea_pixels=eye->fovea_pixels();
     for(int i=0;i<eye->retina_size;i++){
            inputs[r][i+2]=average[i];  
     }

        for(int i=0;i<eye->fovea_size;i++){
            //inputs[r][i+27]=average_fovea_pixels[i];  
     }
#endif
     for(int i=0;i<category_nodes;i++){
       inputs[r][i+38]=outputs[r][i+motor_nodes];
     }

/*if(m_rank==0){
  for(int i=0;i<inputs[r].size();i++){
 cerr << " " << inputs[r][i];
}
  cerr<< endl;
}*/

  for (int i = 0; i < outputs[r].size(); i++) outputs[r][i] = 0.0;

double x=(m_agents[r]->get_r_eye_joints_rotation()[0]);
double y=(m_agents[r]->get_r_eye_joints_rotation()[1]);

if(x < m_agents[r]->l_r_eye_tilt || x > m_agents[r]->h_r_eye_tilt || y < m_agents[r]->l_r_eye_pan|| y > m_agents[r]->h_r_eye_pan){
 counter_for_out_of_eye_view++;
}

//cout<<"get to update sensor3"<<endl;
if(counter_for_out_of_eye_view== MAX_STEPS_FOR_OUT_OF_EYE_VIEW){
        m_iteration =  m_maxIteration;
        counter_for_out_of_eye_view = 0;    
}

}
     
#ifdef _GRAPHICS_
  if( m_viewing )
    viewer_->draw(m_evaluation,scale,rotate);
#endif

// cout<<"leave pdate sensor"<<endl;


}//end of update sensor


/* ---------------------------------------------------------------------------------------- */

void Experiment::update_controllers(void)
{
  // Update robot controllers
  // Give the inputs values to the network, and compute outputs values
   for(int r = 0 ; r < m_agents.size() ; r++)
    {
      m_networks[r]->step( inputs[r],outputs[r] );
m_agents[r]-> r_pan_tilt_offset[0] = ((outputs[r][0]) -0.5) * m_max_eye_tilt_step;
m_agents[r]-> r_pan_tilt_offset[1] = ((outputs[r][1]) -0.5) * m_max_eye_tilt_step;

    }
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::update_world(void)
{
  for(int r=0; r < m_agents.size(); r++)
    {
      // r_elbow[0] += joint_step;
      // m_agents[r]->set_rot( R_ELBOW, r_elbow );
      
      // if( m_agents[r]->get_joint_bounds_reached( R_ELBOW )[0] ) { 
      // 	r_elbow[0] = (15.0*ONE_PI);
      // 	//m_agents[r]->set_joint_current_rotation( R_ELBOW, r_elbow );
	
      // 	//Advance shoulder 2
      // 	r_shoulder[2] += joint_step;
      // 	//m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	m_agents[r]->set_rot( R_SHOULDER, r_shoulder);
	
      // 	if( m_agents[r]->get_joint_bounds_reached( R_SHOULDER )[2] ) {
      // 	  r_shoulder[2] = -(ONE_PI*35.0);
      // 	  //m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	  m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
	  
      // 	  //Adavance shoulder 1
      // 	  r_shoulder[1] += joint_step;
      // 	  //m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	  m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
      // 	  if( m_agents[r]->get_joint_bounds_reached( R_SHOULDER )[1] ) {
      // 	    r_shoulder[1] = (ONE_PI*5.0);
      // 	    //m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	    m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
	    
      // 	    //Adavance shoulder 0
      // 	    r_shoulder[0] += joint_step;
      // 	    //m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	    m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
      // 	    if( m_agents[r]->get_joint_bounds_reached( R_SHOULDER )[0] ) { 
      // 	      r_shoulder[0] =  -(ONE_PI*95.0);
      // 	      //m_agents[r]->set_rot( R_ELBOW, r_elbow );
      // 	      m_agents[r]->set_rot( R_SHOULDER, r_shoulder );
      // 	    }
      // 	  }
      // 	}	
      // }
      
      m_agents[r]->update_right_eye_current_rotation(m_agents[r]->get_r_pan_tilt_offset( ));

      
    }  
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::compute_fitness(void){
         //cout<<"get to compute fitness"<<endl;

  //Here you have to update the following fitness
  //m_fitness_for_each_iter[m_iteration] = 0.0;
   
  // for the pan and tilt
      for(int r=0; r < m_agents.size(); r++){
  if((m_iteration>=ITER_START_FITNESS_COUNT) && (m_iteration<m_maxIteration)){
    int rank=0; 
 double fit_temp;   
    vector<double> outputs_cpy;
    vector<double> rank_index;
    
    outputs_cpy.assign(  category_nodes,0);
    rank_index.assign( category_nodes,0);
    
    for(int i=motor_nodes; i<outputs[r].size();i++){
      rank_index[i-motor_nodes]=(i-motor_nodes);
      outputs_cpy[i-motor_nodes]=outputs[r][i];
    }
    
    double temp_value;
    for(int i=0;i<outputs_cpy.size();i++){
      for(int j=0;j<outputs_cpy.size()-1;j++){
	if(outputs_cpy[j] > outputs_cpy[j+1]){
	  temp_value=outputs_cpy[j];
	  outputs_cpy[j]=outputs_cpy[j+1];
	  outputs_cpy[j+1]=temp_value;
	  temp_value=rank_index[j];
	  rank_index[j]=rank_index[j+1];
	  rank_index[j+1]=temp_value;
	}
      }
    }

    //cout<<"output1="<<outputs_cpy[0]<<endl;
     //cout<<"output2="<<outputs_cpy[1]<<endl;

    for(int i=0;i<rank_index.size();i++){
      if(rank_index[i]==(m_evaluation% category_nodes)){
    rank=( (category_nodes-1)-i);
	break;
      }
    }
//cout<<" "<<endl;
 //cout<<"rank="<<rank<<endl;
    fit_temp=0.5*(1.0/pow(2,rank));
    double sum_out=0.0; 

    vector<double> outputs_cpy_2;
    outputs_cpy_2.assign( category_nodes,0);
       for(int i=motor_nodes; i<outputs[r].size();i++){
         outputs_cpy_2[i-motor_nodes]=outputs[r][i];
       }


    for(int i=0;i<category_nodes;i++){
      if(i!=(m_evaluation%category_nodes)){ 
sum_out+=((1.0-outputs_cpy_2[i])*(0.5/ (double)(category_nodes-1))); //for more than two categories
      }
    }   

 fit_temp+= ((sum_out + (outputs_cpy_2[(m_evaluation% category_nodes)]*0.5)) *0.5); //for more than two categories


      //cout<<"get here"<<endl;
  //cout<<"Fitness= "<< fit_temp<<endl;

     m_fitness_for_each_eval[m_evaluation]+=fit_temp;
   

  }




	  /*vector <double>object_camera;
          object_camera.assign(3, 0.0);
	  vector <double> position;
	  position.assign(16, 0.0); 
	  position[3] = m_objects[0]->get_pos( 0 )[0];
	  position[7] = m_objects[0]->get_pos( 0 )[1];
	  position[11] = m_objects[0]->get_pos( 0 )[2];
	  m_agents[r]->compute_target_position_in_eye_coordinates(object_camera, position, m_agents[r]->RE2 );

  double magnitude=0.0;

         magnitude=((object_camera[0]*object_camera[0])+(object_camera[1]*object_camera[1])+(object_camera[2]*object_camera[2]));
          magnitude=sqrt(magnitude);
      
            object_camera[0]=  object_camera[0]/magnitude;
            object_camera[1]=object_camera[1]/magnitude;
            object_camera[2]=object_camera[2]/magnitude;


          vector <double> rot_x;
          rot_x.assign(9, 0.0);
          vector <double> result_2;
          result_2.assign(3, 0.0);
          vector<double> result;
          result.assign(3, 0.0);
          vector <double> unit_vector;
          unit_vector.assign(3, 0.0);
       
double alpha=m_agents[r]->get_r_pan_tilt_offset( )[0]; 
double theta=m_agents[r]->get_r_pan_tilt_offset( )[1];  
       
      rot_x[0]=1.0;
      rot_x[1]=0.0; 
      rot_x[2]=0.0; 
      rot_x[3]=0.0; 
      rot_x[4]=cos(alpha); 
      rot_x[5]=(-sin(alpha)); 
      rot_x[6]=0.0; 
      rot_x[7]=sin(alpha); 
      rot_x[8]=cos(alpha); 
  
      unit_vector[0]=0.0;
      unit_vector[1]=0.0;
      unit_vector[2]=1.0;

  result[0]=((rot_x[0]*unit_vector[0])+(rot_x[1]*unit_vector[1])+(rot_x[2]*unit_vector[2]));
  result[1]=((rot_x[3]*unit_vector[0])+(rot_x[4]*unit_vector[1])+(rot_x[5]*unit_vector[2]));
  result[2]=((rot_x[6]*unit_vector[0])+(rot_x[7]*unit_vector[1])+(rot_x[8]*unit_vector[2]));
   
      vector <double>rot_z;
      rot_z.assign(9, 0.0);
       
      rot_z[0]=cos(theta);
      rot_z[1]=(-sin(theta)); 
      rot_z[2]=0.0; 
      rot_z[3]=sin(theta); 
      rot_z[4]=cos(theta); 
      rot_z[5]=0.0; 
      rot_z[6]=0.0; 
      rot_z[7]=0.0; 
      rot_z[8]=1.0; 

      result_2[0]=((rot_z[0]*result[0])+(rot_z[1]*result[1])+(rot_z[2]*result[2]));
      result_2[1]=((rot_z[3]*result[0])+(rot_z[4]*result[1])+(rot_z[5]*result[2]));
      result_2[2]=((rot_z[6]*result[0])+(rot_z[7]*result[1])+(rot_z[8]*result[2]));

      //double fit=((m_agents[r]->Rnew_vector[0])*  ( object_camera[0]))+((m_agents[r]->Rnew_vector[1])* ( object_camera[1]))+((m_agents[r]->Rnew_vector[2])*  ( object_camera[2]));
      double fit=((result_2[0])*  ( object_camera[0]))+((result_2[1])* ( object_camera[1]))+((result_2[2])*  ( object_camera[2]));
      m_fitness_for_each_eval[m_evaluation]+=((result_2[0])*  ( object_camera[0]))+((result_2[1])* ( object_camera[1]))+((result_2[2])*  ( object_camera[2]));
  //m_fitness_for_each_iter[m_iteration] = ((result_2[0])*  ( object_camera[0]))+((result_2[1])* ( object_camera[1]))+((result_2[2])*  ( object_camera[2]));
  //cout<<" ONE_PI"<< ONE_PI<<endl;
   cout <<" fitness = "<< fit <<endl;*/
  //cout<<"end compute fitness"<<endl;
}

}



/* ---------------------------------------------------------------------------------------- */

void Experiment::finalise_single_evaluation (void){

 m_fitness_for_each_eval[m_evaluation]/=(double)(m_maxIteration-ITER_START_FITNESS_COUNT);
//cout<<"fitness_eval"<<" "<<       m_fitness_for_each_eval[m_evaluation]<<endl;
}

/* ---------------------------------------------------------------------------------------- */

void Experiment::finalise_evaluation_loop (void){
//cout<<"fitness_eval"<<" "<<       m_fitness_for_each_eval[m_evaluation]<<endl;
  //Compute m_total_fitness[0] relative to the group perfomace
  for(int eval =0; eval < m_maxEvaluation; eval++){
       m_total_fitness[0] += m_fitness_for_each_eval[eval];
    //m_total_fitness[0] += 0.0;
  }
  m_total_fitness[0] /= (double)(m_maxEvaluation);
  //cout<<"m_total_fitness[0]="<<" "<<m_total_fitness[0]<<endl;

}

/* ---------------------------------------------------------------------------------------- */

void Experiment::finalise_evolutionary_run(void){}

/* --------------------------------------------------------------------------------------- */

bool Experiment::stop_iterations_loop(void)
{
    //This function should not be changed
    if(m_iteration >= m_maxIteration)
    {
        finalise_single_evaluation( );
        m_iteration = 0;
        if( m_viewing )
            stop_evaluations_loop( );
        return false;
    }
    else
        return true;
}

/* ---------------------------------------------------------------------------------------- */

bool Experiment::stop_evaluations_loop(void)
{
    m_evaluation++;

    if( m_evolution )
    {
        if( m_evaluation >= m_maxEvaluation )
        {
            m_evaluation = 0;
            return false;
        }
        else
            return true;
    }
    else
    {
        if( m_viewing )
        {
            if( m_evaluation >= m_maxEvaluation )
            {
                m_evaluation = 0;
		finalise_evaluation_loop();
            }
            init_single_evaluation();
            return true;
        }
	else if( m_reEvaluation ){
	  if( m_evaluation >= m_maxEvaluation ){
	    m_evaluation = 0;
	    return false;
          }
          else{
	    return true;
          }
	}
    }
}

/* ---------------------------------------------------------------------------------------- */

Experiment& Experiment::operator=(const Experiment &other)
{
    if(this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}

/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */




