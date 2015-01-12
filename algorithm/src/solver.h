#ifndef SOLVER_H
#define SOLVER_H

#include <stdexcept>
#include <vector>

class Solver {

public:
    virtual void setNumberOfNodes(int nodes) = 0;
    virtual void addPoint(int fromNode, int toNode, double cost) = 0;
    virtual void setStartingPoint(int node) = 0;
    virtual void setGroupForNode(int node, int group) = 0;
    virtual std::vector<int>* solve() = 0;

};

#endif /* SOLVER_H */
