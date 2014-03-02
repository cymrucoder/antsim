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

    int howManyAntsUpdate = map->enviroBeh->getHowManyAntsUpdate();// Could just set this to ants.size() if it returns 0 but might want to add negatives or something for stuff later

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
        }

        for (int i = 0; i < howManyAntsUpdate; i++)
        {
            map->ants.at(i)->updatePheromone();
        }
    }
    else// Used when all ants can update
    {
        for (unsigned int i = 0; i < map->ants.size(); i++)
        {
            map->ants.at(i)->updatePheromone();
        }
    }

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

Map* Controller::generateMap(int noOfNodes)
{
    Map *mapTemp = new Map(noOfNodes, new EnvironmentMaxMinAS(0.5f));

    return mapTemp;
}

void Controller::render()
{
    map->render();
}
