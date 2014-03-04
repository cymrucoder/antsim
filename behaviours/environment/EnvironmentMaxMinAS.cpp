#include "EnvironmentMaxMinAS.h"

EnvironmentMaxMinAS::EnvironmentMaxMinAS(float pheroMin, EdgeArray *edges)
{
    this->pheroMin = pheroMin;

    this->edges = edges;

    howManyAntsUpdate = 1;// If you put this bool elsewhere you could probably wouldn't need this class
}

void EnvironmentMaxMinAS::updatePheromone()
{
    edges->evaporate(0.7f, pheroMin);
}
