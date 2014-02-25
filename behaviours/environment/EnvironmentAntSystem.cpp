#include "EnvironmentAntSystem.h"

EnvironmentAntSystem::EnvironmentAntSystem()
{
    howManyAntsUpdate = 0;
}

void EnvironmentAntSystem::init(EdgeArray* edges)
{
    this->edges = edges;
}

void EnvironmentAntSystem::updatePheromone()
{
    edges->evaporate(0.7f);// evaporationRate needs to be set somewhere (pass in value in constructor?)
}
