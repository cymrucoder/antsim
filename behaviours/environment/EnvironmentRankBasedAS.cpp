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
    // Would it be better to just fill up the processedAnts[] with (nOATU) ants, then add new elements if shorter path (and remove longer ones)?  Would have to sort in some way anyway though

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

    //*processedAnts = std::vector<Ant*>(ants->begin(), ants->begin() + numberOfAntsThatUpdate);// This should work but want to be more specific for now

    for (int i = 0; i < numberOfAntsThatUpdate; i++)// Need to make sure nOATU < ants.size() somewhere
    {
        processedAnts->push_back(ants->at(i));// Add best (numbersOfAntsThatUpdate) ants
    }

    /*for (int i = 0; i < numberOfElitistAnts; i++)
    {
        processedAnts->push_back(ants->at(0));// Add (numberOfElitistAnts) elitist ants (ants that follow the best path so far)// CURRENTLY THIS IS JUST THE BEST OF THE ITERATION NEED TO FIX
    }*/

    // This should work too and saves creating and storing a new Ant here (would that be simpler?  I'm not sure)

    if (ants->at(0)->getLengthOfPath() < lengthOfBestPathSoFar)
    {
        lengthOfBestPathSoFar = ants->at(0)->getLengthOfPath();
        nodesOfBestPathSoFar = ants->at(0)->getNodesVisited();
    }

    for (unsigned int i = 0; i < nodesOfBestPathSoFar.size() - 1; i++)
    {
        edges->incrementPheromone(nodesOfBestPathSoFar.at(i), nodesOfBestPathSoFar.at(i + 1), 1.0f / lengthOfBestPathSoFar);// Should the numerator be 1 or changable?  Need to double check paper
    }
}

void EnvironmentRankBasedAS::updateParams(struct paramData *data)
{
    evapRate = data->evapRate;
    numberOfAntsThatUpdate = data->noOfRankedAnts;
    numberOfElitistAnts = data->noOfElitistAnts;
}
