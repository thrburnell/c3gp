#include "gtsp_solver.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <unordered_set>
#include <vector>

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

std::vector<int>* GtspSolver::solveGtsp() {
    checkBuildReady();

    return solveGtspWithBacktracking();
}


// CODE FOR BACKTRACKING
// TODO: Move this into a separate file or something. Ask someone??

static std::vector<int> tbOrderedResult;
static std::vector<int> tbAccumulator;
static double tbCurrent;
static double tbMinimum;
static int tbTotalVisited;
static int* tbVisited;

void GtspSolver::tbBkt(int currNode) {

    tbTotalVisited ++;
    tbAccumulator.push_back(currNode);
    tbVisited[currNode] = 1;

    if (tbTotalVisited == totalNodes) {
        if (tbCurrent + adjacencyMatrix[currNode][startingPoint] < tbMinimum) {
            tbMinimum = tbCurrent + adjacencyMatrix[currNode][startingPoint];
            tbOrderedResult.clear();
            for (const auto& it : tbAccumulator) {
                tbOrderedResult.push_back(it);
            }
        }
    }

    for (int i = 0; i < totalNodes; i++) {
        if (! tbVisited[i]) {
            tbCurrent += adjacencyMatrix[currNode][i];
            tbBkt(i);
            tbCurrent -= adjacencyMatrix[currNode][i];
        }
    }

    tbVisited[currNode] = 0;
    tbAccumulator.pop_back();
    tbTotalVisited --;
}

std::vector<int>* GtspSolver::solveGtspWithBacktracking() {

    checkBuildReady();

    tbMinimum = std::numeric_limits<double>::max();
    tbOrderedResult.clear();
    tbAccumulator.clear();
    tbVisited = new int[totalNodes];
    for (int i = 0; i < totalNodes; i++) {
        tbVisited[i] = 0;
    }
    tbCurrent = 0;
    tbTotalVisited = 0;

    tbBkt(startingPoint);

    return &tbOrderedResult;
}


//GENETIC ALGORITHM CODE
// TODO: inspired from here
// https://github.com/parano/GeneticAlgorithm-TSP/blob/master/src/algorithm.js

std::vector<int>* GtspSolver::solveGtspWithGeneticAlgorithm() {

    throw std::runtime_error("TODO solve TSP using Genetic Algorithms");

    checkBuildReady();

    std::vector<int>* result = new std::vector<int>();

    return result;
}
