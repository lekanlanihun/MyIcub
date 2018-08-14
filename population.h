#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <algorithm>
#include <mutex>

#include "General.h"

class Experiment;

namespace smoga
{

    template<typename F, typename DATA, typename C>
    /**
         * @brief The Population class Provide the storage of multiple chromosomes in order to apply a GA.
         */
    class Population
    {
    protected:
        // Counters
        unsigned int m_nbMaxChromosomes;                ///> Number maximum of member of chromosomes for this population.
        unsigned int m_nbMaxGroups;                     ///> Number maximum of groups of chromosomes for this population.
        static unsigned int m_sNbMaxGroups;             ///> Number maximum of groups for a population of chromosomes (common to all population).
        static unsigned int m_sNbAgents;                ///> Number of agent per group
        static double m_proportionalChromosomesKeep;    ///> Indicate a percentage of chromosomes that wil be keep in each generation.

        static double m_crossOverProbability;           ///> Probability for a chromosome to crossover.
        static double m_mutateProbability;              ///> Probability for a chromosome to mutate.

        std::vector< F > m_maxFitness;
        std::vector< F > m_minFitness;
        std::vector< F > m_averageFitness;

        std::vector< C > m_chromosomes;                 ///> Chromosomes composing the population.

        std::mutex m_mutex;

        Experiment* m_experiment;

        /**
             * @brief destroy Clear Datas.
             */
        virtual void destroy();
        /**
             * @brief copy Copy content of other datas.
             */
        virtual void copy(const Population& other);

    public:
        Population(Experiment* experiment, const int maxChromosome = -1);
        Population(const Population& other);
        virtual ~Population();

        /**
             * @brief Evaluate the fitness for all chromosomes of the population.
             * The function must rank all solutions according to their fitness in order : the worst to the better.
             */
        virtual void evaluateFitness() =0;

        /**
             * @brief Compute mutation for all chromosomes of the population according to m_mutateProbability.
             */
        virtual void mutate();

        /**
             * @brief selectOneChromosome Select one chromosome from m_chromosomes based on the crowded tournament.
             * @return A chromosome.
             */
        virtual C selectOneChromosome() =0;

        /**
             * @brief select a pair of Chromosomes.
             * @return the pair of chromosomes chose as parent.
             */
        virtual std::pair< C, C > selectChromosomesPair() =0;
        /**
             * @brief perform a crossOver on chromosomes according to m_crossOverProbability.
             * @param parents pair of chromosomes that will be use as parents.
             * @return children Chromosomes generated.
             */
        virtual C crossOver(const std::pair< C, C > parents) =0;

        /**
             * @brief generateRandomChromosomes generate a random population of chromosomes.
             */
        virtual void generateRandomChromosomes();

        /**
             * @brief addChromosome Add a Chromosome to m_chromosomes vector.
             * @param chromosome Will be add to m_chromosomes vector.
             */
        virtual void addChromosome(const C& chromosome);

        /**
             * @brief addChromosomes Add a vector of Chromosomes to m_chromosomes vector.
             * @param chromosomes Will be add to m_chromosomes vector.
             * @param number Number of element that will be added from chromosomes
             */
        virtual void addChromosomes(const std::vector< C > &chromosomes, int number = -1);

        /**
             * @brief isFull Check if the population is completely filled.
             * @return true if the population is full (m_chromosomes.size() >= m_nbMaxChromosomes).
             */
        virtual bool isFull();

        /**
             * @brief reset Reset a population.
             */
        virtual void reset();

        /**
             * @brief computeStats Compute all statistics needed to dump to a file.
             */
        virtual void computeStats();

        ////////////// Accessors/Setters //////////////
        /**
             * @brief setSNbMaxGroups Set the number max of groups for a population (common to all population).
             * @param sNbMaxGroups Number max of groups.
             */
        static void setSNbMaxGroups(const int sNbMaxGroups) { m_sNbMaxGroups = sNbMaxGroups; }
        /**
             * @brief getSNbMaxChromosomes Get the numbr max of groups (common to all population).
             * @return Number max of groups for the population.
             */
        static int getSNbMaxGroups() { return m_sNbMaxGroups; }

        /**
             * @brief setNbMaxChromosomes Set the number max of chromosomes for a population for this population.
             * @param nbMaxChromosomes Number max of chromosomes.
             */
        inline void setNbMaxChromosomes(const int nbMaxChromosomes) { this->m_nbMaxChromosomes = nbMaxChromosomes; }
        /**
             * @brief getNbMaxChromosomes Get the number max of chromosomes for this population.
             * @return Number max of chromosomes for this population.
             */
        inline int getNbMaxChromosomes() { return this->m_nbMaxChromosomes; }

