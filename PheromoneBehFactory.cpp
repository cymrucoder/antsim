#include "PheromoneBehFactory.h"

PheromoneBehFactory::PheromoneBehFactory()
{

}

PheromoneBehaviour* PheromoneBehFactory::makePheromoneBehaviour(int pheromoneBehType, EdgeArray* edges)
{
    if (pheromoneBehType == PHEROMONE_BEH_TYPE_AS)
    {
        return new PheromoneAntSystem(edges, 1.0f);
    }
    else if (pheromoneBehType == PHEROMONE_BEH_TYPE_MMAS)
    {
        return new PheromoneMaxMinAS(edges, 5.0f);
    }
    else
    {
        return new PheromoneAntSystem(edges, 1.0f);
    }
}
