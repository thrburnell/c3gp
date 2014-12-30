#include "tsp_solver.h"

#include <vector>
#include <stdexcept>

//TODO: remove
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
		throw std::runtime_error("The number of nodes in the graph has not been initialized!");
	}

	adjacencyMatrix[firstNode][secondNode] = cost;
}

void TspSolver::setStartingPoint(int node) {
	startingPoint = node;
}

std::vector<int>* TspSolver::solveTsp() {
	if (startingPoint == -1) {
		throw std::runtime_error("Starting point not set");
	}

	return solveTspWithNNGreedy();
}

std::vector<int>* TspSolver::solveTspWithNNGreedy() {

	if (startingPoint == -1) {
		throw std::runtime_error("Starting point not set");
	}

	std::vector<int>* result = new std::vector<int>();

	for (int i = 0; i < totalNodes; i++) {
		result->push_back(i);
	}

	return result;
}

std::vector<int>* TspSolver::solveTspWithBacktracking() {
	throw "TODO";

	if (startingPoint == -1) {
		throw std::runtime_error("Starting point not set");
	}

	std::vector<int>* result = new std::vector<int>();

	return result;
}

std::vector<int>* TspSolver::solveTspWithGeneticAlgorithm() {

	throw std::runtime_error("TODO");

	if (startingPoint == -1) {
		throw std::runtime_error("Starting point not set");
	}


	std::vector<int>* result = new std::vector<int>();

	return result;
}
