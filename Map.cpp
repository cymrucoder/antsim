#include "Map.h"

Map::Map(int noOfNodes, EnvironmentBehaviour *enviroBeh)
{
    edges = new EdgeArray(noOfNodes);

    // Need to separate the map generation code into another class

    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_real_distribution<float> randCoord(0.0f, 800.f);// Assuming the screen is 800px wide and high, works for now

    for (int i = 0; i < noOfNodes; i++)
    {
        nodes.push_back(new Node(randCoord(mt), randCoord(mt), 0.0f));
    }

    for (int i = 0; i < noOfNodes; i++)
    {
        for (int j = 0; j < noOfNodes; j++)
        {
            if (i < j)
            {
                createEdge(i, j);
            }
        }
    }

     for (int i = 0; i < noOfNodes; i++)
    {
        ants.push_back(Ant(i, edges, new MoveAntSystem(edges, 1.0f, 1.0f), new PheromoneAntSystem(edges, 1.0f)));
    }

    enviroBeh->init(edges);// I don't like this way of doing it but it works for now (problem is AntSim doesn't know about *edges[] so can't pass it to PAS())
    this->enviroBeh = enviroBeh;

}

void Map::createEdge(int nodeA, int nodeB)
{
    float distance = sqrt(  pow((nodes.at(nodeA)->getCoord(COORD_X) - nodes.at(nodeB)->getCoord(COORD_X)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Y) - nodes.at(nodeB)->getCoord(COORD_Y)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Z) - nodes.at(nodeB)->getCoord(COORD_Z)), 2.0f));

    edges->addEdge(nodeA, nodeB, distance, 1.0f);// Last argument needs to be default phero level whenever I add that
}

void Map::runIteration()// Runs a single iteration of the search (that is, until each Ant reaches its goal)
{
    for (unsigned int i = 0; i < ants.size(); i++)
    {
        ants.at(i).move();
    }

    enviroBeh->updatePheromone();

    for (unsigned int i = 0; i < ants.size(); i++)
    {
        ants.at(i).updatePheromone();
    }
}

