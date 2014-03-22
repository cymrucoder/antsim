#ifndef _ANT_H_
#define _ANT_H_

#include "MoveBehaviour.h"
#include "PheromoneBehaviour.h"
#include <vector>
#include "Node.h"
#include "Renderer.h"
#include "ParamData.h"

class Ant
{
public:

    Ant(int nodeCurrent, EdgeArray *edges, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh);
    ~Ant();

    void move();
    void updatePheromone();

    int nodeCurrent;// Should be in private but here for debug purposes
    std::vector<int> nodesVisited;// Same

    float getLengthOfPath();
    std::vector<int> getNodesVisited();

    void setMoveBehaviour(MoveBehaviour *moveBeh);
    void setPheromoneBehaviour(PheromoneBehaviour *pheroBeh);
    void updateParams(struct paramData *data);

    void reset();
    void reset(int nodeNew);

    void render();

private:

    MoveBehaviour *moveBeh;
    PheromoneBehaviour *pheroBeh;
    float lengthOfPath;
    EdgeArray *edges;

    Renderer *renderer;
};

#endif // _ANT_H_
