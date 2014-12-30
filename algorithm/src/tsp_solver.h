#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>


class TspSolver {
public:
	virtual ~TspSolver() {};

	void setNumberOfNodes(int nodes);
	void addPoint(int firstNode, int secondNode, int cost);
	void setStartingPoint(int node);

	std::vector<int>* solveTsp();

	std::vector<int>* solveTspWithGreedy();
	std::vector<int>* solveTspWithBacktracking();
	std::vector<int>* solveTspWithGeneticAlgorithm();

private:
	int** adjacencyMatrix;
	int startingPoint = -1;
	bool init = false;

};

#endif /* TSP_SOLVER_H */
