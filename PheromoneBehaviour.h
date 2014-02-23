#ifndef _PHEROMONEBEHAVIOUR_H_
#define _PHEROMONEBEHAVIOUR_H_

#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>
#include "EdgeArray.h"

class PheromoneBehaviour
{
public:

	virtual ~PheromoneBehaviour();

	virtual void updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath) = 0;

private:

};

#endif // _PHEROMONEBEHAVIOUR_H_
