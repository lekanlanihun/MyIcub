#ifndef _PARAMETERS_
#define _PARAMETERS_

#include "general.h"

#include "../EVOL_ALGORITHM/roulette_wheel.h"
#include "../EVOL_ALGORITHM/tournament.h"
#include "../EVOL_ALGORITHM/swarm_ga.h"

#include "../MOEA/nsgaii.h"
#include "../MOEA/tournamentm.h"
#include "../MOEA/chromosomemdoubledouble.h"
#include "../MOEA/chromosomemdoubleint.h"

// Typedefs
#ifdef DOUBLE_GENES_TYPE
typedef double GenesType;
typedef ChromosomeMDoubleDouble ChromosomeDataType;
#else
typedef int GenesType;
typedef ChromosomeMDoubleInt ChromosomeDataType;
#endif

// Population Type
typedef TournamentM< double, GenesType, ChromosomeDataType > PopulationType;

class Experiment;

class Parameters
{
  
private:
    bool m_evolution;
    bool m_viewing;
    bool m_reEvaluation;
    unsigned long m_rootSeed;

    // Global Simulation Parameters
    unsigned int m_nbAgents;
    unsigned int m_nbObjects;
    double** m_objectsDatas;
    unsigned int m_nbBricks;
    unsigned int m_nbCylinders;
    unsigned int m_nbSpheres;
    unsigned int m_nbLights;

    unsigned int m_nbMaxGenerations;
    unsigned int m_nbMaxEvaluations;
    unsigned int m_nbMaxIterations;

    double m_simulationTimeStep;

    std::string m_typeOfController;
    std::string m_typeOfGA;

    std::string m_runName;

    std::string m_statsFileDir;
    std::string m_statsFileName;
    std::string m_genomeFileDir;
    std::string m_genomeFileName;
    std::string m_rootSeedFileDir;
    std::string m_rootSeedFileName;
     //std::string m_camera_readings;
    unsigned int m_dumpStatsEvery;
    unsigned int m_dumpGenomeEvery;

    // Initialize NSGA-II Algorithm
    void initNSGAII(Experiment *experiment);

public:
    Parameters (const char *runName, const bool evolution, const bool viewing, const bool reEvaluation, const unsigned long seed);
    ~Parameters();
    void read_run_parameter_file(const char *run_name);
    void init_random_generator( void );

    // Choose The good GA and initialize it
    void initGA(Experiment* experiment);

    void dump_simulation_seed( void );
    void reset_seed( void );

#ifdef _MOEA_
    smoga::NSGAII<  double,
                    PopulationType,
                    ChromosomeDataType
                 > *m_ga;  // NSGA-II Algorithm
#else
    GA *m_ga;
#endif

    void dumpStats();
    void dumpGenome();

    // Accessors
    inline bool getEvolution() const { return m_evolution; }
    inline bool getViewing() const { return m_viewing; }
    inline bool getReEvolution() const { return m_reEvaluation; }
    inline unsigned long getRootSeed() const { return m_rootSeed; }
    inline unsigned int getNbAgents() const { return m_nbAgents; }
    inline unsigned int getNbObjects() const { return m_nbObjects; }
    inline double** getObjectsDatas() { return m_objectsDatas; }
    inline unsigned int getNbBricks() const { return m_nbBricks; }
    inline unsigned int getNbCylinders() const { return m_nbCylinders; }
    inline unsigned int getNbSpheres() const { return m_nbSpheres; }
    inline unsigned int getNbLights() const { return m_nbLights; }
    inline double getSimulationTimeStep() const { return m_simulationTimeStep; }
    inline unsigned int getNbMaxGenerations() const { return m_nbMaxGenerations; }
    inline unsigned int getNbMaxEvaluations() const { return m_nbMaxEvaluations; }
    inline unsigned int getNbMaxIterations() const { return m_nbMaxIterations; }
    inline std::string getRunName() const { return m_runName; }
    inline std::string getTypeOfController() const { return m_typeOfController; }
};
#endif
