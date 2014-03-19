#ifndef _MOVEANTSYSTEM_H_
#define _MOVEANTSYSTEM_H_

#include "../../MoveBehaviour.h"

class MoveAntSystem : public MoveBehaviour
{
public:

    MoveAntSystem(EdgeArray *edges, float importancePhero, float importanceDist);

    int generateMove(std::vector<int> *tabuList);

    void updateParams(struct paramData *data);

private:

    EdgeArray *edges;

    float importancePhero, importanceDist;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_real_distribution<float> distFloat;
};

#endif // _MOVEANTSYSTEM_H_
