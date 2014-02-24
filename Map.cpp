#include "Map.h"

Map::Map(int noOfNodes, EnvironmentBehaviour *enviroBeh)
{
    edges = new EdgeArray(noOfNodes);

    // Need to separate the map generation code into another class

    /*std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_real_distribution<float> randCoord(0.0f, 100.f);// Assuming the screen is 100px wide and high, works for now

    for (int i = 0; i < noOfNodes; i++)
    {
        nodes.push_back(new Node(randCoord(mt), randCoord(mt), 0.0f));
    }*/

    nodes.push_back(new Node(54.0f, 67.0f, 0.0f));
    nodes.push_back(new Node(54.0f, 62.0f, 0.0f));
    nodes.push_back(new Node(37.0f, 84.0f, 0.0f));
    nodes.push_back(new Node(41.0f, 94.0f, 0.0f));
    nodes.push_back(new Node(2.0f, 99.0f, 0.0f));
    nodes.push_back(new Node(7.0f, 64.0f, 0.0f));
    nodes.push_back(new Node(25.0f, 62.0f, 0.0f));
    nodes.push_back(new Node(22.0f, 60.0f, 0.0f));
    nodes.push_back(new Node(18.0f, 54.0f, 0.0f));
    nodes.push_back(new Node(4.0f, 50.0f, 0.0f));
    nodes.push_back(new Node(13.0f, 40.0f, 0.0f));
    nodes.push_back(new Node(18.0f, 40.0f, 0.0f));
    nodes.push_back(new Node(24.0f, 42.0f, 0.0f));
    nodes.push_back(new Node(25.0f, 38.0f, 0.0f));
    nodes.push_back(new Node(44.0f, 35.0f, 0.0f));
    nodes.push_back(new Node(41.0f, 26.0f, 0.0f));
    nodes.push_back(new Node(45.0f, 21.0f, 0.0f));
    nodes.push_back(new Node(58.0f, 35.0f, 0.0f));
    nodes.push_back(new Node(62.0f, 32.0f, 0.0f));
    nodes.push_back(new Node(82.0f,  7.0f, 0.0f));
    nodes.push_back(new Node(91.0f, 38.0f, 0.0f));
    nodes.push_back(new Node(83.0f, 46.0f, 0.0f));
    nodes.push_back(new Node(71.0f, 44.0f, 0.0f));
    nodes.push_back(new Node(64.0f, 60.0f, 0.0f));
    nodes.push_back(new Node(68.0f, 58.0f, 0.0f));
    nodes.push_back(new Node(83.0f, 69.0f, 0.0f));
    nodes.push_back(new Node(87.0f, 76.0f, 0.0f));
    nodes.push_back(new Node(74.0f, 78.0f, 0.0f));
    nodes.push_back(new Node(71.0f, 71.0f, 0.0f));
    nodes.push_back(new Node(58.0f, 69.0f, 0.0f));

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
        //ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneAntSystem(edges, 100.0f)));
        ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneMaxMinAS(edges, 4.0f)));
    }

    enviroBeh->init(edges);// I don't like this way of doing it but it works for now (problem is AntSim doesn't know about *edges[] so can't pass it to PAS())
    this->enviroBeh = enviroBeh;

}

void Map::createEdge(int nodeA, int nodeB)
{
    float distance = sqrt(  pow((nodes.at(nodeA)->getCoord(COORD_X) - nodes.at(nodeB)->getCoord(COORD_X)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Y) - nodes.at(nodeB)->getCoord(COORD_Y)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Z) - nodes.at(nodeB)->getCoord(COORD_Z)), 2.0f));

    edges->addEdge(nodeA, nodeB, distance, 4.0f);// Last argument needs to be default phero level whenever I add that
}

void Map::runIteration()// Runs a single iteration of the search (that is, until each Ant reaches its goal)
{
    for (unsigned int i = 0; i < ants.size(); i++)
    {
        ants.at(i)->move();
    }

    enviroBeh->updatePheromone();

    int howManyAntsUpdate = enviroBeh->getHowManyAntsUpdate();// Could just set this to ants.size() if it returns 0 but might want to add negatives or something for stuff later

    if (howManyAntsUpdate > 0)// Used when the algorithm only lets certain ants update (usually the ants that found the shortest path)
    {
        // Sort list (I don't think it matters if you just reorder the current ants[] order doesn't really matter)

        Ant *antTemp;

        for (unsigned int i = 0; i < ants.size() - 1; i++)// Quicksort, probably better way of doing it
        {
            for (unsigned int j = 0; j < ants.size() - 1; j++)
            {
                if (ants.at(j)->getLengthOfPath() > ants.at(j + 1)->getLengthOfPath())
                {
                    antTemp = ants.at(j);
                    ants.at(j) = ants.at(j + 1);
                    ants.at(j + 1) = antTemp;
                }
            }
        }

        for (int i = 0; i < howManyAntsUpdate; i++)
        {
            ants.at(i)->updatePheromone();
        }
    }
    else// Used when all ants can update
    {
        for (unsigned int i = 0; i < ants.size(); i++)
        {
            ants.at(i)->updatePheromone();
        }
    }
}

