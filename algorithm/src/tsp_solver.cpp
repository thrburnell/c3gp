#include "tsp_solver.h"

#include <vector>


void TspSolver::setNumberOfNodes(int nodes) {
	adjacencyMatrix = new int*[nodes];
	for (int i = 0; i < nodes; i++) {
		adjacencyMatrix[i] = new int[nodes];
	}
}

void TspSolver::addPoint(int firstNode, int secondNode, int cost) {
	if (! init) {
		throw "The number of nodes in the graph has not been initialized!";
	}

	adjacencyMatrix[firstNode][secondNode] = cost;
}

void TspSolver::setStartingPoint(int node) {
	startingPoint = node;
}

std::vector<int>* TspSolver::solveTsp() {
	if (startingPoint == -1) {
		throw "Starting point not set";
	}

	return solveTspWithGreedy();
}

std::vector<int>* TspSolver::solveTspWithGreedy() {

	if (startingPoint == -1) {
		throw "Starting point not set";
	}

	std::vector<int>* result = new std::vector<int>();

	return result;
}

std::vector<int>* TspSolver::solveTspWithBacktracking() {
	throw "TODO";

	if (startingPoint == -1) {
		throw "Starting point not set";
	}

	std::vector<int>* result = new std::vector<int>();

	return result;
}

std::vector<int>* TspSolver::solveTspWithGeneticAlgorithm() {

	throw "TODO";

	if (startingPoint == -1) {
		throw "Starting point not set";
	}


	std::vector<int>* result = new std::vector<int>();

	return result;
}
