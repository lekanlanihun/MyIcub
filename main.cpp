#include <chrono>

#ifdef _GRAPHICS_
#include "../EXP/RENDERING/viewer.h"
#include "../EXP/RENDERING/interface.h"
#endif

#include "./EXP/experiment.h"
#include "./MISC/parameters.h"

bool evolution     = false;
bool viewing       = false;
bool re_evaluation = false;
char *run_name  = new char[100];
unsigned long root_seed = 0;
int target_gen   = 0;
double scale=0.0, rotation=0.0; 
/* ------------------------------------------------------------ */
void usage ( )
{
    cerr << "Bad input format - Options are required\n"
         << "-e evolutionary mode. REQUIRES the parameter -n and -s has to be specified\n (e.g., ./evo_sim -e -n A -s 637823)\n"
         << "-r re-evaluation mode. REQUIRES the evolutionary run name, a generation number, and a root seed\n (e.g., ./evo_sim -r -n A 2500 -s 637823)\n"
         << "-v viewing mode - with graphical rendering  - no file name needed\n"
         << endl;
    exit(EXIT_FAILURE);
}
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
void  parse_command_line( int argc, char** argv )
{
  if ( argc < 2 )
    usage( );
  for(int i=1; i<argc; i++) {
    if(argv[i][0] != '-') usage( );
    switch(argv[i][1]) {
    case 'r':
      if ( i==argc-1 ) { // if last arg
	cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	exit(EXIT_FAILURE);
      }
      ++i;
      if(argv[i][0] == '-' && argv[i][1] == 'n' ) {  // looks like the correct flag
	if ( i==argc-1 ) { // if last arg
	  cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
	++i;
	re_evaluation = true;
	sprintf(run_name, "%s", argv[i]);
	if ( i==argc-1 ) { // if last arg
	  cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
	++i;
	target_gen = atoi(argv[i]);
	if ( i==argc-1 ) { // if last arg
	  cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
	++i;
	if(argv[i][0] == '-' && argv[i][1] == 's' ) {  // looks like the correct flag
	  if ( i==argc-1 ) { // if last arg
	  cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	  }
	  ++i;
	  root_seed = atoi(argv[i]);
	}
	else{
	  cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
      }
      else{
	cerr << "-r re-evaluation mode, requires -n RUN NAME and GENERATION NUMBER, and -s ROOT SEED "<<endl;
	exit(EXIT_FAILURE);
      }
      break;
    case 'e':
      evolution = true;
      if ( i==argc-1 ) { // if last arg
	cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	exit(EXIT_FAILURE);
      }
      ++i;
      if(argv[i][0] == '-' && argv[i][1] == 'n' ) {  // looks like the correct flag
	if ( i==argc-1 ) { // if last arg
	  cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
	++i;
	sprintf(run_name, "%s", argv[i]);
	/* ------------ root_seed  ------------ */
	if ( i==argc-1 ) { // if last arg
	  cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	  exit(EXIT_FAILURE);
	}
	else{
	  ++i;
	  if(argv[i][0] == '-' && argv[i][1] == 's' ) {  // looks like the correct flag
	    if ( i==argc-1 ) { // if last arg
	      cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	      exit(EXIT_FAILURE);
	    }
	    ++i;
	    root_seed = atoi(argv[i]);
	  }
	  else{
	    cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	    exit(EXIT_FAILURE);
	  }
	}
	/* ------------------------------------ */
      }
      else{
	cerr << "-e evolutionary mode, requires -n RUN NAME, and -s ROOT SEED "<<endl;
	exit(EXIT_FAILURE);
      }
      break;
    case 'v':
      viewing   = true;
      break;
    default:
      usage();
    }
  }
}

/* ------------------------------------------------------------ */
/* ------------------------------------------------------------ */

int main(int argc, char** argv)
{
    
  //parse the command line
  parse_command_line( argc, argv );
     MPI_Init(&argc, &argv);
      MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

  //std::cout << "Programm Begin..." << std::endl << std::endl;
  root_seed = 427218;
  Parameters* parameters = new Parameters(run_name, evolution, viewing, re_evaluation, root_seed);

  //This is where you create the experiment
  Experiment *exp = new Experiment(parameters, argc, argv);  

  if( evolution )
    {
      //std::cout << "Evolutionary Mode :" << std::endl;
#ifdef _HETERO_GROUP_SELECTION_
      std::cout << "Heterogeneous Selection" << std::endl;
#else
      //std::cout << "Homogeneous Selection" << std::endl;
#endif
      parameters->initGA(exp);
      
      //At this point all chromosomes are initialised and evaluated
      if (!parameters->m_ga->getIfIsInitialized())
	exit(EXIT_FAILURE);
      
      std::chrono::steady_clock::time_point beginning = std::chrono::steady_clock::now();

//      MPI_Init(&argc, &argv);
//      MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);
      while(parameters->m_ga->getIndexCurrentGeneration() <parameters->m_ga->getNbGenerationsWanted())
	{ 
	  //cerr << " Gen = " << parameters->m_ga->getIndexCurrentGeneration() << endl;cin.ignore();
	  parameters->m_ga->runOneGeneration();
	  if( m_rank == 0 ) parameters->dumpStats();
	  if( m_rank == 0 ) parameters->dumpGenome();
#ifndef _MOEA_
	  if( m_rank == 0 ) parameters->m_ga->breeding();
#endif
	}
      MPI_Finalize();
      std::chrono::duration<double> elapsedTime = std::chrono::steady_clock::now() - beginning;
      
      // Compute Time elapsed display
      int secondCount = elapsedTime.count();
      int hh, mm, ss;
      hh = secondCount / 3600;
      secondCount -= hh*3600;
      mm = secondCount / 60;
      secondCount -= mm*60;
      ss = secondCount;
      //std::cout << std::endl << "Time elapsed : " << hh << "h " << mm << "min " << ss << "s." << std::endl;
    }
  else
    {
      if( viewing )
        {
#ifdef _GRAPHICS_
	  QApplication application(argc, argv);
	  Viewer    *viewer = new Viewer(  0,exp->m_evaluation, scale, rotation, exp->getAgent(), exp->getObject(), argc, argv ); 
	  exp->viewer_ = viewer;
	  Interface *render = new Interface( 0, exp, viewer );
	  render->show();
	  return application.exec();
	  delete viewer;
	  delete render;
#endif
        }
      else if( re_evaluation )
	{
	  char *buffer_file = new char[500];
	  for(int generation = target_gen; generation >= (target_gen-0); generation-=1){
#ifdef _HETERO_GROUP_SELECTION_
#ifdef _MOEA_
	    sprintf(buffer_file,"/home/elt7/Simulations/EvoSim/MOEA_GENOME/%s_pop_G%d.geno",run_name,generation);
#else
	    sprintf(buffer_file,"/home/elt7/Simulations/EvoSim/HETE_GENOME/%s_pop_G%d.geno",run_name,generation);
#endif
#else
	    sprintf(buffer_file, "/home/elt7/Simulations/EvoSim/HOMO_GENOME/%s_pop_G%d.geno", run_name, generation);
#endif	
	    //Load the genes into the file "genes"
	    int num_groups = 0;
	    vector < vector <chromosome_type> > genes;
	    upload_genome_from_file <chromosome_type> ( buffer_file, genes, &num_groups );
	    
#ifndef _MOEA_
	    for(int group = 0; group <= 1; group++){
#else
	    //for(int group = 1; group < num_groups; group++){
#endif
	      int which_genotype = group;
	      exp->from_genome_to_controllers( genes, which_genotype );
	      
	      /* --- BEGINNING OF CORE LOOP --- */ 
	      exp->init_evaluations_loop();
	      do {                                      // Loop for evalutations
		exp->init_single_evaluation();
		do {                                    // Loop for iterations
		  exp->adv();
		} while( exp->stop_iterations_loop());  // Until the last iteration
	      } while( exp->stop_evaluations_loop());   // Until the last evaluation
	      exp->finalise_evaluation_loop();
	      /* --- END OF CORE LOOP --- */
	      
	      //Dump statistics here e.g., exp->dump_re_eval_stats() 
	    }// end of groups
	  }//end of generation
	}//end of re-evaluation
      /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
      /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
      /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
      
    }//end of not evolution conditions
  delete exp;
  delete[] run_name;
  std::cout << std::endl << "Programm End..." << std::endl;
}

