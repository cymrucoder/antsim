#ifndef _ENVIRONMENTBEHAVIOUR_H_
#define _ENVIRONMENTBEHAVIOUR_H_

#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>
#include "EdgeArray.h"
#include "Ant.h"
#include "ParamData.h"

class EnvironmentBehaviour
{
public:

	virtual ~EnvironmentBehaviour();

	virtual void updatePheromone() = 0;

    //int getHowManyAntsUpdate();

    virtual void processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts);

    virtual void updateParams(struct paramData *data) = 0;

//protected:

    //int howManyAntsUpdate;

};

#endif // _ENVIRONMENTBEHAVIOUR_H_
