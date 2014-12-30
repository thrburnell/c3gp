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

std::vector<int>* TspSolver::solveTspWithBacktracking() {

	checkBuildReady();

	std::vector<int>* result = new std::vector<int>();

	return result;
}

std::vector<int>* TspSolver::solveTspWithGeneticAlgorithm() {

	throw std::runtime_error("TODO solve TSP using Genetic Algorithms");

	checkBuildReady();

	std::vector<int>* result = new std::vector<int>();

	return result;
}
