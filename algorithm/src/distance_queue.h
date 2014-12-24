#ifndef DISTANCE_QUEUE_H
#define DISTANCE_QUEUE_H

#include "haversine.h"

#include <queue>
#include <vector>
#include <memory>

class distance_queue {

public:
    distance_queue(Coordinate point) :
    compare_with_target(point), queue(compare_with_target) {
    }

    void push(const Coordinate& point) {
        queue.push(point);
        if(queue.size() > kPointLimit) {
            queue.pop();
        }
    }

    std::vector<Coordinate> finish() {
        std::vector<Coordinate> result(queue.size());
        for(int i = result.size() - 1; i >= 0; --i) {
            result[i] = queue.top();
            queue.pop();
        }
        return result;
    }

private:
    // Number of points closest to the input point we wish to hold on to
    static const int kPointLimit = 3;
    
    class dist_comp {
        Coordinate point;

    public:
        dist_comp(Coordinate target_point) : point(target_point) {
        }

        bool operator() (const Coordinate& lhs, const Coordinate& rhs) {
            return calculate_distance(point, lhs) <
                calculate_distance(point, rhs);
        }
    };

    dist_comp compare_with_target;
    std::priority_queue<Coordinate, std::vector<Coordinate>, dist_comp> queue;

};

#endif /* DISTANCE_QUEUE_H */