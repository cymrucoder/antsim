#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Map.h"
#include "ParamData.h"
#include <fstream>
#include <string>
#include <queue>
#include "MoveBehFactory.h"
#include "PheromoneBehFactory.h"
#include "EnvironmentBehFactory.h"

class Controller
{
public:

	Controller(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE, int sourceNode = 0, int destinationNode = 0);

	void runIteration(bool maptype = MAPTYPE_TSP);

    void updateMoveBehaviour(int moveBehaviourType);
    void updatePheromoneBehaviour(int pheromoneBehaviourType);
    void updateEnvironmentBehaviour(int environmentBehaviourType);
	void updateParams(struct paramData *data);

	void regenerateMap(int noOfNodes, bool type, bool load);
	Map* generateMap(int noOfNodes, bool type = MAPTYPE_TSP, bool load = MAP_GENERATE);

	void render();

    int iteration;
    int maxIterations;

	float shortestKnownPath;

	struct timespec spec, specend;
    unsigned long long int totalTime;

    Map *map;

private:

    MoveBehFactory moveBehFactory;
    PheromoneBehFactory pheromoneBehFactory;
    EnvironmentBehFactory environmentBehFactory;

    int sourceNode, destinationNode;
};

#endif // _CONTROLLER_H_
