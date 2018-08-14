#ifndef NSGAII_H
#define NSGAII_H

#include <iostream>

#include "ga.h"

namespace smoga
{

    template<typename F, typename P, typename C>
    class NSGAII
            : public GA<F, P, C>
    {
    protected:

        P* m_offspring; ///> Offspring of m_population.
        bool m_consoleDisplay; ///> To have a display in console.

        virtual void releaseMemory();

        /**
         * @brief breeding Perform GA operators (selection, crossover, mutation) on m_population.
         * @return The offspring population.
         */
        virtual P* breeding();

        /**
         * @brief fastNonDominatedSort Determine all non-dominated front of the Population in parameter.
         * @param popToSort Population to search non-dominated fronts.
         * @return Vector of non-dominated fronts, fisrt element correspond to front 1 and so on.
         */
        virtual std::vector < P > fastNonDominatedSort(P* popToSort);

        /**
         * @brief crowdingDistanceAssignement Compute the crowding distance on the popualtion in parameter.
         * @param popToAssignCrowdingDistance Population which we want to compute crowding distance.
         */
        virtual void crowdingDistanceAssignement(P* popToAssignCrowdingDistance);

        /**
         * @brief addChromosomeWithoutControl Add a Chromosome chromosome to the population pop, if pop will be full, it add the chromosome and increment max Population size by one.
         * @param pop Population that we want to add Chromosome.
         * @param chromosome Chromosome to add.
         */
        virtual void addChromosomeWithoutControl(P* pop, C* chromosome);

        /**
         * @brief displayAdvancement Display in the console advancement of the algorithm.
         */
        virtual void displayAdvancement();

    public:
        NSGAII(Experiment *experiment, bool consoleDisplay = true);
        virtual ~NSGAII();

        virtual void initialize();
        virtual std::vector< C > performGA();
        virtual void reset();
        virtual void dumpToFile(const char *fileDir, const char* fileName);
        virtual void dumpStatisticToFile(const char* fileDir, const char* fileName);


        /**
         * @brief runOneGeneration Do all steps needed for one generation (iteration), like mutation and crossover operators, etc...
         */
        virtual void runOneGeneration();

        ////////////// Accessors/Setters //////////////
        /**
         * @brief setConsoleDisplay Enable/Disable console display of the advancement of algorithm.
         * @param state true if want display, else false.
         */
        inline void setConsoleDisplay(bool state) { m_consoleDisplay = state; }
        /**
         * @brief getConsoleDsiplay Get state Enable/Disable of the console display of the advancement of algorithm.
         * @return Bool of the state (m_consoleDisplay).
         */
        inline bool getConsoleDsiplay() const { return m_consoleDisplay; }
    };

    template<typename F, typename P, typename C>
    NSGAII<F, P, C>::NSGAII(Experiment *experiment, bool consoleDisplay)
        : GA<F, P, C>(experiment)
        , m_offspring(nullptr)
        , m_consoleDisplay(consoleDisplay)
    {
    }

