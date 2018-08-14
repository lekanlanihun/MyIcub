#ifndef TOURNAMENTM_H
#define TOURNAMENTM_H

#include <future>

#include "population.h"

//#include "../EXP/firstexp.h"
#include "../EXP/experiment.h"

//typedef FirstExp ExperimentType;
typedef Experiment ExperimentType;

template<typename F, typename DATA, typename C>
/**
   * @brief The TournamentM class Provide a selection of parents to breeding based on a Tournament and for Multi objective GA.
   */
class TournamentM
        : public smoga::Population<F, DATA, C>
{
protected:
    static int m_tournament_size;

    virtual void destroy();
    virtual void copy(const TournamentM<F, DATA, C> &other);
    void computeFitnessForTheRange(const unsigned int begin, const unsigned int end);

public:
    TournamentM(Experiment *experiment, const int maxChromosome = -1);
    TournamentM(const TournamentM &other);

    virtual void evaluateFitness();
    virtual C selectOneChromosome();
    virtual std::pair< C, C > selectChromosomesPair();
    virtual C crossOver(const std::pair<C, C> parents);
    virtual std::vector< C > getBestSolution() const;
    static void setTournamentSize(int tournamenmt_size ) {m_tournament_size = tournamenmt_size; }

    // Operator Like
    TournamentM& add(const TournamentM& op);
    // Operator
    TournamentM& operator=(const TournamentM& other);
};

template<typename F, typename DATA, typename C>
int TournamentM<F, DATA, C>::m_tournament_size = 0;

template<typename F, typename DATA, typename C>
TournamentM<F, DATA, C>::TournamentM(Experiment *experiment, const int maxChromosome)
    : smoga::Population<F, DATA, C>(experiment, maxChromosome)
{
}

template<typename F, typename DATA, typename C>
TournamentM<F, DATA, C>::TournamentM(const TournamentM& other)
    : smoga::Population<F, DATA, C>(other)
{
    copy(other);
}

template<typename F, typename DATA, typename C>
void TournamentM<F, DATA, C>::destroy()
{
    smoga::Population<F, DATA, C>::destroy();
}

template<typename F, typename DATA, typename C>
void TournamentM<F, DATA, C>::copy(const TournamentM<F, DATA, C> &other)
{
    smoga::Population<F, DATA, C>::copy(other);
    m_tournament_size = other.m_tournament_size;
}

template<typename F, typename DATA, typename C>
void TournamentM<F, DATA, C>::computeFitnessForTheRange(const unsigned int begin, const unsigned int end)
{
    this->m_mutex.lock();
    ExperimentType localExperiment(*(static_cast<ExperimentType*>(this->m_experiment)));
    this->m_mutex.unlock();
    const unsigned int nbAgents = this->m_sNbAgents;

#ifdef _HETERO_GROUP_SELECTION_
    // Compute the fitness for each chromosome
    for (unsigned int i = begin ; i <= end ; i += nbAgents)
    {
        // Set chromosomes genes to the experiment
        for (unsigned int chrom = 0 ; chrom < nbAgents ; ++chrom)
	  localExperiment.setGenes(chrom, this->m_chromosomes[i + chrom].getDatas());

        localExperiment.init_evaluations_loop();
        do {                                                        // Loop for evalutations
            localExperiment.init_single_evaluation();
            do {                                                    // Loop for iterations
                localExperiment.adv();
            } while(localExperiment.stop_iterations_loop());        // Until the last iteration
        } while(localExperiment.stop_evaluations_loop());           // Until the last evaluation

        localExperiment.finalise_evaluation_loop();

        // Set fitness computed to the good chromosome
        for (unsigned int chrom = 0 ; chrom < nbAgents ; ++chrom)
            this->m_chromosomes[i + chrom].setFitness(localExperiment.getFitness());
    }
#else
    // Compute the fitness for each chromosome
    for (unsigned int i = begin ; i <= end ; ++i)
    {
      localExperiment.setGenes(0, this->m_chromosomes[i].getDatas());

      //This is for the Quinn apporach      
      /*
	std::uniform_int_distribution<> distribution(0, this->m_nbMaxGroups-1 );
	//std::uniform_int_distribution<> distribution(begin, end );
	int groupMate = 0;
	for (unsigned int chrom = 1 ; chrom < nbAgents; ++chrom){
	do{
	groupMate = distribution (generator);
	}while( groupMate == i );
	localExperiment.setGenes(chrom, this->m_chromosomes[groupMate].getDatas());
      }
      */
      //End of Quinn approach
      
      localExperiment.init_evaluations_loop();
      do {                                                        // Loop for evalutations
            localExperiment.init_single_evaluation();
            do {                                                    // Loop for iterations
                localExperiment.adv();
            } while(localExperiment.stop_iterations_loop());    // Until the last iteration
        } while(localExperiment.stop_evaluations_loop());       // Until the last evaluation
      
      localExperiment.finalise_evaluation_loop();
      
      // Set fitness computed to the good chromosome
      this->m_chromosomes[i].setFitness(localExperiment.getFitness());
    }
#endif
}

