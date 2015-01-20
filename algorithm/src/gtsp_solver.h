#ifndef GTSP_SOLVER_H
#define GTSP_SOLVER_H

#include "solver.h"

#include <stdexcept>
#include <vector>

using std::vector;

typedef vector<int> chromosome;
typedef vector<chromosome*> population;

/**
 * Factory-ish pattern implemented here. The way you use this class is
 *  - Set the number of nodes on which you want to apply the TSP
 *  - add the points using addPoint method meaning there is a cost
 *      cost between fromNode to toNode
 *  - set the starting point (as an integer). Generally it will be node 0
 *  - call solveTsp.
 *  - The result is an ordered array of points, where the node on the
 *      first position (0) will be the starting point for the TSP
 */
class GtspSolver : public Solver {

public:
    virtual ~GtspSolver() {};

    virtual void setNumberOfNodes(int nodes);
    virtual void addPoint(int fromNode, int toNode, double cost);
    virtual void setStartingPoint(int node);
    virtual void setGroupForNode(int node, int group);

    virtual std::vector<int>* solve();

    std::vector<int>* solveGtspWithBacktracking();
    std::vector<int>* solveGtspWithGeneticAlgorithm();

private:
    double** adjacencyMatrix;
    int* nodeGroup;
    int totalNodes = -1;
    int startingPoint = -1;

    void tbBkt(int currNode);

    void checkBuildReady() {
        if (startingPoint == -1) {
            throw std::runtime_error("Starting point not set");
        } else if (startingPoint >= totalNodes) {
            throw std::runtime_error(
                "Starting point greater than no. of nodes");
        }
    }

    void checkInitializationReady() {
        if (totalNodes == -1) {
            throw std::runtime_error("Not initialized");
        }
    }

    population* getInitialPopulation();
    double getFitness(chromosome* chrom);
    chromosome* getBestChromosome(population* pop);
    void mutation(chromosome* chrom);
    population* crossover(chromosome* chrom1, chromosome* chrom2);
    population* getBestChromosomes(population* pop);
    void killWorstChromosomes(population* pop);
    population* getOffspringThroughCrossover(population* bestFits);
    void mutatePopulation(population* pop);


};

#endif /* GTSP_SOLVER_H */
