#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <stdexcept>
#include <vector>


class TspSolver {

public:
	virtual ~TspSolver() {};

	void setNumberOfNodes(int nodes);
	void addPoint(int firstNode, int secondNode, double cost);
	void setStartingPoint(int node);

	std::vector<int>* solveTsp();

	std::vector<int>* solveTspWithNNGreedy();
	std::vector<int>* solveTspWithBacktracking();
	std::vector<int>* solveTspWithGeneticAlgorithm();

private:
	double** adjacencyMatrix;
	int totalNodes = -1;
	int startingPoint = -1;

	void checkBuildReady() {
		if (startingPoint == -1) {
			throw std::runtime_error("Starting point not set");
		}
	}

};

#endif /* TSP_SOLVER_H */
