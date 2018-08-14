#ifndef ChromosomeMDoubleDouble_H
#define ChromosomeMDoubleDouble_H

#include "General.h"
#include "chromosome.h"
#include "population.h"

class ChromosomeMDoubleDouble
        : public smoga::Chromosome<double, double>
{
protected:
    double m_crowdingDistance;                          ///> Crowding distance (to measure how solutions are crowed).
    int m_rank;                                         ///> Rank of the solution (or front).
    int m_nbSolutionDominatesMe;                        ///> Number of solutions that dominates this solution.
    std::vector<ChromosomeMDoubleDouble*> m_dominatedSolutions;///> Solution dominated by this one.

public:
    ChromosomeMDoubleDouble();

    /**
     * @brief resetDominance Reset Values of m_dominatedSolutions and m_nbSolutionDominatesMe.
     */
    virtual void resetDominance();
    /**
     * @brief dominates Check which solution dominates the other.
     * @param other Solution that will be checked.
     * @return true if current solution dominates other, otherwise false.
     */
    virtual bool dominates(const ChromosomeMDoubleDouble& other);

    virtual bool mutate();
    virtual void generateRandomChromosome();

    /**
     * @brief getDistance Get crowding distance of the chromosome.
     * @return Crowding distance.
     */
    inline double getDistance() const { return m_crowdingDistance; }
    /**
     * @brief setDistance Set crowding distance of the chromosome.
     * @param dist Crowding distance.
     */
    inline void setDistance(const double dist) { m_crowdingDistance = dist; }

    /**
     * @brief getRank Get the Rank of the chromosome.
     * @return Rank.
     */
    inline int getRank() const { return m_rank; }
    /**
     * @brief setRank Set the Rank of the chromosome.
     * @param rank Rank wanted.
     */
    inline void setRank(const int rank) { m_rank = rank; }

    /**
     * @brief getDominatedSolution Solutions dominated by this chromosome.
     * @return Vector of solutions dominated by this chromosome.
     */
    inline std::vector<ChromosomeMDoubleDouble*> getDominatedSolution() { return m_dominatedSolutions; }

    /**
     * @brief addDominatedSolution Add a chromosome to the vector of solutions dominated.
     * @param other chromosome to add.
     */
    virtual void addDominatedSolution(ChromosomeMDoubleDouble *other);

    /**
     * @brief setNbSolutionDominatesMe Set the number of solutions that dominates this one.
     * @param nb Number of solutions that dominates this one.
     */
    inline void setNbSolutionDominatesMe(const int nb) { m_nbSolutionDominatesMe = nb; }

    /**
     * @brief getNbSolutionDominatesMe Get the number of solutions that dominates this one.
     * @return Number of solutions that dominates this one.
     */
    inline int getNbSolutionDominatesMe() { return m_nbSolutionDominatesMe; }
};

#endif // ChromosomeMDoubleDouble_H
