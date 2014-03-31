#ifndef _MOVEBEHFACTORY_H_
#define _MOVEBEHFACTORY_H_

#include "behaviours/move/MoveAntSystem.h"

#define MOVE_BEH_TYPE_AS 0

class MoveBehFactory
{
public:

    MoveBehFactory();

    MoveBehaviour* makeMoveBehaviour(int moveBehaviourType, EdgeArray* edges);
};

#endif // _MOVEBEHFACTORY_H_