template<typename F, typename DATA, typename C>
C TournamentM<F, DATA, C>::selectOneChromosome()
{
  const unsigned int nbGroups = this->m_nbMaxGroups;
    //std::uniform_int_distribution<> distributionPoolSize(2, nbGroups);
    const unsigned int poolSize = m_tournament_size; //distributionPoolSize(generator); Tournament size
    int proba[poolSize]; 

    std::uniform_int_distribution<> distribution(0, nbGroups-1);

    // Generate random Index to select groups for tournament (different of of each other index already selected)
    int counter = 0;
    bool equalIndex = false;
    do{
        do{
            equalIndex = false;
            proba[counter] = distribution(generator);
            for (int i = 0; i < counter; ++i)
            {
                if( proba[counter] == proba[i] )
                {
                    equalIndex = true;
                    break;
                }
            }
        } while( equalIndex );

        counter++;

    } while(counter != poolSize);

    C chromosome;
#ifdef _HETERO_GROUP_SELECTION_
    // Action 1 - Select Group where we will chose randomly a chromosome   
    unsigned int grpSelectedIndex = proba[0];
    double grpSelectedDistance = this->m_chromosomes[grpSelectedIndex*this->m_sNbAgents].getDistance();
    int grpSelectedRank = this->m_chromosomes[grpSelectedIndex*this->m_sNbAgents].getRank();

    for (unsigned int i = 0 ; i < poolSize ; ++i)
    {
        if( this->m_chromosomes[proba[i]*this->m_sNbAgents].getRank() < grpSelectedRank // rank i < rank group
                || (this->m_chromosomes[proba[i]*this->m_sNbAgents].getRank() == grpSelectedRank && this->m_chromosomes[proba[i]*this->m_sNbAgents].getDistance() > grpSelectedDistance)) // rank i == rank group && dist i > dist group
        {
            grpSelectedIndex = proba[i];
            grpSelectedDistance = this->m_chromosomes[grpSelectedIndex*this->m_sNbAgents].getDistance();
            grpSelectedRank = this->m_chromosomes[grpSelectedIndex*this->m_sNbAgents].getRank();
        }
    }

    // Action 2 - Select One chromosome randomly in the selected group
    // Return a random chromosome in the group selected
    std::uniform_int_distribution<> distRandomChromInGroup(0, this->m_sNbAgents-1);
    chromosome = this->m_chromosomes[grpSelectedIndex*this->m_sNbAgents + distRandomChromInGroup(generator)];
#else
    chromosome = this->m_chromosomes[proba[0]];
    for (unsigned int i = 0 ; i < poolSize ; ++i)
    {
        if( this->m_chromosomes[proba[i]].getRank() < chromosome.getRank() // rank i < rank chromosome
                || (this->m_chromosomes[proba[i]].getRank() == chromosome.getRank() && this->m_chromosomes[proba[i]].getDistance() > chromosome.getDistance())) // rank i == rank chromosome && dist i > dist chromosome
            chromosome = this->m_chromosomes[proba[i]];
    }
#endif

    return chromosome;
}

