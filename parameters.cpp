#include "parameters.h"

/* ---------------------------------------- */

void Parameters::read_run_parameter_file( const char *run_name ){

    ifstream I ("../MISC/init_run.txt");
    if(!I)
    {
        cerr << "File for Run Parameters not found" <<endl;
        exit(EXIT_FAILURE);
    }

    /* ------------------------------- */
    //Load parameters from init_run.txt
    /* ------------------------------- */
    m_rootSeed          = getInt('=', I);
    m_nbMaxGenerations  = getInt('=', I);
    m_nbMaxEvaluations  = getInt('=', I);
    m_nbMaxIterations   = getInt('=', I);
    m_nbAgents          = getInt('=', I);

    m_dumpStatsEvery  = getInt('=', I);
    m_dumpGenomeEvery = getInt('=', I);

    getStr('=', I, m_statsFileDir );
    getStr('=', I, m_genomeFileDir );
    getStr('=', I, m_typeOfController );
    getStr('=', I, m_typeOfGA );
    //getStr('=', I, m_camera_readings);
    m_simulationTimeStep = getDouble('=', I);

    m_nbBricks        = getInt('=', I);
    m_nbCylinders     = getInt('=', I);
    m_nbSpheres       = getInt('=', I);
    m_nbLights        = getInt('=', I);
    m_nbObjects       = m_nbBricks + m_nbCylinders + m_nbSpheres + m_nbLights;

    int num_obj_properties = getInt('=', I);

    if ( m_nbObjects )
    {
        m_objectsDatas = new double*[m_nbObjects];

        for(int b=0; b < m_nbObjects; b++)
        {
            m_objectsDatas[b] = new double[num_obj_properties];
        }

        for(int c=0; c < num_obj_properties; c++)
        {
            for(int b=0; b < m_nbObjects; b++)
            {
                m_objectsDatas[b][c] = getDouble('=', I);
            }
        }
    }
    /* ------------------------------- */
    //End of loading parameters
    /* ------------------------------- */

    m_statsFileName = m_runName;
    m_rootSeedFileDir = m_statsFileDir;
    m_rootSeedFileName = m_runName;
    m_genomeFileName = m_runName;
}


/* ---------------------------------------- */

Parameters::Parameters(const char *runName, const bool evolution, const bool viewing, const bool reEvaluation, const unsigned long seed)
{
    m_runName = runName;
    read_run_parameter_file( m_runName.c_str() ); //Open the first configuration file called init_run.txt
    m_evolution = evolution;
    m_viewing = viewing;
    m_reEvaluation = reEvaluation;
    m_rootSeed = seed;
    //cerr << " root seed = " << m_rootSeed << endl;
    init_random_generator();

    if( m_evolution )
        dump_simulation_seed ( );//This is to dump the seed number in EXP/DATA
}

/* ---------------------------------------- */

Parameters::~Parameters()
{
    // Delete NSGA-II object
    delete m_ga;

    //Delete object_data
    for(int b = 0 ; b < m_nbObjects ; b++)
        delete[] m_objectsDatas[b];
    delete[] m_objectsDatas;

    GSL_randon_generator::free_generator( );
}

/* ---------------------------------------- */

void Parameters::init_random_generator( void )
{
    GSL_randon_generator::init_generator( m_rootSeed );
}

/* ---------------------------------------- */

void Parameters::initGA(Experiment *experiment)
{
  int num_bases_per_allele = 1;

  if( m_typeOfGA == "roulette_wheel" ){
#ifndef _MOEA_
    //cerr << " The GA is roulette_wheel " << endl;
    m_ga = new Roulette_wheel ( experiment );    
#endif
  }
  else if ( m_typeOfGA ==  "tournament" ) {
#ifndef _MOEA_
    m_ga = new Tournament ( experiment );
#endif
  }
  else if ( m_typeOfGA ==  "swarm_ga" ) {
#ifndef _MOEA_
    m_ga = new Swarm_ga ( experiment );
#endif
  }  
  else if ( m_typeOfGA == "nsga_ii" )
    {
#ifdef _MOEA_
      cerr << " The GA is nsga_ii " << endl;
      initNSGAII(experiment);
#endif
    }
  else{
    cerr << "In Parameters::initGA - GA type not found " << endl;
    exit(EXIT_FAILURE);
  }
  m_ga->setNbGenerationsWanted(m_nbMaxGenerations);
}

#ifdef _MOEA_
void Parameters::initNSGAII(Experiment* experiment)
{
    generator = std::mt19937(m_rootSeed);

    if (m_ga)
      delete m_ga;

    m_ga = new smoga::NSGAII< double, PopulationType, ChromosomeDataType >(experiment, false);
    
    // Set parameters :
    try {
      m_ga->readParamsFromFile("../MOEA/initialisation_params.txt");
    }
    catch(std::runtime_error& e)
      {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
      }
    m_ga->setNbGenerationsWanted(m_nbMaxGenerations);
    // Set the number of genes per solutions
    ChromosomeDataType::setNbGenes(experiment->getNetworksNbGenes());
    PopulationType::setNbAgents( m_nbAgents );
    
    // End of Init
    m_ga->initialize();
    
    std::cout << "NSGA-II " << (m_ga->getIfIsInitialized() ? "Initialized" : "Not Initialized")
	      << std::endl << " Nb Generations : " << m_ga->getNbGenerationsWanted()
      //<< std::endl << " Nb Chromosomes : " << PopulationType::getSNbMaxChromosomes()
	      << std::endl << " Prob Mutate : " << PopulationType::getMutateProbability()
	      << std::endl << " Prob Crossover : " << PopulationType::getCrossOverProbability()
	      << std::endl << " Nb Genes : " << ChromosomeDataType::getNbGenes() << std::endl << std::endl;
    

}
#endif

/* ---------------------------------------- */

void Parameters::dump_simulation_seed( void )
{
  // //Create the Directory to save seed
  // struct stat st = {0};
  // if( stat (m_rootSeedFileDir.c_str(), &st) == -1 ){
  //   mkdir(m_rootSeedFileDir.c_str(), 0700 );
  // }
  
  std::string fileName = m_rootSeedFileDir + m_rootSeedFileName + ".seed";
  ofstream outfile ( fileName, ios::app);
  outfile.setf(ios::fixed);
  outfile << "m_rootSeed=" << m_rootSeed << endl;
  outfile.close();
}

/* ---------------------------------------- */

void Parameters::reset_seed( void )
{
    GSL_randon_generator::reset_seed( m_rootSeed );
}

/* ---------------------------------------- */

void Parameters::dumpStats()
{
  if( !(m_ga->getIndexCurrentGeneration()%m_dumpStatsEvery))
    m_ga->dumpStatisticToFile(m_statsFileDir.c_str(), m_statsFileName.c_str());
}

/* ---------------------------------------- */

void Parameters::dumpGenome()
{
    if(!(m_ga->getIndexCurrentGeneration()%m_dumpGenomeEvery))
        m_ga->dumpToFile(m_genomeFileDir.c_str(), m_genomeFileName.c_str());
}

/* ---------------------------------------- */
