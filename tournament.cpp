#include "tournament.h"

/* -------------------------------------------------------------------------------------- */

Tournament::Tournament ( Experiment* experiment ) : GA( experiment ){
  unsigned int num_bases_per_allele = 1;
  chromosome        = new Chromosome <chromosome_type> *[num_groups];
  tmp_chromosome    = new Chromosome <chromosome_type> *[num_groups];
  for (int g = 0; g < num_groups; g++){
    chromosome[g]     = new Chromosome <chromosome_type> [num_agents_per_group];
    tmp_chromosome[g] = new Chromosome <chromosome_type> [num_agents_per_group];
    for(int ind = 0; ind < num_agents_per_group; ind++){
      chromosome[g][ind].set_diploid ( DIPLOID_FLAG );
      chromosome[g][ind].init_allele_values ( m_experiment->getNetworksNbGenes() /*num_alleles_*/, num_bases_per_allele );
      tmp_chromosome[g][ind].set_diploid ( DIPLOID_FLAG );
    }
  }
  fitness.clear();
  m_average_fitness = 0.0;
  m_is_initialised = true;
}

/* -------------------------------------------------------------------------------------- */

Tournament::~Tournament ( void ){
  for (int g = 0; g < num_groups; g++){
    delete[] chromosome[g];
    delete[] tmp_chromosome[g];
  }
  delete[] chromosome;
  delete[] tmp_chromosome;
}

/* -------------------------------------------------------------------------------------- */

void Tournament::assign_fitness( const int ind, const vector <double> & final_fitness ){
  if( ind == 0 ){
    m_average_fitness = 0;
    fitness.clear();
    fitness.push_back( MakeValueWithIndex(final_fitness[0], ind) );
  }
  else {
    fitness.push_back( MakeValueWithIndex(final_fitness[0], ind) );
    if( ind == (num_tot_solutions-1) ) sort(fitness.begin(), fitness.end());
  }
  m_average_fitness += final_fitness[0];
}

/* -------------------------------------------------------------------------------------- */

void Tournament::breeding   ( void ){

  for(int g = 0; g < num_groups; g++){
    if( g < num_elite ){
      for(int ind = 0; ind < num_agents_per_group; ind++){
	tmp_chromosome[g][ind] = chromosome[fitness[num_tot_solutions-1-g].index][ind];
      }
    }
    else{
      int mum, dad, first_ind, second_ind;
      for(int ind = 0; ind < num_agents_per_group; ind++){
	select_group ( &mum );
	first_ind = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_agents_per_group );
	
	if( gsl_rng_uniform(GSL_randon_generator::r_rand)  < prob_cross_over ) {
	  dad = mum;
	  do{
	    select_group( &dad );
	  }while( mum == dad );
	  second_ind = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_agents_per_group );
	  tmp_chromosome[g][ind].create_with_cross_over_and_mutate_operators ( chromosome[mum][first_ind], chromosome[dad][second_ind], &prob_mutation );
	}
	else{
	  tmp_chromosome[g][ind].create_with_mutate_operator ( chromosome[mum][first_ind], &prob_mutation );
	}
      }
    }
  }
  
  for(int g = 0; g < num_groups; g++){
    for(int ind = 0; ind < num_agents_per_group; ind++){
      chromosome[g][ind] = tmp_chromosome[g][ind];
    }
  }
}

/* -------------------------------------------------------------------------------------- */

void Tournament::select_group( int *ind ){
  int p[POOL_SIZE];
  int counter = 0;
  double max_value = 0.0;
  bool equal_ind   = false;
  do{
    do{
      equal_ind = false;
      p[counter] = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_tot_solutions );
      for (int j = 0; j < counter; j++){
	if( p[counter] == p[j] ) {
	  equal_ind = true;
	  break;
	}
      }
    }while( equal_ind );
    if( fitness[p[counter]].value >= max_value ){
      max_value = fitness[p[counter]].value;
      *ind = fitness[p[counter]].index;
    }
    counter++;
  }while(counter != POOL_SIZE);
}
/* -------------------------------------------------------------------------------------- */

void Tournament::dumpToFile ( const char* fileDir, const char* fileName ){
  char fname_genome[500];
  sprintf(fname_genome, "%s%s_pop_G%d.geno", fileDir, fileName, m_current_generation  );
  ofstream out ( fname_genome );
  out.setf( ios::fixed );
  
  for(unsigned int g=0; g<num_groups; g++) {
    for(unsigned int ind = 0; ind < num_agents_per_group; ind++) {
      out << " " << chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values().size();
      for(int n=0; n<chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values().size(); n++){
	out << " " << setprecision(15) << chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values()[n]; 
      }
    }
    out << " " << fitness[num_tot_solutions-1-g].value;
    out	<< endl;
  }
  out.close();
}

/* -------------------------------------------------------------------------------------- */

void Tournament::upload_genome_from_file( const char *dir, const char *fileName, const int generation ) {
  char fname_genome[500];
  sprintf(fname_genome, "%s%s_pop_G%d.geno", dir, fileName, generation );
 
  ifstream inFile (fname_genome );
  inFile.setf(ios::fixed );
  string s;
  int num_g = 0;
  int genotype_lenght;
  vector <chromosome_type> genes;
  genes.assign(chromosome[0][0].get_allele_values().size(), 0);
  
  while(getline(inFile, s) && ( num_g < num_groups ) ){
    istringstream ss(s);
    
    for(unsigned int ind = 0; ind < num_agents_per_group; ind++) {
      ss >> genotype_lenght;
      for(int q=0; q<genes.size(); q++){
	ss >> genes[q];
      }
      chromosome[num_g][ind].set_allele_values( genes );
    }
    
    num_g++;
  }
  fitness.clear();
}
/* -------------------------------------------------------------------------------------- */

void Tournament::runOneGeneration ( void ){

}

/* -------------------------------------------------------------------------------------- */

void Tournament::computeFitnessForTheRange (const unsigned int begin, const unsigned int end){

}
/* -------------------------------------------------------------------------------------- */
//                                       END
/* -------------------------------------------------------------------------------------- */

