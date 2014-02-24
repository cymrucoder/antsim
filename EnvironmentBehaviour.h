#ifndef _ENVIRONMENTBEHAVIOUR_H_
#define _ENVIRONMENTBEHAVIOUR_H_

#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>
#include "EdgeArray.h"

class EnvironmentBehaviour
{
public:

	virtual ~EnvironmentBehaviour();

	virtual void init(EdgeArray *edges) = 0;

	virtual void updatePheromone() = 0;

    int getHowManyAntsUpdate();

protected:

    int howManyAntsUpdate;

};


#endif // _ENVIRONMENTBEHAVIOUR_H_
