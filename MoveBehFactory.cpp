#include "MoveBehFactory.h"

MoveBehFactory::MoveBehFactory()
{

}

MoveBehaviour* MoveBehFactory::makeMoveBehaviour(int moveBehaviourType, EdgeArray* edges)
{
    if (moveBehaviourType == MOVE_BEH_TYPE_AS)
    {
        return new MoveAntSystem(edges, 1.0f, 5.0f);
    }
    else
    {
        return new MoveAntSystem(edges, 1.0f, 5.0f);
    }
}
