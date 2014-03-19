#include "PheromoneAntSystem.h"

PheromoneAntSystem::PheromoneAntSystem(EdgeArray* edges, float constNumerator)
{
    this->edges = edges;
    this->constNumerator = constNumerator;
}

void PheromoneAntSystem::updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath)// Either store pointers or pass them in each time this called (but storing them would be annoying because this is created before the Ant)
{
    for (unsigned int i = 0; i < (nodesVisited->size() - i); i++)// For each edge travelled along...
    {
        edges->incrementPheromone(nodesVisited->at(i), nodesVisited->at(i + 1), (constNumerator / lengthOfPath));// Update the pheromone by cN/lOP
    }
}

void PheromoneAntSystem::updateParams(struct paramData *data)
{
    constNumerator = data->pheroNumerator;
}