        /**
             * @brief setNbAgents Set the number of agents.
             * @param nbAgents Number of agents.
             */
        static void setNbAgents(const unsigned int nbAgents) { m_sNbAgents = nbAgents; }
        /**
             * @brief getNbAgents Get the numbr of agents.
             * @return Number of agents.
             */
        static int getNbAgents() { return m_sNbAgents; }

        /**
             * @brief getCurrentNbChromosomes Get the current number of chromosomes in the population.
             * @return Number of members currently in the population.
             */
        inline int getCurrentNbChromosomes() const { if (m_chromosomes.empty()) return 0; return m_chromosomes.size(); }

        /**
             * @brief setCrossOverProbability Set the probability to crossover.
             * @param crossOverProbability Probability to crossover.
             */
        static void setCrossOverProbability(const double crossOverProbability) { m_crossOverProbability = crossOverProbability; }
        /**
             * @brief getCrossOverProbability Get the probability to crossover.
             * @return The probability to crossover.
             */
        static double getCrossOverProbability() { return m_crossOverProbability; }

        /**
             * @brief setMutateProbability Set the probability to mutate.
             * @param mutateProbability Probability to mutate.
             */
        static void setMutateProbability(const double mutateProbability) { m_mutateProbability = mutateProbability; }
        /**
             * @brief getMutateProbability Get the probability to mutate
             * @return The probability to mutate
             */
        static double getMutateProbability() { return m_mutateProbability; }

        /**
             * @brief setProportionalKeeping Set the coefficient of proportionnality for chromosomes that will be kept in the current generation for the next.
             * @param proportionalKeeping Coefficient of proportionnality.
             */
        static void setProportionalKeeping(const double proportionalKeeping) { m_proportionalChromosomesKeep = proportionalKeeping; if (m_proportionalChromosomesKeep > 1) m_proportionalChromosomesKeep = 1; if (m_proportionalChromosomesKeep < 0) m_proportionalChromosomesKeep = 0; }
        /**
             * @brief getProportionalKeeping Get the coefficient of proportionnality for chromosomes that will be kept in the current generation for the next.
             * @return Coefficient of proportionnality.
             */
        static double getProportionalKeeping() { return m_proportionalChromosomesKeep; }

        /**
             * @brief getChromosomes Get the vector storing all chromosomes composing the Population.
             * @return Vector of chromosomes.
             */
        inline std::vector< C > getChromosomes() { return m_chromosomes; }
        /**
             * @brief setChromosomes Set the vector storing all chromosomes composing the Population to those in parameter.
             * @param chromosomes Vector of chromosomes
             */
        inline void setChromosomes(const std::vector< C > chromosomes) { m_chromosomes = chromosomes; }

        std::vector< F > getMaxFitness() const { return m_maxFitness; }
        std::vector< F > getMinFitness() const { return m_minFitness; }
        std::vector< F > getAverageFitness() const { return m_averageFitness; }

        /**
             * @brief getBestSolution Best solution found by GA.
             * @return The solution to the problem.
             */
        virtual std::vector< C > getBestSolution() const =0;

        // Operator+ like
        Population& add(const Population& op);
        // Operator
        Population& operator=(const Population& other);
    };

    // Init static variables
    template<typename F, typename DATA, typename C>
    unsigned int Population<F, DATA, C>::m_sNbMaxGroups = 100;
    template<typename F, typename DATA, typename C>
    unsigned int Population<F, DATA, C>::m_sNbAgents = 1;
    template<typename F, typename DATA, typename C>
    double Population<F, DATA, C>::m_proportionalChromosomesKeep = 0.2;

    template<typename F, typename DATA, typename C>
    double Population<F, DATA, C>::m_crossOverProbability = 0.3;
    template<typename F, typename DATA, typename C>
    double Population<F, DATA, C>::m_mutateProbability = 0.04;


    template<typename F, typename DATA, typename C>
    Population<F, DATA, C>::Population(Experiment *experiment, const int maxChromosome)
#ifdef _HETERO_GROUP_SELECTION_
    : m_nbMaxChromosomes(maxChromosome == -1 ? m_sNbMaxGroups*m_sNbAgents : maxChromosome)
#else
    : m_nbMaxChromosomes(maxChromosome == -1 ? m_sNbMaxGroups : maxChromosome)
#endif
        , m_nbMaxGroups(m_sNbMaxGroups)
        , m_chromosomes()
        , m_experiment(experiment)
    {
    }

    template<typename F, typename DATA, typename C>
    Population<F, DATA, C>::Population(const Population<F, DATA, C>& other)
    {
        copy(other);
    }

