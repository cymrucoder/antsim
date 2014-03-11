#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Map.h"
#include <fstream>
#include <string>
#include <queue>

class Controller
{
public:

	Controller(int noOfNodes, char type = MAPTYPE_TSP_RANDOM);

	void run(int maxIterations);
	void runIteration();

    void regenerateMap();
	void regenerateMap(int noOfNodes);

	void generateMap(int noOfNodes, EdgeArray *edges, char type = MAPTYPE_TSP_RANDOM);

	void render();

private:

    Map *map;

    //int noOfNodes;
    int maxIterations;

    float shortestKnownPath;
};

#endif // _CONTROLLER_H_
