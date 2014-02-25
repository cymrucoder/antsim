#include "EnvironmentMaxMinAS.h"

EnvironmentMaxMinAS::EnvironmentMaxMinAS(float pheroMin)
{
    this->pheroMin = pheroMin;
}

void EnvironmentMaxMinAS::init(EdgeArray* edges)
{
    this->edges = edges;
}

void EnvironmentMaxMinAS::updatePheromone()
{
    edges->evaporate(0.7f, pheroMin);
}

void EnvironmentMaxMinAS::processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts)
{
    //Ant *antWithShortestPath = ants->at(0);

    int indexOfBestAnt = 0;
    float lengthOfBestPathThisIter = INFINITY;

    for (unsigned int i = 0; i < ants->size(); i++)
    {
        if (ants->at(i)->getLengthOfPath() < lengthOfBestPathThisIter)
        {
            indexOfBestAnt = i;
            lengthOfBestPathThisIter = ants->at(i)->getLengthOfPath();
        }
    }

    processedAnts->push_back(ants->at(indexOfBestAnt));
}
