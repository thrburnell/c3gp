#ifndef DISTANCE_QUEUE_H
#define DISTANCE_QUEUE_H

#include "haversine.h"

#include <queue>
#include <vector>
#include <memory>

class DistanceQueue {

public:
    DistanceQueue(Coordinate point, int max_points) :
    point_limit(max_points), compare_with_target(point), 
    queue(compare_with_target) {
        // Sets up a queue to track the max_points closest points to the
        // specified coordinate object.
    }

    void push(const Coordinate& point) {
        queue.push(point);
        if (queue.size() > point_limit) {
            queue.pop();
        }
    }

    std::vector<Coordinate> finish() {
        // Returns a vector of the kPointLimit closest points in sorted order,
        // in ascending order of distance (so result[0] is the closest one).
        std::vector<Coordinate> result(queue.size());
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = queue.top();
            queue.pop();
        }
        return result;
    }

private:
    // Number of points closest to the input point we wish to hold on to
    int point_limit;
    
    class DistComp {
        Coordinate point;

    public:
        DistComp(Coordinate target_point) : point(target_point) {
        }

        bool operator() (const Coordinate& lhs, const Coordinate& rhs) {
            // Queue contains the point_limit closest points but with the
            // furthest point on top. This allows for efficient implementation
            // of push().
            return calculate_distance(point, lhs) <
                calculate_distance(point, rhs);
        }
    };

    DistComp compare_with_target;
    std::priority_queue<Coordinate, std::vector<Coordinate>, DistComp> queue;

};

#endif /* DISTANCE_QUEUE_H */
