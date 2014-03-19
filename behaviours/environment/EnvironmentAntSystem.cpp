#include "EnvironmentAntSystem.h"

EnvironmentAntSystem::EnvironmentAntSystem(EdgeArray *edges, float evapRate)
{
    this->edges = edges;
    this->evapRate = evapRate;
}

void EnvironmentAntSystem::updatePheromone()
{
    edges->evaporate(evapRate);
}

void EnvironmentAntSystem::updateParams(struct paramData *data)
{
    evapRate = data->evapRate;
}
