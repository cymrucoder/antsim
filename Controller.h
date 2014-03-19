#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Map.h"
#include "ParamData.h"
#include <fstream>
#include <string>
#include <queue>

class Controller
{
public:

	Controller(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE);

	void run(int maxIterations);
	void runIteration();

	void updateParams(struct paramData *data);

	void regenerateMap(int noOfNodes, bool type, bool load);

	Map* generateMap(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE);

	void render();

private:

    Map *map;

    //int noOfNodes;
    int maxIterations;

    float shortestKnownPath;
};

#endif // _CONTROLLER_H_
