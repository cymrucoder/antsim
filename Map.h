#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <math.h>
#include <iostream>
#include "Node.h"
#include "Ant.h"
#include "EdgeArray.h"
#include "RenderableEdge.h"
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

class Map
{
public:

	Map(int noOfNodes, EdgeArray *edges, EnvironmentBehaviour *enviroBeh, bool type);
	~Map();

    void createNode(float x, float y, float z);
    void createEdge(int nodeA, int nodeB);
    void createAnt(int node, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh);

    void setEnvironmentBehaviour(EnvironmentBehaviour *enviroBeh);

	void render();

	std::vector<Ant*> ants;
    std::vector<Ant*> processedAnts;
    std::vector<Node*> nodes;
	EdgeArray *edges;

    EnvironmentBehaviour *enviroBeh;

private:

    std::vector<RenderableEdge*> renderableEdges;

    bool type;
};

#endif // _MAP_H_
