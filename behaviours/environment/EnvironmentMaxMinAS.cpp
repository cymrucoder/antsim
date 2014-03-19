#include "EnvironmentMaxMinAS.h"

EnvironmentMaxMinAS::EnvironmentMaxMinAS(EdgeArray *edges, float evapRate, float pheroMin)
{
    this->edges = edges;

    this->evapRate = evapRate;
    this->pheroMin = pheroMin;
}

void EnvironmentMaxMinAS::updatePheromone()
{
    edges->evaporate(evapRate, pheroMin);
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

void EnvironmentMaxMinAS::updateParams(struct paramData *data)
{
    evapRate = data->evapRate;
    pheroMin = data->pheroMin;
}
