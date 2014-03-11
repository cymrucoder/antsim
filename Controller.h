#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Map.h"
#include <fstream>
#include <string>
#include <queue>

struct paramData
{
    float importancePhero;
    float importanceDistance;
    float evapRate;
    float pheroNumerator;

    int noOfElitistAnts;
    int noOfRankedAnts;
    float pheroMax;
    float pheroMin;
};

class Controller
{
public:

	Controller(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE);

	void run(int maxIterations);
	void runIteration();

	void updateParams(struct paramData *data);

    void regenerateMap(); // Maybe won't need these two
	void regenerateMap(int noOfNodes);

	Map* generateMap(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE);

	void render();

private:

    Map *map;

    //int noOfNodes;
    int maxIterations;

    float shortestKnownPath;
};

#endif // _CONTROLLER_H_
