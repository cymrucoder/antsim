#include "EdgeArray.h"

EdgeArray::EdgeArray(int noOfNodes)
{
    this->noOfNodes = noOfNodes;

	edgeLengths = new float*[noOfNodes];
	edgePheromones = new float*[noOfNodes];

	for (int i = 0; i < noOfNodes; i++)
	{
	    edgeLengths[i] = new float[noOfNodes];
	    edgePheromones[i] = new float[noOfNodes];

	    for (int j = 0; j < noOfNodes; j++)
	    {
	        edgeLengths[i][j] = -1.0f;
	        edgePheromones[i][j] = -1.0f;
	    }
	}
}

void EdgeArray::addEdge(int nodeA, int nodeB, float distance, float pheromoneLevel)
{
    if (distance >= 0.0f && pheromoneLevel >= 0.0f)// Check if nodeA and nodeB are within the array limits (and not the same node)?
    {
        edgeLengths[nodeA][nodeB] = distance;
        edgePheromones[nodeA][nodeB] = pheromoneLevel;
        edgeLengths[nodeB][nodeA] = distance;// Have to mirror array so can lookup from either direction
        edgePheromones[nodeB][nodeA] = pheromoneLevel;
    }
}

int EdgeArray::getNoOfNodes()
{
    return noOfNodes;
}

float EdgeArray::getLength(int nodeA, int nodeB)
{
    return edgeLengths[nodeA][nodeB];
}

float EdgeArray::getPheromone(int nodeA, int nodeB)
{
    return edgePheromones[nodeA][nodeB];
}

void EdgeArray::evaporate(float evaporationRate)// Minimum value phero can go to?
{
    if (evaporationRate > 0.0f && evaporationRate <= 1.0f)
    {
        float leftAfterEvaporation = 1.0 - evaporationRate;

        for (int i = 0; i < noOfNodes; i++)
        {
            for (int j = 0; j < noOfNodes; j++)
            {
                if (edgePheromones[i][j] > 0.0f)// Only update edges that exist (and aren't zero to save some time) (Could easily check min value here)
                {
                    edgePheromones[i][j] *= leftAfterEvaporation;
                }
            }
        }
    }
}

void EdgeArray::incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease)// Max value phero can go to?
{
    if (pheromoneIncrease > 0.0f)
    {
        edgePheromones[nodeA][nodeB] += pheromoneIncrease;
        edgePheromones[nodeB][nodeA] = edgePheromones[nodeA][nodeB];
    }
}
