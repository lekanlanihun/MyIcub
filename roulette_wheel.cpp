#include "roulette_wheel.h"

/* -------------------------------------------------------------------------------------- */

Roulette_wheel::Roulette_wheel ( Experiment* experiment ) : GA( experiment ){
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
  wheel.assign (num_tot_solutions, 0.0);
  fitness.clear();
  m_average_fitness = 0.0;
  
  fit_vector.resize( num_tot_solutions );
  parents.resize(  num_groups * num_agents_per_group );
  
#ifdef _RANK_BASED_
  linear_rank_wheel();
#endif
  m_is_initialised = true;
}

/* -------------------------------------------------------------------------------------- */

Roulette_wheel::~Roulette_wheel ( void ){
  for (int g = 0; g < num_groups; g++){
    delete[] chromosome[g];
    delete[] tmp_chromosome[g];
  }
  delete[] chromosome;
  delete[] tmp_chromosome;
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::assign_fitness( const int ind, const vector <double> & final_fitness ){
  
  wheel[ind] = 0.0;
  fitness.push_back( MakeValueWithIndex(final_fitness[ind], ind) );
  m_average_fitness += final_fitness[ind];
  
  for (int i = 0; i < 1/*final_fitness.size()*/; i++){
    fit_vector[ind].push_back( final_fitness[ind] );
  }
  

}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::breeding   ( void ){

#ifdef _HETERO_INDIVIDUAL_SELECTION_
  breeding_hetero_individual_selection();
#else
  breeding_group_selection();
#endif
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::breeding_group_selection ( void ){
  /*
    for(int i = 0; i < num_tot_solutions; i++)
    cerr << " fit["<< i << " ] = " << fitness[i].value << " index = " << fitness[i].index << endl;
    getchar();
  */

  int mum, dad, first_ind, second_ind;

  for(int i = 0; i < parents.size(); i++) parents[i].clear();
  
  for(int g = 0; g < num_groups; g++){    
    if( g < num_elite ){
      for(int ind = 0; ind < num_agents_per_group; ind++){
	tmp_chromosome[g][ind] = chromosome[fitness[num_tot_solutions-1-g].index][ind];
	int who  = (num_agents_per_group*fitness[num_tot_solutions-1-g].index)+ind; 
	parents[(num_agents_per_group*g)+ind].push_back( who );
	parents[(num_agents_per_group*g)+ind].push_back( 999 );
      }
    }
    else{
      for(int ind = 0; ind < num_agents_per_group; ind++){
	select_group ( &mum );
#ifdef _HETERO_GROUP_SELECTION_
	first_ind = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_agents_per_group );
#else
	first_ind = 0;
#endif
	parents[(num_agents_per_group*g)+ind].push_back( (num_agents_per_group*mum)+first_ind );
	
	if( gsl_rng_uniform(GSL_randon_generator::r_rand)  < prob_cross_over ) {
	  select_second_group( &mum, &dad );
#ifdef _HETERO_GROUP_SELECTION_
	  second_ind = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_agents_per_group );
#else
	  second_ind = 0;
#endif
	  parents[(num_agents_per_group*g)+ind].push_back( (num_agents_per_group*dad)+second_ind );
	  tmp_chromosome[g][ind].create_with_cross_over_and_mutate_operators ( chromosome[mum][first_ind], 
									       chromosome[dad][second_ind], &prob_mutation );
	}
	else{
	  parents[(num_agents_per_group*g)+ind].push_back( 999 );
	  tmp_chromosome[g][ind].create_with_mutate_operator ( chromosome[mum][first_ind], &prob_mutation );
	}
      }
    }
  }
  copy_new_genotypes_in_working_array ();
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::copy_new_genotypes_in_working_array ( void ) {
  for(int g = 0; g < num_groups; g++){
    for(int ind = 0; ind < num_agents_per_group; ind++){
      chromosome[g][ind] = tmp_chromosome[g][ind];
    }
  }
}

/* -------------------------------------------------------------------------------------- */

#ifdef _HETERO_INDIVIDUAL_SELECTION_
void Roulette_wheel::breeding_hetero_individual_selection( void ){
  //THE FOLLOWING ALGORITHM IS PROBABLY WRONG 01-10-2014
  // NEEDS TO BE REVISED
  for(int g = 0; g < num_groups; g++){//num_groups is probably a mistake
    if( g < num_elite ){
      tmp_chromosome[g][0] = chromosome[fitness[num_tot_solutions-1-g].index][0];
    }
    else{
      int mum = 999;
      select_group ( &mum );
      if( gsl_rng_uniform(GSL_randon_generator::r_rand)  < prob_cross_over ) {
	int dad = 999;
	select_second_group( &mum, &dad );
	tmp_chromosome[g][0].create_with_cross_over_and_mutate_operators ( chromosome[mum][0], 
									   chromosome[dad][0], &prob_mutation );
      }
      else{
	tmp_chromosome[g][0].create_with_mutate_operator ( chromosome[mum][0], &prob_mutation );
      }
    }
  }
  copy_new_genotypes_in_working_array ();
}
#endif

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::select_group( int *mum ){
  *mum = gsl_rng_uniform_int (GSL_randon_generator::r_rand, num_tot_solutions );
  /*
    for(int i = 0; i< num_tot_solutions; i++){
    cerr << " wheel["<<i<<"] = " << wheel[i] << endl;
    getchar();
    }
  */
  double reference = gsl_rng_uniform(GSL_randon_generator::r_rand) * wheel[num_tot_solutions-1];
  for (int selected = num_solutions_truncated; selected  < num_tot_solutions; selected++ ){
    /*    
	  cerr << " wheel["<<selected<<"] = " << wheel[selected] 
	  << " reference = " << reference
	  << endl;
	  getchar();
    */
    if(reference < wheel[selected] ){
      *mum = fitness[selected].index;
      //cerr << " mum = " << *mum << endl;
      break;
    }
  }
}

/* --------------------------------------------------------------------------------------- */

void Roulette_wheel::select_second_group(const int *mum, int *dad ){
  *dad = *mum;
  int iter = 0;
  do{
    select_group( dad );
    iter++;
  }while(*mum == *dad && iter < 5);
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::compute_cumulative_fitness ( void ){

  double tmp_fit = 0.0;
  for(int i = 0; i < num_tot_solutions; i++){      
    if( i < num_solutions_truncated ){
      wheel[i] = 0.0;
      tmp_fit  = fitness[i].value;
    }
    else if ( i == num_solutions_truncated ){
      wheel[i] = fitness[i].value - tmp_fit;
    }
    else{
      wheel[i] += wheel[i-1] + ( fitness[i].value - tmp_fit);
    }
    //cerr << " Chrom = " << i << " fitness["<<i<<"].value = " << fitness[i].value << " fitness["<<i<<"].index = " << fitness[i].index
    //	 << " Wheel["<<i<<"] = " << wheel[i] << endl;
    //getchar();
  }
}

/* -------------------------------------------------------------------------------------- */

#ifdef _RANK_BASED_
void Roulette_wheel::linear_rank_wheel( void ){
  double selective_pressure = 2.0;
  for (int position = 0; position < num_tot_solutions; position++){
    if (position <= (num_solutions_truncated-1) ) {
      wheel[position] = 0.0;
    }
    else {
      wheel[position] = ((2.0 - selective_pressure) + 
			 2.0*(selective_pressure - 1.0)*((double)(position - num_solutions_truncated )/(double)(num_tot_solutions-1-num_solutions_truncated)) );
    }
  }
}
#endif

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::dumpToFile ( const char* fileDir, const char* fileName ){
  
  char fname_genome[500];
  sprintf(fname_genome, "%s%s_pop_G%d.geno", fileDir, fileName, m_current_generation  );
  ofstream out ( fname_genome );
  out.setf( ios::fixed );
  
  for(unsigned int g=0; g<num_groups; g++) {
    for(unsigned int ind = 0; ind < num_agents_per_group; ind++) {
      out << "" << chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values().size();
      for(int n=0; n<chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values().size(); n++){
	out << " " << setprecision(15) << chromosome[fitness[num_tot_solutions-1-g].index][ind].get_allele_values()[n]; 
      }

      //out << " " << fitness[num_tot_solutions-1-g].value;
      
      int who = ( num_agents_per_group * fitness[num_tot_solutions-1-g].index ) + ind;
      out << " " << who;
      for(int z = 0; z < parents[who].size(); z++){
	out << " " << parents[who][z];
      }
      out << " " << fit_vector[fitness[num_tot_solutions-1-g].index][0]
	  << " " << fit_vector[fitness[num_tot_solutions-1-g].index][1+ind];
      out << endl;
    }
  }
  out.close();
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::upload_genome_from_file( const char *dir, const char *fileName, const int generation ) {
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
  fit_vector.clear();
}

/* -------------------------------------------------------------------------------------- */

void Roulette_wheel::runOneGeneration ( void ){
  const unsigned int nbChromosomes = num_groups;
  const unsigned int nbAgents      = num_agents_per_group;
  
  m_average_fitness = 0.0;
  fitness.clear();
  for(int i = 0; i <fit_vector.size(); i++) fit_vector[i].clear();
  
  //All processes must stop here and wait for the others
  MPI_Barrier(MPI_COMM_WORLD);
      
  m_genes.resize( chromosome[0][0].allele.size() );
  if(m_rank == 0 ){
    for (unsigned int i = 0 ; i < nbChromosomes ; ++i)
      {
	//send values in tmp_vec to process with m_rank i, with i equal to the i^th individual
	MPI_Send(&chromosome[i][0].allele[0], chromosome[i][0].allele.size() , MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      }
    m_genes = chromosome[0][0].allele;
  }
  else{ 
    //if you are process m_rank > 0, then receive the values from tmp_vec and store them in m_genes
    MPI_Recv(&m_genes[0], m_genes.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  
  
  //From this point on each process does evalution independently
  //MPI_Barrier(MPI_COMM_WORLD);
  this->m_experiment->setGenes( 0, m_genes);
  this->m_experiment->init_evaluations_loop();
  do {                                                        // Loop for evalutations
    this->m_experiment->init_single_evaluation();
    do {                                                    // Loop for iterations
      this->m_experiment->adv();
    } while(this->m_experiment->stop_iterations_loop());    // Until the last iteration
  } while(this->m_experiment->stop_evaluations_loop());       // Until the last evaluation
  this->m_experiment->finalise_evaluation_loop();
  
  //Stop and wait for everyone to finalise the evalution
  MPI_Barrier(MPI_COMM_WORLD);
  
  // Set fitness computed to the chromosome
  vector <double> store_fitness(nbChromosomes, 0);
  if (m_rank == 0){
    MPI_Gather(&this->m_experiment->getFitness()[0], 1, MPI_DOUBLE, &store_fitness[0], 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    //Process rank 0 gathers fitness vaklues from all other processes
  }
  else { 
    MPI_Gather(&this->m_experiment->getFitness()[0], 1, MPI_DOUBLE, NULL, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
    //Each process send to process rank 0 the fitness
  }
  
  //At this point store_fitness has all the fitnesses sent by all other processes
  if (m_rank == 0){
    for (unsigned int i = 0 ; i < nbChromosomes ; ++i){
      assign_fitness( i, store_fitness );	
    }
  }
  
  if( m_rank == 0 ){
 sort(fitness.begin(), fitness.end());
//for(int i=0;i<nbChromosomes;i++){
   generational_max_fitness = fitness[num_tot_solutions-1].value;
//}
    generational_min_fitness =fitness[0].value;
generational_avg_fitness = 0;
    for (int i = 0; i < fitness.size(); i++){

        generational_avg_fitness= generational_avg_fitness + fitness[i].value;

    }
generational_avg_fitness = generational_avg_fitness/num_tot_solutions;
}
#ifndef _RANK_BASED_
  if( m_rank == 0 )  compute_cumulative_fitness ( );
#endif
  m_current_generation++;
}

/* -------------------------------------------------------------------------------------- */
void Roulette_wheel::computeFitnessForTheRange(unsigned int, unsigned int){}

/* -------------------------------------------------------------------------------------- */
//                                       END
/* -------------------------------------------------------------------------------------- */

