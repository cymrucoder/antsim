#ifndef _PHEROMONEANTSYSTEM_H_
#define _PHEROMONEANTSYSTEM_H_

#include "../../PheromoneBehaviour.h"

class PheromoneAntSystem : public PheromoneBehaviour
{
public:

	PheromoneAntSystem(EdgeArray* edges, float constNumerator);

	void updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath);

private:

    EdgeArray* edges;
    float constNumerator;

};

#endif // _PHEROMONEANTSYSTEM_H_
