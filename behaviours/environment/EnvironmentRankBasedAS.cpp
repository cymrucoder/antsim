#include "EnvironmentRankBasedAS.h"

EnvironmentRankBasedAS::EnvironmentRankBasedAS(EdgeArray *edges, float evapRate, int numberOfAntsThatUpdate, int numberOfElitistAnts)
{
    this->edges = edges;

    this->evapRate = evapRate;
    this->numberOfAntsThatUpdate = numberOfAntsThatUpdate;
    this->numberOfElitistAnts = numberOfElitistAnts;

    lengthOfBestPathSoFar = INFINITY;
}

void EnvironmentRankBasedAS::updatePheromone()
{
    edges->evaporate(evapRate);
}

void EnvironmentRankBasedAS::processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts)
{
    // Generates list of best n ants

    Ant *antTemp;

    for (unsigned int i = 0; i < ants->size() - 1; i++)// Quicksort, probably better way of doing it (and this whole thing actually) but this works for now
    {
        for (unsigned int j = 0; j < ants->size() - 1; j++)
        {
            if (ants->at(j)->getLengthOfPath() > ants->at(j + 1)->getLengthOfPath())
            {
                antTemp = ants->at(j);
                ants->at(j) = ants->at(j + 1);
                ants->at(j + 1) = antTemp;
            }
        }
    }

    for (int i = 0; i < numberOfAntsThatUpdate; i++)
    {
        processedAnts->push_back(ants->at(i));// Add best (numbersOfAntsThatUpdate) ants
    }

    if (ants->at(0)->getLengthOfPath() < lengthOfBestPathSoFar)// Keep track of best path for elitism
    {
        lengthOfBestPathSoFar = ants->at(0)->getLengthOfPath();
        nodesOfBestPathSoFar = ants->at(0)->getNodesVisited();
    }

    for (unsigned int i = 0; i < nodesOfBestPathSoFar.size() - 1; i++)// Elitism
    {
        edges->incrementPheromone(nodesOfBestPathSoFar.at(i), nodesOfBestPathSoFar.at(i + 1), 1.0f / lengthOfBestPathSoFar);
    }
}

void EnvironmentRankBasedAS::updateParams(struct paramData *data)
{
    evapRate = data->evapRate;
    numberOfAntsThatUpdate = data->noOfRankedAnts;
    numberOfElitistAnts = data->noOfElitistAnts;
}