template<typename F, typename DATA, typename C>
void TournamentM<F, DATA, C>::evaluateFitness()
{
    if (this->m_chromosomes.empty())
        return;

    const unsigned int nbAgents = this->m_sNbAgents;
    const unsigned int nbChromosomes = this->m_chromosomes.size();
    const unsigned int maxNbThread =  std::thread::hardware_concurrency();

    if (maxNbThread > 2)    // Parallelize only if there are more than 2 cores
    {
#ifdef _HETERO_GROUP_SELECTION_
        const unsigned int nbGroups = this->m_nbMaxGroups;
        const unsigned int nbGroupsPerAsync = nbGroups/maxNbThread;

        unsigned int begin = 0;
        unsigned int end;
        std::vector< std::future<void> > computeFitnessPartFunc;
        for (unsigned int i = 0 ; i < maxNbThread ; ++i)
        {
            end = begin + nbGroupsPerAsync * nbAgents - 1;
            if (i == maxNbThread-1)
                end = nbChromosomes-1;

            computeFitnessPartFunc.push_back(std::async(launch::async,
                                                        [this](const unsigned int begin, const unsigned int end)
                                                        {
                                                            return this->computeFitnessForTheRange(begin, end);
                                                        },
                                                        begin,
                                                        end));

            begin += nbGroupsPerAsync * nbAgents;
        }

        for (unsigned int i = 0 ; i < maxNbThread ; ++i)
            computeFitnessPartFunc[i].get();
#else
        const unsigned int nbComputePerAsync = nbChromosomes/maxNbThread;

        unsigned int begin = 0;
        unsigned int end;
        std::vector< std::future<void> > computeFitnessPartFunc;
        for (unsigned int i = 0 ; i < maxNbThread ; ++i)
        {
            end = begin + nbComputePerAsync - 1;
            if (i == maxNbThread-1)
                end = this->m_chromosomes.size()-1;

            computeFitnessPartFunc.push_back(std::async(launch::async,
                                                        [this](const unsigned int begin, const unsigned int end)
                                                        {
                                                            return this->computeFitnessForTheRange(begin, end);
                                                        },
                                                        begin,
                                                        end));

            begin += nbComputePerAsync;
        }

        for (unsigned int i = 0 ; i < maxNbThread ; ++i)
            computeFitnessPartFunc[i].get();
#endif
    }
    else    // Not Parallelized
    {
#ifdef _HETERO_GROUP_SELECTION_
        // Compute the fitness for each chromosome
        for (unsigned int i = 0 ; i < nbChromosomes ; ++i)
        {
            // Set chromosomes genes to the experiment
            for (unsigned int chrom = 0 ; chrom < nbAgents ; ++chrom)
                this->m_experiment->setGenes(chrom, this->m_chromosomes[i + chrom].getDatas());

            this->m_experiment->init_evaluations_loop();
            do {                             
                this->m_experiment->init_single_evaluation();
                do {                                                    // Loop for iterations
                    this->m_experiment->adv();
                } while(this->m_experiment->stop_iterations_loop());    // Until the last iteration
            } while(this->m_experiment->stop_evaluations_loop());       // Until the last evaluation

            this->m_experiment->finalise_evaluation_loop();

            // Set fitness computed to the good chromosome
            for (unsigned int chrom = 0 ; chrom < nbAgents ; ++chrom)
                this->m_chromosomes[i + chrom].setFitness(this->m_experiment->getFitness());
        }
#else
        // Compute the fitness for each chromosome
        for (unsigned int i = 0 ; i < nbChromosomes ; ++i)
        {
            // Set chromosomes genes to the experiment
	  this->m_experiment->setGenes(0, this->m_chromosomes[i].getDatas());

            this->m_experiment->init_evaluations_loop();
            do {                                                        // Loop for evalutations
                this->m_experiment->init_single_evaluation();
		do {                                                    // Loop for iterations
                    this->m_experiment->adv();
                } while(this->m_experiment->stop_iterations_loop());    // Until the last iteration
            } while(this->m_experiment->stop_evaluations_loop());       // Until the last evaluation

            this->m_experiment->finalise_evaluation_loop();
	    
	    //	    cerr << " fitn[0] = " << this->m_experiment->getFitness() << endl;
	      /*  << " fitn[1] = " << this->m_experiment->getFitness()[1]
	       << end;
	    */

            // Set fitness computed to the good chromosome
            this->m_chromosomes[i].setFitness(this->m_experiment->getFitness());
        }
#endif
    }
}

template<typename F, typename DATA, typename C>
std::pair< C, C > TournamentM<F, DATA, C>::selectChromosomesPair()
{
    return std::pair< C, C >(selectOneChromosome(), selectOneChromosome());
}

template<typename F, typename DATA, typename C>
C TournamentM<F, DATA, C>::crossOver(const std::pair< C, C > parents)
{
    // Children Chromosome
    C offspring;

    std::vector<DATA> offspringGenes;    // Children chromosome => will be fill
    // Get parents genes
    std::vector<DATA> mumGenes = parents.first.getDatas();
    std::vector<DATA> dadGenes = parents.second.getDatas();

    // According to crossover probability it's the dad or mum that will begin to fill offspring genes
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    float probaCrossOver = distribution(generator);

    const unsigned int nbGenes = C::getNbGenes();
    if (nbGenes == 0)
        return offspring;

    // Random number to define on which genes crossover begin
    std::uniform_int_distribution<> distributionInt(0, C::getNbGenes()-1);
    const unsigned int indexCrossover = distributionInt(generator);

    if (probaCrossOver <= 0.5)  // Take mum genes before dad, with 1/2
    {
        for (unsigned int i = 0 ; i < indexCrossover ; ++i)
            offspringGenes.push_back(mumGenes[i]);

        for (unsigned int i = indexCrossover ; i < nbGenes ; ++i)
            offspringGenes.push_back(dadGenes[i]);
    }
    else    // Take dad genes before mum
    {
        for (unsigned int i = 0 ; i < indexCrossover ; ++i)
            offspringGenes.push_back(dadGenes[i]);

        for (unsigned int i = indexCrossover ; i < nbGenes ; ++i)
            offspringGenes.push_back(mumGenes[i]);
    }

    // Set offspring genes
    offspring.setDatas(offspringGenes);

    return offspring;
}

template<typename F, typename DATA, typename C>
std::vector< C > TournamentM<F, DATA, C>::getBestSolution() const
{
    return this->m_chromosomes;
}

template<typename F, typename DATA, typename C>
TournamentM<F, DATA, C>& TournamentM<F, DATA, C>::add(const TournamentM& op)
{
    smoga::Population<F, DATA, C>::add(op);

    evaluateFitness();

    return *this;
}

template<typename F, typename DATA, typename C>
TournamentM<F, DATA, C>& TournamentM<F, DATA, C>::operator=(const TournamentM& other)
{
    if(this != dynamic_cast<const TournamentM<F, DATA, C>*>(&other))
    {
        destroy();
        copy(other);
    }

    return *this;
}


#endif // TOURNAMENTM_H
