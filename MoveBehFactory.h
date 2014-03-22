#ifndef _MOVEBEHFACTORY_H_
#define _MOVEBEHFACTORY_H_

#include "behaviours/move/MoveAntSystem.h"

#define MOVE_BEH_TYPE_AS 0

class MoveBehFactory
{
	public:
		MoveBehFactory();
		//~MoveBehFactory();

		MoveBehaviour* makeMoveBehaviour(int moveBehaviourType, EdgeArray* edges);

	private:

};

#endif // _MOVEBEHFACTORY_H_
