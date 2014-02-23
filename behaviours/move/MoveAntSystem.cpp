#include "MoveAntSystem.h"

MoveAntSystem::MoveAntSystem(EdgeArray *edges, float importancePhero, float importanceDist)
{
    this->edges = edges;
    this->importancePhero = importancePhero;
    this->importanceDist = importanceDist;

    mt = std::mt19937(rd());
}

// Comment the actual equation in here for clarity?

int MoveAntSystem::generateMove(std::vector<int> *nodesVisited)
{
    float denom = 0.0f;
    int currentNode = nodesVisited->back();

    std::vector<int> validNodes;

    for (int i = 0; i < edges->getNoOfNodes(); i++)// Creates vector of reachable (connected to current node by each) nodes not on the ant's tabu list
    {
        if (edges->getLength(currentNode, i) >= 0.0f && std::find(nodesVisited->begin(), nodesVisited->end(), i) == nodesVisited->end())// Length < 0 => no connecting edge
        {
            validNodes.push_back(i);
        }

    }

    std::vector<float> probabilities;

    for (unsigned int i = 0; i < validNodes.size(); i++)// Loops through non tabu nodes to generate numerators and adds each to the total denominator
    {
        probabilities.push_back((pow(edges->getPheromone(currentNode, validNodes.at(i)), importancePhero) * pow((1.0f / edges->getLength(currentNode, validNodes.at(i))), importanceDist)));
        denom += probabilities.at(i);
    }

    distFloat = std::uniform_real_distribution<float>(0.0f, denom);// Range of [0.0f, denom)
    float randomNumber = distFloat(mt);

    float runningCount = 0.0f;// Add probabilities to rC, when rC > rN use that node

    for (unsigned int i = 0; i < probabilities.size(); i++)
    {
        runningCount += probabilities.at(i);
        if (runningCount >= randomNumber)
        {
            return validNodes.at(i);
        }
    }
    return -1;
    // This would probably break if the pheromone to each was 0 (checking rC against rN is now >= which I think should at least make it not break, but it's not a proper fix)
}
