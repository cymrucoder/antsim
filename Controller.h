#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Map.h"

class Controller
{
public:

	Controller(int noOfNodes);

	void run(int maxIterations);
	void runIteration();

    void regenerateMap();
	void regenerateMap(int noOfNodes);

	Map* generateMap(int noOfNodes);

private:

    Map *map;

    //int noOfNodes;
    int maxIterations;

    float shortestKnownPath;
};

#endif // _CONTROLLER_H_
