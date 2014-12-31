#include "tsp_solver.h"

#include <limits>
#include <stdexcept>
#include <unordered_set>
#include <vector>

void TspSolver::setNumberOfNodes(int nodes) {
    totalNodes = nodes;
    adjacencyMatrix = new double*[nodes];
    for (int i = 0; i < nodes; i++) {
        adjacencyMatrix[i] = new double[nodes];
    }
}

void TspSolver::addPoint(int firstNode, int secondNode, double cost) {
    if (totalNodes < 0) {
        throw std::runtime_error("The number of nodes in the graph has not been initialized!");
    }

    adjacencyMatrix[firstNode][secondNode] = cost;
}

void TspSolver::setStartingPoint(int node) {
    startingPoint = node;
}

std::vector<int>* TspSolver::solveTsp() {
    checkBuildReady();

    if (totalNodes < 8) {
        return solveTspWithBacktracking();
    }

    return solveTspWithNNGreedy();
}

std::vector<int>* TspSolver::solveTspWithNNGreedy() {

    checkBuildReady();

    std::vector<int>* result = new std::vector<int>();

    int pivot = 0;
    bool visited[totalNodes];
    for (int i = 0; i < totalNodes; i++) {
        visited[i] = 0;
    }

    result->push_back(0);
    while (result->size() < totalNodes) {
        visited[pivot] = 1;

        double min_dist = std::numeric_limits<double>::max();
        int next = 0;

        for (int i = 0; i < totalNodes; i++) {
            if (!visited[i] && adjacencyMatrix[pivot][i] < min_dist) {
                min_dist = adjacencyMatrix[pivot][i];
                next = i;
            }
        }

        result->push_back(next);
        pivot = next;
    }

    return result;
}

// CODE FOR BACKTRACKING
// TODO: Move this into a separate file or something. Ask someone??

static std::vector<int> tbOrderedResult;
static std::vector<int> tbAccumulator;
static double tbCurrent;
static double tbMinimum;
static int tbTotalVisited;
static int* tbVisited;

void TspSolver::tbBkt(int currNode) {

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

std::vector<int>* TspSolver::solveTspWithBacktracking() {

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

std::vector<int>* TspSolver::solveTspWithGeneticAlgorithm() {

    throw std::runtime_error("TODO solve TSP using Genetic Algorithms");

    checkBuildReady();

    std::vector<int>* result = new std::vector<int>();

    return result;
}
