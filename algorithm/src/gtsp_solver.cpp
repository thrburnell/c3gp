#include "gtsp_solver.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <unordered_set>
#include <ctime>
#include <cmath>
#include <vector>

using std::vector;

void GtspSolver::setNumberOfNodes(int nodes) {
    totalNodes = nodes;
    adjacencyMatrix = new double*[nodes];
    for (int i = 0; i < nodes; i++) {
        adjacencyMatrix[i] = new double[nodes];
    }
    nodeGroup = new int[nodes];
    for (int i = 0; i < nodes; i++) {
        nodeGroup[i] = 0;
    }
}

void GtspSolver::addPoint(int firstNode, int secondNode, double cost) {
    if (totalNodes < 0) {
        throw std::runtime_error("Number of nodes in graph not initialized!");
    }

    if (firstNode >= totalNodes ||
        secondNode >= totalNodes ||
        firstNode < 0 ||
        secondNode < 0) {
        throw std::out_of_range("Node indices out of range!");
    }

    adjacencyMatrix[firstNode][secondNode] = cost;
}

void GtspSolver::setGroupForNode(int node, int group) {
    checkInitializationReady();

    nodeGroup[node] = group;
}

void GtspSolver::setStartingPoint(int node) {
    startingPoint = node;
}

vector<int>* GtspSolver::solve() {
    checkBuildReady();

    return solveGtspWithBacktracking();
}


static vector<int> tbOrderedResult;
static vector<int> tbAccumulator;
static double tbCurrent;
static double tbMinimum;
static int tbTotalVisited;
static int tbTotalGroups;
static int* tbVisited;
static int* tbGroupVisited;

void GtspSolver::tbBkt(int currNode) {

    tbTotalVisited ++;
    tbAccumulator.push_back(currNode);
    tbVisited[currNode] = 1;
    tbGroupVisited[nodeGroup[currNode]] = 1;

    if (tbTotalVisited == tbTotalGroups) {
        if (tbCurrent + adjacencyMatrix[currNode][startingPoint] < tbMinimum) {
            tbMinimum = tbCurrent + adjacencyMatrix[currNode][startingPoint];
            tbOrderedResult.clear();
            for (const auto& it : tbAccumulator) {
                tbOrderedResult.push_back(it);
            }
        }
    }

    for (int i = 0; i < totalNodes; i++) {
        if (! tbVisited[i] && !tbGroupVisited[nodeGroup[i]]) {
            tbCurrent += adjacencyMatrix[currNode][i];
            tbBkt(i);
            tbCurrent -= adjacencyMatrix[currNode][i];
        }
    }

    tbVisited[currNode] = 0;
    tbGroupVisited[nodeGroup[currNode]] = 0;
    tbAccumulator.pop_back();
    tbTotalVisited --;
}

vector<int>* GtspSolver::solveGtspWithBacktracking() {

    checkBuildReady();

    tbMinimum = std::numeric_limits<double>::max();
    tbOrderedResult.clear();
    tbAccumulator.clear();
    tbVisited = new int[totalNodes];
    for (int i = 0; i < totalNodes; i++) {
        tbVisited[i] = 0;
    }
    tbGroupVisited = new int[totalNodes];
    for (int i = 0; i < totalNodes; i++) {
        tbGroupVisited[i] = 0;
    }

    tbTotalGroups = 0;
    for (int i = 0; i < totalNodes; i++) {
        int currGroup = nodeGroup[i];
        if (tbGroupVisited[currGroup] == 0) {
            tbTotalGroups++;
            tbGroupVisited[currGroup] = 1;
        }
    }

    for (int i = 0; i < totalNodes; i++) {
        tbGroupVisited[i] = 0;
    }

    tbCurrent = 0;
    tbTotalVisited = 0;

    tbBkt(startingPoint);

    return &tbOrderedResult;
}

///////////////////////
// Genetic Algorithm //
///////////////////////

// Inspired from here
// http://josilber.scripts.mit.edu/GTSP.pdf


chromosome* GtspSolver::solveGtspWithGeneticAlgorithm() {

    checkBuildReady();

    srand(time(NULL));

    tbGroupVisited = new int[totalNodes];
    for (int i = 0; i < totalNodes; i++) {
        tbGroupVisited[i] = 0;
    }

    tbTotalGroups = 0;
    for (int i = 0; i < totalNodes; i++) {
        int currGroup = nodeGroup[i];
        if (tbGroupVisited[currGroup] == 0) {
            tbTotalGroups++;
            tbGroupVisited[currGroup] = 1;
        }
    }

    for (int i = 0; i < totalNodes; i++) {
        tbGroupVisited[i] = 0;
    }

    population* pop = getInitialPopulation();

    for (int i = 0; i < 200; i++) {
        population* heroes = getBestChromosomes(pop);
        population* children = getOffspringThroughCrossover(heroes);
        killWorstChromosomes(pop);
        mutatePopulation(pop);

        while (!children->empty()) {
            pop->push_back(children->back());
            children->pop_back();
        }
    }

    chromosome* result = getBestChromosome(pop);

    return result;
}

void GtspSolver::mutation(chromosome* chrom) {

    int cut1 = rand() % chrom->size();
    int cut2 = rand() % chrom->size();

    if (cut1 > cut2) {
        int aux = cut1;
        cut1 = cut2;
        cut2 = aux;
    }

    for (int i = 0; i < (cut2 - cut1 + 1) / 2; i++) {
        int aux = (*chrom)[cut1 + i];
        (*chrom)[cut1 + i] = (*chrom)[cut2 - i];
        (*chrom)[cut2 - i] = aux;
    }
}

