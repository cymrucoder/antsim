#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <math.h>
#include <iostream>
#include "Node.h"
#include "Ant.h"
#include "EdgeArray.h"
#include "behaviours/move/MoveAntSystem.h"
#include "behaviours/pheromone/PheromoneAntSystem.h"
#include "behaviours/environment/EnvironmentAntSystem.h"

class Map
{
public:

	Map(int noOfNodes, EnvironmentBehaviour *enviroBehh);// Maybe have another parameter for type (has dead ends or doesn't for TSP), and option param for random seed
	//~Map();

    void createEdge(int nodeA, int nodeB);

	void runIteration();

	std::vector<Ant> ants;// Should be in private but here for debug purposes
	EdgeArray *edges;// Should be in private but here for debug purposes

private:

    std::vector<Node*> nodes;

    EnvironmentBehaviour *enviroBeh;
};

#endif // _MAP_H_
