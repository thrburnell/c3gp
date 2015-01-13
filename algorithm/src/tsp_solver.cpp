#include "tsp_solver.h"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <iostream>

void TspSolver::setNumberOfNodes(int nodes) {
    totalNodes = nodes;
    adjacencyMatrix = new double*[nodes];
    for (int i = 0; i < nodes; i++) {
        adjacencyMatrix[i] = new double[nodes];
    }
}

void TspSolver::addPoint(int firstNode, int secondNode, double cost) {
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

void TspSolver::setStartingPoint(int node) {
    startingPoint = node;
}

std::vector<int>* TspSolver::solveTsp() {
    checkBuildReady();

    if (totalNodes < 8) {
        return solveTspWithBacktracking();
    }

    std::vector<int>* result = solveTspWithNNGreedy();
    apply2OptLocalSearch(result);

    return result;
}

std::vector<int>* TspSolver::solveTspWithNNGreedy() {

    checkBuildReady();

    std::vector<int>* result = new std::vector<int>();

    int pivot = startingPoint;
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

double TspSolver::computeTourWeight(std::vector<int>* tour) {
    if (tour->empty()) {
        return 0;
    }

    double weight = 0;
    for (int i = 1; i < tour->size(); ++i) {
        weight += adjacencyMatrix[tour->at(i-1)][tour->at(i)];
    }
    weight += adjacencyMatrix[tour->at(tour->size() - 1)][startingPoint];

    return weight;
}

// Applies 2-opt local search heuristic to the given tour, modifying it
// in-place.
void TspSolver::apply2OptLocalSearch(std::vector<int>* tour) {
    bool hasImprovement = true;
    double min_dist = computeTourWeight(tour);
    std::vector<int> temp = *tour; // copy tour to a temporary buffer
    temp.push_back(startingPoint); // makes implementation easier
    totalNodes++;

    while (hasImprovement) {
        hasImprovement = false;
        for (int i = 1; i < totalNodes; i++) {
            for (int j = i + 2; j < totalNodes; j++) {
                // We are trying to cut (i-1, i) and (j-1, j).
                // We're then comparing cost of start->(i-1), (i-1)->(j-1),
                // (j-1)->(i), (i)->(j) and (j)->start vs. original.
                double new_dist = 0;

                // Start to (i - 1)
                for (int k = 1; k < i; ++k) {
                    new_dist += adjacencyMatrix[temp[k-1]][temp[k]];
                }

                // (i - 1) to (j - 1)
                new_dist += adjacencyMatrix[temp[i-1]][temp[j-1]];

                // (j - 1) to (i), backwards
                for (int k = j - 1; k > i; --k) {
                    new_dist += adjacencyMatrix[temp[k]][temp[k-1]];
                }

                // (i) to (j)
                new_dist += adjacencyMatrix[temp[i]][temp[j]];

                // (j) to start
                for (int k = j + 1; k < totalNodes; k++) {
                    new_dist += adjacencyMatrix[temp[k-1]][temp[k]];
                }

                // Check if there is an improvement
                if (new_dist < min_dist) {
                    hasImprovement = true;
                    min_dist = new_dist;
                    // Swap the relevant elements.
                    std::reverse(temp.begin() + i, temp.begin() + j);
                }
            }
        }
    }
    totalNodes--;
    temp.pop_back(); // get rid of the extra origin added to make things easier
    *tour = temp; // update the starting vector.
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

// Dynamic Programming code.
// hash_combine from Boost.
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

static std::unordered_map<std::pair<std::vector<bool>, int>, double>* opt_map;
static std::unordered_map<std::pair<std::vector<bool>, int>, int>* prev_step;

double TspSolver::dynamicSolve(std::vector<bool> visited, int end) {
    if (opt_map->find(std::make_pair(visited, end)) != opt_map->end()) {
        return (*opt_map)[std::make_pair(visited, end)];
    }

    if (std::count(visited.begin(), visited.end(), true) == 0) {
        return 0;
    }

    if (std::count(visited.begin(), visited.end(), true) == 1) {
        // find which bit is involved
        (*opt_map)[std::make_pair(visited, end)] 
            = adjacencyMatrix[startingPoint][end];
        (*prev_step)[std::make_pair(visited, end)] = startingPoint;
        return adjacencyMatrix[startingPoint][end];
    }

    // The 'other' cases when we need to take something out
    double min_cost = std::numeric_limits<double>::max();
    visited[end] = false;
    for (int i = 0; i < totalNodes; ++i) {
        if (visited[i]) {
            double possible_cost = dynamicSolve(visited, i) +
                                   adjacencyMatrix[i][end];
            if (possible_cost < min_cost) {
                min_cost = possible_cost;
                (*prev_step)[std::make_pair(visited, end)] = i;
            }
        }
    }
    visited[end] = true;
    (*opt_map)[std::make_pair(visited, end)] = min_cost;
    return min_cost;
}

std::vector<int>* TspSolver::solveTspWithDynamicProgramming() {
    opt_map
        = new std::unordered_map<std::pair<std::vector<bool>, int>, double>();
    prev_step
        = new std::unordered_map<std::pair<std::vector<bool>, int>, int>();

    std::vector<bool> all_nodes(totalNodes, true);
    // No need to visit the origin as an intermediate point.
    all_nodes[startingPoint] = false; 

    dynamicSolve(all_nodes, 0);

    std::vector<int>* solution = new std::vector<int>(totalNodes);
    std::vector<bool> considered_nodes(all_nodes);
    int currNode = startingPoint;
    for(int i = totalNodes - 1; i >= 0; --i) {
        currNode =
            (*prev_step)[std::make_pair(considered_nodes, currNode)];
        considered_nodes[currNode] = false;
        (*solution)[i] = currNode;
    }
    return solution;
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
