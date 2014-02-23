#ifndef _ANT_H_
#define _ANT_H_

#include "MoveBehaviour.h"
#include "PheromoneBehaviour.h"
#include <vector>
#include "Node.h"

class Ant
{
public:

    Ant(int nodeCurrent, EdgeArray *edges, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh);
    //~Ant();

    void move();
    void updatePheromone();

    int nodeCurrent;// Should be in private but here for debug purposes
    std::vector<int> nodesVisited;

    float getLengthOfPath();

    void reset();
    void reset(int nodeNew);

private:

    MoveBehaviour *moveBeh;
    PheromoneBehaviour *pheroBeh;
    float lengthOfPath;
    EdgeArray *edges;
};

#endif // _ANT_H_
