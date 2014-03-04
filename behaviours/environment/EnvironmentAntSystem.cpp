#include "EnvironmentAntSystem.h"

EnvironmentAntSystem::EnvironmentAntSystem(EdgeArray *edges)
{
    this->edges = edges;
}

void EnvironmentAntSystem::updatePheromone()
{
    edges->evaporate(0.7f);// evaporationRate needs to be set somewhere (pass in value in constructor?)
}