population* GtspSolver::crossover(chromosome* chrom1, chromosome* chrom2) {
    //TODO
    return NULL;
}

population* GtspSolver::getInitialPopulation() {
    auto result = new population();

    for (int i = 1; i <= 50; i++) {
        for (int j = 0; j < tbTotalGroups; j++) {
            tbGroupVisited[j] = 0;
        }

        auto chromosome = new vector<int>();
        int totalNodesAdded = 0;

        chromosome->push_back(startingPoint);
        tbGroupVisited[nodeGroup[startingPoint]] = true;
        totalNodesAdded++;

        for (;;) {
            if (totalNodesAdded == tbTotalGroups) {
                break;
            }

            int randomNode = rand() % totalNodes;
            if (nodeGroup[randomNode] == true) {
                continue;
            }

            chromosome->push_back(randomNode);
            tbGroupVisited[nodeGroup[randomNode]] = true;
            totalNodesAdded++;
        }

        result->push_back(chromosome);
    }

    return result;
}

double GtspSolver::getFitness(chromosome* chrom) {

    double length = 0;

    for (int i = 1; i < chrom->size(); i++) {
        length += adjacencyMatrix[chrom->at(i-1)][chrom->at(i)];
    }

    length += adjacencyMatrix[chrom->at(chrom->size()-1)][chrom->at(0)];

    return length;
}

chromosome* GtspSolver::getBestChromosome(population* pop) {

    double bestFitnessValue = std::numeric_limits<double>::max();
    vector<int>* bestFitnessChromosome = NULL;

    for (const auto& it : *pop) {
        double currentFitnessValue = getFitness(it);
        if (currentFitnessValue < bestFitnessValue) {
            bestFitnessValue = currentFitnessValue;
            bestFitnessChromosome = it;
        }
    }

    if (bestFitnessChromosome == NULL) {
        throw std::runtime_error("No chromosome was selected by getBestChromosome() method");
    }

    return bestFitnessChromosome;
}

population* GtspSolver::getBestChromosomes(population* pop) {
    population* new_pop = new population();
    vector<double> cum_sum;
    double cumulativeARFitnessValue = 0;
    const double kReprodPow = 0.375;

    // Finds the *worst* fitness value in the population.
    double worstFitnessValue = std::numeric_limits<double>::min();
    for (const auto& it : *pop) {
        worstFitnessValue = std::max(worstFitnessValue, getFitness(it));
    }

    // Computes the auxiliary value for each element.
    for(int j = 0; j < pop->size(); ++j) {
        double ARFitnessValue = pow(worstFitnessValue - 
                                    getFitness(pop->at(j)),
                                    kReprodPow);
        cumulativeARFitnessValue += ARFitnessValue;
        cum_sum.push_back(cumulativeARFitnessValue);
    }

    // Select individuals for reproduction.
    // Note that the algorithm DOES allow for the same chromosome to
    // be selected multiple times.
    // Note: This is suboptimal (such sampling can be done in O(1))
    // but the populations we work with generally aren't very large.
    for (int i = 0; i < 30; ++i) {
        double target = rand() * cumulativeARFitnessValue;
        int to_add;
        for(int j = 0; j < pop->size(); ++j) {
            if(target < cum_sum[j]) {
                to_add = j;
                break;
            }
        }

        new_pop->push_back(pop->at(to_add));
    }

    return new_pop;
}

void GtspSolver::killWorstChromosomes(population* pop) {
    const double kDeathPow = 0.375;
    vector<bool> death_list(pop->size(), false);
    vector<double> cum_sum;
    double cumulativeADFitnessValue = 0;

    // Finds the *best* fitness value in the population.
    double bestFitnessValue = std::numeric_limits<double>::max();
    for (const auto& it : *pop) {
        bestFitnessValue = std::min(bestFitnessValue, getFitness(it));
    }

    // Computes the auxiliary value for each element.
    for (int j = 0; j < pop->size(); ++j) {
        double ADFitnessValue = pow(getFitness(pop->at(j)) -
                                    bestFitnessValue,
                                    kDeathPow);
        cumulativeADFitnessValue += ADFitnessValue;
        cum_sum.push_back(cumulativeADFitnessValue);
    }

    // Use rejection sampling to determine which to kill
    for (int num_killed = 0; num_killed < 30;) {
        double target = rand() * cumulativeADFitnessValue;
        for(int j = 0; j < pop->size(); ++j) {
            if(target < cum_sum[j]) {
                if(!death_list[j]) {
                    ++num_killed;
                    death_list[j] = true;
                }
                break;
            }
        }
    }

    population* survivors = new population();

    // Kill everything which is destined to die
    for (int i = 0; i < pop->size(); ++i) {
        if (!death_list[i]) {
            survivors->push_back(pop->at(i));
        }
    }

    *pop = *survivors;
}

population* GtspSolver::getOffspringThroughCrossover(population* bestFits) {

    //TODO
    return bestFits;

}

void GtspSolver::mutatePopulation(population* pop) {
    // Mutates each chromosome in the population with probability 0.05

    for(auto& it : *pop) {
        if(rand() < 0.05) {
            mutation(it);
        }
    }
}