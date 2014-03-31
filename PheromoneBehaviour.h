#ifndef _PHEROMONEBEHAVIOUR_H_
#define _PHEROMONEBEHAVIOUR_H_

#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>
#include "EdgeArray.h"
#include "ParamData.h"

class PheromoneBehaviour
{
public:

	virtual ~PheromoneBehaviour();

	virtual void updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath) = 0;

	virtual void updateParams(struct paramData *data) = 0;
};

#endif // _PHEROMONEBEHAVIOUR_H_
