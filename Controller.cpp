#include "Controller.h"

Controller::Controller(int noOfNodes)
{
    //this->noOfNodes = noOfNodes;
    map = generateMap(noOfNodes);

    shortestKnownPath = INFINITY;
}

void Controller::run(int maxIterations)
{
    for (int i = 0; i < maxIterations; i++)
    {
        runIteration();
    }
}

void Controller::runIteration()
{
    for (unsigned int i = 0; i < map->ants.size(); i++)
    {
        map->ants.at(i)->move();
    }

    map->enviroBeh->updatePheromone();

    /*int howManyAntsUpdate = map->enviroBeh->getHowManyAntsUpdate();// Could just set this to ants.size() if it returns 0 but might want to add negatives or something for stuff later

    if (howManyAntsUpdate > 0)// Used when the algorithm only lets certain ants update (usually the ants that found the shortest path)
    {
        // Sort list (I don't think it matters if you just reorder the current ants[] order doesn't really matter)

        Ant *antTemp;

        for (unsigned int i = 0; i < map->ants.size() - 1; i++)// Quicksort, probably better way of doing it
        {
            for (unsigned int j = 0; j < map->ants.size() - 1; j++)
            {
                if (map->ants.at(j)->getLengthOfPath() > map->ants.at(j + 1)->getLengthOfPath())
                {
                    antTemp = map->ants.at(j);
                    map->ants.at(j) = map->ants.at(j + 1);
                    map->ants.at(j + 1) = antTemp;
                }
            }
        }*/

    map->enviroBeh->processAntList(&map->ants, &map->processedAnts);// enviroBeh generates new list of ants that are able to update

    for (unsigned int i = 0; i < map->processedAnts.size(); i++)
    {
        map->processedAnts.at(i)->updatePheromone();
    }

    map->processedAnts.clear();
    //}
    /*else// Used when all ants can update
    {
        for (unsigned int i = 0; i < map->ants.size(); i++)
        {
            map->ants.at(i)->updatePheromone();
        }
    }*/

    for (unsigned int i = 0; i < map->ants.size(); i++)
    {
        float actualLengthA = map->ants.at(i)->getLengthOfPath() + (map->edges->getLength(map->ants.at(i)->nodesVisited.at(0), map->ants.at(i)->nodesVisited.back()));// Move from final node to start node not accounted for ATM,

        if (actualLengthA < shortestKnownPath)
        {
            shortestKnownPath = actualLengthA;
            //std::cout << "New shortest path, length: " << shortestKnownPath << " (iteration: " << iter << "):";

            for (unsigned int j = 0; j < map->ants.at(i)->nodesVisited.size(); j++)
            {
                std::cout << " " << map->ants.at(i)->nodesVisited.at(j);
            }
            //std::cout << std::endl;

            for (unsigned int j = 0; j < map->ants.at(i)->nodesVisited.size(); j++)
            {

            }
        }
        map->ants.at(i)->reset();
    }
}

void Controller::regenerateMap()
{

}

void Controller::regenerateMap(int noOfNodes)
{

}

Map* Controller::generateMap(int noOfNodes, char type)
{
    EdgeArray *tempEdges = new EdgeArray(noOfNodes);// Would prefer to create this inside Map but if it's here than the behaviours can use it easier

    Map *mapTemp = new Map(noOfNodes, tempEdges, new EnvironmentMaxMinAS(0.5f, tempEdges));

    if (type == MAPTYPE_TSP_RANDOM)// Generate random map for TSP type problem
    {
        std::random_device rd;
        std::mt19937 mt = std::mt19937(rd());
        std::uniform_real_distribution<float> randCoord(-5.0f, 5.0f);// Assuming the screen is 100px wide and high, works for now

        for (int i = 0; i < noOfNodes; i++)// Create set of random nodes
        {
            mapTemp->createNode(randCoord(mt), 0.0f, randCoord(mt));
        }

        for (int i = 0; i < noOfNodes; i++)// Create edges between all nodes
        {
            for (int j = 0; j < noOfNodes; j++)
            {
                if (i < j)// Only create one edge for each pair of nodes
                {
                    mapTemp->createEdge(i, j);
                }
            }
        }

        for (int i = 0; i < noOfNodes; i++)
        {
            //ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneAntSystem(edges, 100.0f)));
            mapTemp->createAnt(i, new MoveAntSystem(tempEdges, 1.0f, 5.0f), new PheromoneMaxMinAS(tempEdges, 4.0f));
        }
    }
    else if (type == MAPTYPE_TSP_LOADED)// Load nodes for TSP type problem from file
    {
        // Load nodes
    }
    else if (type == MAPTYPE_MAZE_RANDOM)// Generate random maze
    {
        // Generate maze
    }
    else if (type == MAPTYPE_MAZE_LOADED)// Load maze from file
    {
        // Load maze
    }

    return mapTemp;
}

void Controller::render()
{
    map->render();
}