    template<typename F, typename P, typename C>
    NSGAII<F, P, C>::~NSGAII()
    {
        releaseMemory();
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::releaseMemory()
    {
        GA<F, P, C>::releaseMemory();
        if (m_offspring)
            delete m_offspring;
        m_offspring = nullptr;
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::runOneGeneration()
    {
        // Combine parent and offsprings population
        this->m_population->add(*m_offspring);

        // Determine all non dominated fronts
        std::vector < P > fronts = fastNonDominatedSort(this->m_population);

        // Secure check if it's not empty (should never arrived)
        if (fronts.empty())
        {
            this->m_currentGeneration++;
            return;
        }

        P* newParents = this->createNewPopulation();  // Future population
        int i = 0;              // Index front
        // Until the population is filled
        while (newParents->getCurrentNbChromosomes() + fronts[i].getCurrentNbChromosomes() <= newParents->getNbMaxChromosomes())
        {
            // Calculate crowding-distance in ith Front
            crowdingDistanceAssignement(&fronts[i]);

            // Include ith non-dominated front in the population
            newParents->addChromosomes(fronts[i].getChromosomes());
            i++;    // Check the next front for inclusion
        }

        if (!newParents->isFull())
        {
            // Calculate crowding-distance in ith Front, because previous loop stop just before calculate these values
            crowdingDistanceAssignement(&fronts[i]);
            std::vector< C > chromosomes = fronts[i].getChromosomes();

            // Sort in descending order the ith front using crowding operator
            std::sort(chromosomes.begin(), chromosomes.end(), CrowdingOperator< C >());

            // Choose the first (max chromosomes - size newParents) of ith front
            newParents->addChromosomes(chromosomes, newParents->getNbMaxChromosomes() - newParents->getCurrentNbChromosomes());
        }

        delete this->m_population;
        this->m_population = this->createNewPopulation();
        *this->m_population = *newParents;
        // Use selection, crossover and mutation to create new offspring population
        delete m_offspring;
        // Execute breeding (create offspring using GA)
        m_offspring = breeding();

        // Only for Display
        if (m_consoleDisplay)
            displayAdvancement();

        this->m_currentGeneration++;    // Generation counter
    }

    template<typename F, typename P, typename C>
    P* NSGAII<F, P, C>::breeding()
    {
        P* newPop = this->createNewPopulation();

        std::uniform_real_distribution<float> distribution(0.0, 1.0);

        while (!newPop->isFull())
        {
            // CrossOver only if prob <= prob crossover
            float probaCrossOver = distribution(generator);

            C chromosome;
            if (probaCrossOver <= P::getCrossOverProbability()) // Crossover
            {
                chromosome = this->m_population->crossOver(this->m_population->selectChromosomesPair());
                newPop->addChromosome(chromosome);
            }
            else    // Don't Crossover
            {
                chromosome = this->m_population->selectOneChromosome();
                newPop->addChromosome(chromosome);
            }
        }

        newPop->mutate();
        newPop->evaluateFitness();

        return newPop;
    }

    template<typename F, typename P, typename C>
    std::vector< P > NSGAII<F, P, C>::fastNonDominatedSort(P* popToSort)
    {
        // Will contain all fronts
        std::vector< P > fronts;

        // Recover population's vector of chomosomes
        std::vector< C > chromosomes = popToSort->getChromosomes();
        const unsigned int nbChromosomes = chromosomes.size();

        P* front1 = this->createNewPopulation();
        // Determine first front
#ifdef _HETERO_GROUP_SELECTION_
        const unsigned int nbAgents = P::getNbAgents();
        for (unsigned int p = 0 ; p < nbChromosomes ; p += nbAgents)
#else
        for (unsigned int p = 0 ; p < nbChromosomes ; p++)
#endif
        {
            // Sp = void | np = 0
            chromosomes[p].resetDominance();
#ifdef _HETERO_GROUP_SELECTION_
            for (unsigned int q = 0 ; q < nbChromosomes ; q += nbAgents)
#else
            for (unsigned int q = 0 ; q < nbChromosomes ; q++)
#endif
            {
                if (chromosomes[p] == chromosomes[q]) // case when we compare same chromosomes
                    continue;

                if (chromosomes[p].dominates(chromosomes[q]))       // p dominates q
                {
#ifdef _HETERO_GROUP_SELECTION_
                    for (unsigned int a = 0 ; a < nbAgents ; ++a)
                        chromosomes[p].addDominatedSolution(&chromosomes[q + a]);    // Sp = Sp U {group p}
#else
                    chromosomes[p].addDominatedSolution(&chromosomes[q]);    // Sp = Sp U {p}
#endif
                }
                else if (chromosomes[q].dominates(chromosomes[p]))  // q dominates p
                    chromosomes[p].setNbSolutionDominatesMe(chromosomes[p].getNbSolutionDominatesMe()+1);   // np + 1
            }

            // p belongs to the first front
            if (chromosomes[p].getNbSolutionDominatesMe() == 0)
            {
#ifdef _HETERO_GROUP_SELECTION_
                for (unsigned int a = 0 ; a < nbAgents ; ++a)
                {
                    chromosomes[p + a].setRank(0);
                    addChromosomeWithoutControl(front1, &chromosomes[p + a]);
                }
#else
                chromosomes[p].setRank(0);
                addChromosomeWithoutControl(front1, &chromosomes[p]);
#endif
            }
        }
        fronts.push_back(*front1);
        delete front1;
        // Reaffect chromosomes to the population to sort
        popToSort->setChromosomes(chromosomes);

        // Determine other fronts
        int i = 0; // Initialize front counter
        P* Q = this->createNewPopulation();
        while (fronts[i].getCurrentNbChromosomes() != 0)
        {
            Q->reset();
#ifdef _HETERO_GROUP_SELECTION_
            for (unsigned int p = 0 ; p < fronts[i].getChromosomes().size() ; p += nbAgents)
            {
                for (unsigned int q = 0 ; q < fronts[i].getChromosomes()[p].getDominatedSolution().size() ; q += nbAgents)
#else
            for (unsigned int p = 0 ; p < fronts[i].getChromosomes().size() ; p++)
            {
                for (unsigned int q = 0 ; q < fronts[i].getChromosomes()[p].getDominatedSolution().size() ; q++)
#endif
                {
                    int nq = fronts[i].getChromosomes()[p].getDominatedSolution()[q]->getNbSolutionDominatesMe();
                    fronts[i].getChromosomes()[p].getDominatedSolution()[q]->setNbSolutionDominatesMe(nq-1);
                    if (fronts[i].getChromosomes()[p].getDominatedSolution()[q]->getNbSolutionDominatesMe() == 0)    // q belongs to the next front, nq = 0
                    {
#ifdef _HETERO_GROUP_SELECTION_
                        for (unsigned int a = 0 ; a < nbAgents ; ++a)
                        {
                            fronts[i].getChromosomes()[p].getDominatedSolution()[q+a]->setRank(i+1);   // group qrank = i + 1
                            addChromosomeWithoutControl(Q, fronts[i].getChromosomes()[p].getDominatedSolution()[q+a]);    // Q = Q U {group q}
                        }
#else
                        fronts[i].getChromosomes()[p].getDominatedSolution()[q]->setRank(i+1);   // qrank = i + 1
                        addChromosomeWithoutControl(Q, fronts[i].getChromosomes()[p].getDominatedSolution()[q]);    // Q = Q U {q}
#endif
                    }
                }
            }
            i++;
            fronts.push_back(*Q);
        }
        // Delete fronts created if it is empty.
        auto removeEnd = std::remove_if(fronts.begin(), fronts.end(), EmptyPopulation< P >());
        if (removeEnd != fronts.end())
            fronts.erase(removeEnd, fronts.end());

        return fronts;
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::crowdingDistanceAssignement(P* popToAssignCrowdingDistance)
    {
        if (popToAssignCrowdingDistance->getChromosomes().empty())
            return;

#ifdef _HETERO_GROUP_SELECTION_
        const unsigned int nbAgents = P::getNbAgents();
#endif
        // Number of solutions in popToAssignCrowdingDistance
        const unsigned int nbSolutions = popToAssignCrowdingDistance->getCurrentNbChromosomes();
        std::vector< C > chromosomes = popToAssignCrowdingDistance->getChromosomes();

        // Initialize distance to 0
#ifdef _HETERO_GROUP_SELECTION_
        for (unsigned int i = 0 ; i < nbSolutions ; i += nbAgents)
            chromosomes[i].setDistance(0);
#else
        for (unsigned int i = 0 ; i < nbSolutions ; i++)
            chromosomes[i].setDistance(0);
#endif

        // Normaly it has to sort in ascending order
        Ascending< C > comparator;    // Comparator using to sort on ascending order each objectives
        const unsigned int nbObjective = chromosomes[0].getNbObjective();

        for (unsigned int m = 0 ; m < nbObjective ; m++)
        {
            // Sort using each objective value
            comparator.index = m;
            std::sort(chromosomes.begin(),
                      chromosomes.end(),
                      comparator);

            // Assigne value of max minus min of fitness for the objective m
            F maxMinusMinFitness = chromosomes[nbSolutions-1].getFitness()[m] - chromosomes[0].getFitness()[m];

            if (maxMinusMinFitness == 0) // Little cheat to prevent division by 0
                maxMinusMinFitness = 0.00001;
            if (chromosomes.size() == 1)    // Alone solution
            {
                chromosomes[0].setDistance(0);
                continue;
            }
            else if (chromosomes.size() == 2)
            {
                chromosomes[0].setDistance(std::numeric_limits<double>::max());
                chromosomes[1].setDistance(std::numeric_limits<double>::max());
                continue;
            }

            // So that boundary point are always selected
            // Extremes chromosomes of the vector are initialized with an infinite distance
#ifdef _HETERO_GROUP_SELECTION_
            for (unsigned int i = 0 ; i < nbAgents ; ++i)
                chromosomes[i].setDistance(std::numeric_limits<double>::max());
            for (unsigned int i = nbSolutions-1 ; i > (nbSolutions-1)-nbAgents ; --i)
                chromosomes[i].setDistance(std::numeric_limits<double>::max());
#else
            chromosomes[0].setDistance(std::numeric_limits<double>::max());
            chromosomes[nbSolutions-1].setDistance(std::numeric_limits<double>::max());
#endif

            // For all other points
            double distance;
#ifdef _HETERO_GROUP_SELECTION_
            for (unsigned int i = nbAgents ; i < nbSolutions-nbAgents ; i += nbAgents)
            {
                distance =   chromosomes[i].getDistance()
                             + (chromosomes[i+nbAgents].getFitness()[m] - chromosomes[i-nbAgents].getFitness()[m])
                             / (maxMinusMinFitness);

                for (unsigned int a = 0 ; a < nbAgents ; a++)
                    chromosomes[i + a].setDistance(distance);
            }
#else
            for (unsigned int i = 1 ; i < nbSolutions-1 ; i++)
            {
                distance =   chromosomes[i].getDistance()
                             + (chromosomes[i+1].getFitness()[m] - chromosomes[i-1].getFitness()[m])
                             / (maxMinusMinFitness);
                chromosomes[i].setDistance(distance);
            }
#endif
        }

        // Reaffect chromosomes to the population
        popToAssignCrowdingDistance->setChromosomes(chromosomes);
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::addChromosomeWithoutControl(P* pop, C* chromosome)
    {
        if (pop->isFull())
            pop->setNbMaxChromosomes(pop->getNbMaxChromosomes()+1);
        pop->addChromosome(*chromosome);
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::displayAdvancement()
    {
        const int nbSymbols = 40;
        double advancement = this->m_currentGeneration / (double)this->m_nbGenerationsWanted;
        double nbSymbolsToDraw = nbSymbols * advancement;
        std::cout << "\r" << "[";
        for (int i = 0 ; i < nbSymbols ; i++)
        {
            if (i <= nbSymbolsToDraw)
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << "]" << "\t" << advancement*100 << "%";
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::initialize()
    {
        if(this->m_isInitialized)   // already initialized
            return;

        this->releaseMemory();

        // Generate a random population make step that need to be done before running algorithm
        this->m_population = this->createNewPopulation();//Just allocate memory for m_population
        this->m_population->generateRandomChromosomes();//This function is in population.h and call functions in chromosomem...
        this->m_population->evaluateFitness(); //This is in tournament.h

	//cerr << " HERE 5 in initialie() " << endl;

        // Create offspring of the random population
        this->m_offspring = breeding();

        this->m_currentGeneration = 1;
        this->m_isInitialized = true;
    }

    template<typename F, typename P, typename C>
    std::vector< C > NSGAII<F, P, C>::performGA()
    {
        // Run the algorithm if it is initialized, and return Pareto Optimal Set
        if (!this->m_isInitialized)
            throw std::runtime_error("NSGA-II not initialzed !");

        while (this->m_currentGeneration <= this->m_nbGenerationsWanted)
            runOneGeneration();

        return this->m_population->getBestSolution();
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::reset()
    {
        this->m_currentGeneration = 1;
        this->m_isInitialized = false;
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::dumpToFile(const char* fileDir, const char* fileName)
    {
        std::string fileSaveLocation = fileDir;
        if (!endsWith(fileSaveLocation, std::string("/")))
            fileSaveLocation += '/';

        /*std::vector<std::string> filenameSplited = split(std::string(fileName), '.');
        std::ostringstream oss;
        if (filenameSplited.empty())
            oss << (this->m_currentGeneration-1) << ".txt";
        else if (filenameSplited.size() == 1)
            oss << filenameSplited[0] << (this->m_currentGeneration-1) << ".txt";
        else
            oss << filenameSplited[0] << (this->m_currentGeneration-1) << "." << filenameSplited[1];*/
        std::ostringstream oss;
        oss << fileName << "_pop_G" << (this->m_currentGeneration-1) << ".geno";

        fileSaveLocation += oss.str();

        std::ofstream file(fileSaveLocation, std::ios::out | std::ios::trunc);

        if (file)
        {
            std::vector< C > chromosomes = this->m_population->getBestSolution();
            const unsigned int nbChromosomes = this->m_population->getBestSolution().size();
            const unsigned int nbObjectives = this->m_population->getBestSolution()[0].getFitness().empty() ? 0 : this->m_population->getBestSolution()[0].getFitness().size();
            for (unsigned int i = 0 ; i < nbChromosomes ; i++)
            {
                file << C::getNbGenes();
                file << chromosomes[i].datasToStr();
                for (unsigned int o = 0 ; o < nbObjectives ; o++)
                    file << " " << chromosomes[i].getFitness()[o];
                file << " " << chromosomes[i].getRank();
                if (i != this->m_population->getBestSolution().size()-1)
                    file << std::endl;
            }
        }
        else
            throw std::runtime_error("Impossible to open or write in Genome File! : " + fileSaveLocation);
    }

    template<typename F, typename P, typename C>
    void NSGAII<F, P, C>::dumpStatisticToFile(const char* fileDir, const char* fileName)
      {
      this->m_population->computeStats();

        std::string fileSaveLocation = fileDir;
        if (!endsWith(fileSaveLocation, std::string("/")))
            fileSaveLocation += '/';
        fileSaveLocation += fileName;
	fileSaveLocation.append(".data");

        std::ofstream file(fileSaveLocation, std::ios::out | std::ios::app);

        if (file)
        {
            file << " " << (this->m_currentGeneration-1) << " /";
            const unsigned int nbObjectives = this->m_population->getMaxFitness().size();
            for (unsigned int i = 0 ; i < nbObjectives ; ++i)
                file << " " << (this->m_population->getMaxFitness()[i]);
            file << " /";
            for (unsigned int i = 0 ; i < nbObjectives ; ++i)
                file << " " << (this->m_population->getAverageFitness()[i]);
            file << " /";
            for (unsigned int i = 0 ; i < nbObjectives ; ++i)
                file << " " << (this->m_population->getMinFitness()[i]);
            file << std::endl;

            file.close();
        }
        else
            throw std::runtime_error("Impossible to open or write in Statistics File! : " + fileSaveLocation);
    }
}

#endif // NSGAII_H