    template<typename F, typename DATA, typename C>
    Population<F, DATA, C>::~Population()
    {
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::destroy()
    {
        m_chromosomes.clear();
        m_maxFitness.clear();
        m_minFitness.clear();
        m_averageFitness.clear();
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::copy(const Population<F, DATA, C>& other)
    {
        m_nbMaxChromosomes = other.m_nbMaxChromosomes;
        m_chromosomes = other.m_chromosomes;
        m_experiment = other.m_experiment;
        m_maxFitness = other.m_maxFitness;
        m_minFitness = other.m_minFitness;
        m_averageFitness = other.m_averageFitness;
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::mutate()
    {
        const unsigned int nbChromosomes = m_chromosomes.size();
        for (unsigned int i = 0 ; i < nbChromosomes ; ++i)
            m_chromosomes[i].mutate();
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::generateRandomChromosomes()
    {
        m_chromosomes.clear();
        // Fill the population until it is full
        while (!isFull())
        {
            C chromosome;
            chromosome.generateRandomChromosome();
            addChromosome(chromosome);
        }
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::addChromosome(const C &chromosome)
    {
        if (!isFull())
            m_chromosomes.push_back(chromosome);
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::addChromosomes(const std::vector< C >& chromosomes, int number)
    {
        unsigned int limit = number == -1 ? chromosomes.size() : number;
        int i = 0;
        while (!isFull() && i < limit)
        {
            m_chromosomes.push_back(chromosomes[i]);
            ++i;
        }
    }

    template<typename F, typename DATA, typename C>
    bool Population<F, DATA, C>::isFull()
    {
        if (m_chromosomes.empty())
            return false;
        return m_chromosomes.size() >= m_nbMaxChromosomes;
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::reset()
    {
        m_chromosomes.clear();
        m_nbMaxChromosomes = m_sNbMaxGroups * m_sNbAgents;
    }

    template<typename F, typename DATA, typename C>
    void Population<F, DATA, C>::computeStats()
    {
        // Compute Fitness min, max and average for the current population
        m_maxFitness.clear();
        m_minFitness.clear();
        m_averageFitness.clear();

        if (this->m_chromosomes.empty())
            return;

        const unsigned int nbObjectives = this->m_chromosomes[0].getNbObjective();
        const unsigned int nbGroups = m_nbMaxGroups;
        for(unsigned int o = 0 ; o < nbObjectives ; ++o)
        {
            m_maxFitness.push_back(this->m_chromosomes[0].getFitness()[o]);
            m_minFitness.push_back(this->m_chromosomes[0].getFitness()[o]);
            m_averageFitness.push_back(0);

            for (unsigned int i = 0 ; i < nbGroups ; ++i)
            {
#ifdef _HETERO_GROUP_SELECTION_
                if (this->m_chromosomes[i*this->m_sNbAgents].getFitness()[o] < m_minFitness[o])
                    m_minFitness[o] = this->m_chromosomes[i*this->m_sNbAgents].getFitness()[o];

                if (this->m_chromosomes[i*this->m_sNbAgents].getFitness()[o] > m_maxFitness[o])
                    m_maxFitness[o] = this->m_chromosomes[i*this->m_sNbAgents].getFitness()[o];

                m_averageFitness[o] += this->m_chromosomes[i*this->m_sNbAgents].getFitness()[o];
#else
                if (this->m_chromosomes[i].getFitness()[o] < m_minFitness[o])
                    m_minFitness[o] = this->m_chromosomes[i].getFitness()[o];

                if (this->m_chromosomes[i].getFitness()[o] > m_maxFitness[o])
                    m_maxFitness[o] = this->m_chromosomes[i].getFitness()[o];

                m_averageFitness[o] += this->m_chromosomes[i].getFitness()[o];
#endif
            }

            m_averageFitness[o] /= nbGroups;
        }
    }

    template<typename F, typename DATA, typename C>
    Population<F, DATA, C>& Population<F, DATA, C>::add(const Population<F, DATA, C>& op)
    {
        this->m_chromosomes.reserve(this->m_chromosomes.size() + op.m_chromosomes.size());
        this->m_chromosomes.insert(this->m_chromosomes.end(), op.m_chromosomes.begin(), op.m_chromosomes.end());
        this->m_nbMaxChromosomes += op.m_nbMaxChromosomes;
        this->m_nbMaxGroups += op.m_nbMaxGroups;

        return *this;
    }

    template<typename F, typename DATA, typename C>
    Population<F, DATA, C>& Population<F, DATA, C>::operator=(const Population<F, DATA, C>& other)
    {
        if(this != dynamic_cast<Population<F, DATA, C>*>(&other))
        {
            destroy();
            copy(other);
        }
        return *this;
    }

}

#endif // POPULATION_H
