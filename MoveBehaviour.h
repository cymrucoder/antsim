#ifndef _MOVEBEHAVIOUR_H_
#define _MOVEBEHAVIOUR_H_

#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <iostream>
#include "EdgeArray.h"

class MoveBehaviour
{
public:

	virtual ~MoveBehaviour();

	virtual int generateMove(std::vector<int> *tabuList) = 0;
};


#endif // _MOVEBEHAVIOUR_H_

