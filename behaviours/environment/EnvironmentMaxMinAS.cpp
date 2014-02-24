#include "EnvironmentMaxMinAS.h"

EnvironmentMaxMinAS::EnvironmentMaxMinAS(float pheroMin)
{
    this->pheroMin = pheroMin;

    howManyAntsUpdate = 1;// If you put this bool elsewhere you could probably wouldn't need this class
}

void EnvironmentMaxMinAS::init(EdgeArray* edges)
{
    this->edges = edges;
}

void EnvironmentMaxMinAS::updatePheromone()
{
    edges->evaporate(0.7f, pheroMin);
}
