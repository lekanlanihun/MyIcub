#include "chromosomemdoubledouble.h"

ChromosomeMDoubleDouble::ChromosomeMDoubleDouble()
    : Chromosome<double, double>()
    , m_crowdingDistance(0)
    , m_rank(-1)
    , m_nbSolutionDominatesMe(0)
    , m_dominatedSolutions()
{
}

void ChromosomeMDoubleDouble::resetDominance()
{
    m_nbSolutionDominatesMe = 0;
    m_dominatedSolutions.clear();
}

bool ChromosomeMDoubleDouble::dominates(const ChromosomeMDoubleDouble& other)
{
    const unsigned int nbMaxObjective = std::min(m_fitness.size(), other.m_fitness.size());

    // 2 conditions :
    // The current solution is no worse than other solution in all objectives
    for (unsigned int o = 0 ; o < nbMaxObjective ; ++o)
    {
        if (m_fitness[o] <= other.m_fitness[o])
            continue;
        else
            return false;
    }

    // The current solution is strictly better than other solution in at least one objective
    for (unsigned int o = 0 ; o < nbMaxObjective ; ++o)
    {
        if (m_fitness[o] < other.m_fitness[o])
            return true;
        else
            continue;
    }

    return false;
}

bool ChromosomeMDoubleDouble::mutate()
{
    // Mutate each genes according to the probability
    // and indicate if there has been a mutation with a flag.
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    // Gaussian distribution with the middle of distribution at 0.0
    // and the standard deviation sigma to 0.1
    std::normal_distribution<double> gaussianDistribution(0.0, 0.1);
    bool flag = false;

    const unsigned int nbBits = m_datas.size();//This is just the number of genes
    float rand;
    double value;
    //Proba is the probability of mutation
    const float proba = smoga::Population<double, int, ChromosomeMDoubleDouble>::getMutateProbability();
    for (unsigned int i = 0 ; i < nbBits ; ++i)
    {
      rand = distribution(generator);

        if (rand > proba)
            continue;

        value = gaussianDistribution(generator);

        if (m_datas[i] + value > 1)
            m_datas[i] = 1;
        else if (m_datas[i] + value < 0)
            m_datas[i] = 0;
        else
            m_datas[i] += value;

        flag = true;//This flag is just to know is there has been a mutation.
    }

    return flag;
}

void ChromosomeMDoubleDouble::generateRandomChromosome()
{
  std::uniform_real_distribution<> distribution(0.0, 1.0);

    for (unsigned int i = 0 ; i < m_nbGenes ; ++i)
        m_datas.push_back(distribution(generator));
}

void ChromosomeMDoubleDouble::addDominatedSolution(ChromosomeMDoubleDouble* other)
{
    m_dominatedSolutions.push_back(other);
}
