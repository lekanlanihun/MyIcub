#ifndef _TOURNAMENT_SELECTION__
#define _TOURNAMENT_SELECTION__

#include "ga.h"
#include "chromosome.h"

#define POOL_SIZE     4
using namespace std;

class Tournament : public GA { 
  
 private:
  //vector< ValueWithIndex <double> > fitness;
  
  Chromosome <chromosome_type> **chromosome;
  Chromosome <chromosome_type> **tmp_chromosome;
  
 public:
  //Tournament ( const int num_alleles_, const int num_bases_per_allele_, const int num_agents_per_group_ );
  Tournament ( Experiment* experiment );
  ~Tournament( );
  
  /* -------------------------------------------------------------------------------------------------- */
  /*                                             VIRTUAL FUNCTIONS                                      */
  /* -------------------------------------------------------------------------------------------------- */  
  void computeFitnessForTheRange                 (const unsigned int begin, const unsigned int end);
  void runOneGeneration                          ( void );
  void breeding                                  ( void );
  void assign_fitness                            ( const int ind, const vector <double> & final_fitness);
  void dumpToFile                                ( const char* fileDir, const char* fileName );
  void upload_genome_from_file                   ( const char *dir, const char *fileName, const int generation );
  inline vector <chromosome_type> & get_solution ( const int g, const int ind ){ return chromosome[g][ind].allele; }
  /* -------------------------------------------------------------------------------------------------- */
  
  void select_group                              ( int *mum );
};

#endif
