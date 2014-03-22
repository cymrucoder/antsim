#include "EnvironmentBehFactory.h"

EnvironmentBehFactory::EnvironmentBehFactory()
{

}

EnvironmentBehaviour* EnvironmentBehFactory::makeEnvironmentBehaviour(int environmentBehaviourType, EdgeArray *edges)
{
    // Should probably make these switches
    if (environmentBehaviourType == ENVIRONMENT_BEH_TYPE_AS)
    {
        return new EnvironmentAntSystem(edges, 0.7f);
    }
    else if (environmentBehaviourType == ENVIRONMENT_BEH_TYPE_AS)
    {
        return new EnvironmentMaxMinAS(edges, 0.7f, 0.5f);// Min phero
    }
    else if (environmentBehaviourType == ENVIRONMENT_BEH_TYPE_AS)
    {
        return new EnvironmentRankBasedAS(edges, 0.7f, 4, 4);// Ranked ants, elitist ants
    }
    else
    {
        return new EnvironmentAntSystem(edges, 0.7f);
    }
}
