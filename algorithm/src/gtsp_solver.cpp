#include "gtsp_solver.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <unordered_set>
#include <ctime>
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


vector<int>* GtspSolver::solveGtspWithGeneticAlgorithm() {

    throw std::runtime_error("TODO solve TSP using Genetic Algorithms");

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

    vector<vector<int>*>* initialPopulation = getInitialPopulation();

    vector<int>* result = getBestChromosome(initialPopulation);

    return result;
}


vector<vector<int>*>* GtspSolver::getInitialPopulation() {
    auto result = new vector<vector<int>*>();

    for (int i = 1; i <= 50; i++) {
        for (int j = 0; j < tbTotalGroups; j++) {
            tbGroupVisited[j] = 0;
        }

        auto chromosome = new vector<int>();

        chromosome->push_back(startingPoint);
        tbGroupVisited[nodeGroup[startingPoint]] = true;

        for (;;) {

        }


        result->push_back(chromosome);
    }



    return result;
}

double GtspSolver::getFitness(vector<int>* chromosome) {

    double length = 0;

    for (int i = 1; i < chromosome->size(); i++) {
        length += adjacencyMatrix[chromosome->at(i-1)][chromosome->at(i)];
    }

    length += adjacencyMatrix[chromosome->at(chromosome->size()-1)][chromosome->at(0)];

    return length;
}

vector<int>* GtspSolver::getBestChromosome(vector<vector<int>*>* population) {

    double bestFitnessValue = std::numeric_limits<double>::max();
    vector<int>* bestFitnessChromosome = NULL;

    for (const auto& it : *population) {
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
