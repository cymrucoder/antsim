#include "EnvironmentAntSystem.h"

EnvironmentAntSystem::EnvironmentAntSystem()
{

}

void EnvironmentAntSystem::init(EdgeArray* edges)
{
    this->edges = edges;
}

void EnvironmentAntSystem::updatePheromone()
{
    edges->evaporate(0.01f);// evaporationRate needs to be set somewhere (pass in value in constructor?)
}
