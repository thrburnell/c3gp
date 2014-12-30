#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>


class TspSolver {
public:
	virtual ~TspSolver() {};

	void addPoint(int firstNode, int secondNode, int cost);
	void setStartingPoint(int node);

	std::vector<int>* solveTsp();

	std::vector<int>* solveTspWithGreedy();
};

#endif /* TSP_SOLVER_H */
