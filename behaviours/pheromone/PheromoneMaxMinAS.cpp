#include "PheromoneMaxMinAS.h"

PheromoneMaxMinAS::PheromoneMaxMinAS(EdgeArray* edges, float pheroMax)
{
    this->edges = edges;
    this->pheroMax = pheroMax;
}

void PheromoneMaxMinAS::updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath)// Either store pointers or pass them in each time this called (but storing them would be annoying because this is created before the Ant)
{
    for (unsigned int i = 0; i < (nodesVisited->size() - i); i++)// For each edge travelled along...
    {
        edges->incrementPheromone(nodesVisited->at(i), nodesVisited->at(i + 1), (1.0f / lengthOfPath), pheroMax);// Update the pheromone by 1/lOP
    }
}

void PheromoneMaxMinAS::updateParams(struct paramData *data)
{
    pheroMax = data->pheroMax;
}
