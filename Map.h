#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <math.h>
#include <iostream>
#include "Node.h"
#include "Ant.h"
#include "EdgeArray.h"
#include "Edge.h"
#include "behaviours/move/MoveAntSystem.h"
#include "behaviours/pheromone/PheromoneAntSystem.h"
#include "behaviours/environment/EnvironmentAntSystem.h"
#include "behaviours/pheromone/PheromoneMaxMinAS.h"
#include "behaviours/environment/EnvironmentMaxMinAS.h"
#include "behaviours/environment/EnvironmentRankBasedAS.h"

#define MAP_GENERATE 0
#define MAP_LOAD 1

#define MAPTYPE_TSP 0
#define MAPTYPE_MAZE 1

// Maybe move above defs to Controller.h

class Map
{
public:

	Map(int noOfNodes, EdgeArray *edges, EnvironmentBehaviour *enviroBeh);
	~Map();

    void createNode(float x, float y, float z);
    void createEdge(int nodeA, int nodeB);
    void createAnt(int node, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh);

	void render();

	std::vector<Ant*> ants;// May move ants, edges and enviroBeh into private and rework access later
    std::vector<Ant*> processedAnts;// Move this to Controller?
	EdgeArray *edges;

    EnvironmentBehaviour *enviroBeh;

private:

    std::vector<Node*> nodes;
    std::vector<Edge*> renderableEdges;


};

#endif // _MAP_H_
