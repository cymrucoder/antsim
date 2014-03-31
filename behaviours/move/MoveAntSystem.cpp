#include "MoveAntSystem.h"

MoveAntSystem::MoveAntSystem(EdgeArray *edges, float importancePhero, float importanceDist)
{
    this->edges = edges;
    this->importancePhero = importancePhero;
    this->importanceDist = importanceDist;

    mt = std::mt19937(rd());
}

int MoveAntSystem::generateMove(std::vector<int> *nodesVisited)
{
    float totalProbability = 0.0f;
    int currentNode = nodesVisited->back();

    std::vector<int> validNodes;

    for (int i = 0; i < edges->getNoOfNodes(); i++)// Creates vector of reachable (connected to current node by each) nodes not on the ant's tabu list
    {
        if (edges->getLength(currentNode, i) >= 0.0f && std::find(nodesVisited->begin(), nodesVisited->end(), i) == nodesVisited->end())// Length < 0 => no connecting edge
        {
            validNodes.push_back(i);
        }
    }

    if (validNodes.size() == 0)// If all neighbouring nodes have been visited, allow movement to any neighbouring node
    {
        for (int i = 0; i < edges->getNoOfNodes(); i++)
        {
            if (edges->getLength(currentNode, i) >= 0.0f)// Length < 0 => no connecting edge
            {
                validNodes.push_back(i);
            }
        }
    }

    std::vector<float> probabilities;

    for (unsigned int i = 0; i < validNodes.size(); i++)// Loops through non tabu nodes to generate numerators and adds each to the total totalProbabilityinator
    {
        probabilities.push_back((pow(edges->getPheromone(currentNode, validNodes.at(i)), importancePhero) * pow((1.0f / edges->getLength(currentNode, validNodes.at(i))), importanceDist)));
        totalProbability += probabilities.at(i);
    }

    if (totalProbability > 0.0f)// If all pheromone levels are 0, all nodes have 0 probability so need to work around that
    {
        std::uniform_real_distribution<float> distFloat = std::uniform_real_distribution<float>(0.0f, totalProbability);// Range of [0.0f, totalProbability)
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
        return validNodes.back();// Shouldn't reach here but in case of float inprecision
    }
    else
    {
        std::uniform_int_distribution<unsigned int> distInt = std::uniform_int_distribution<unsigned int>(0, validNodes.size() - 1);
        return validNodes.at(distInt(mt));// Return random node if they all have 0 probability (would always return the first node using the above method)
    }
}

void MoveAntSystem::updateParams(struct paramData *data)
{
    importancePhero = data->importancePhero;
    importanceDist = data->importanceDistance;
}
