#include "Ant.h"
#include "Map.h"
#include <vector>
#include <iostream>

#define NO_OF_NODES 31

int main(void)
{
    float shortestKnownPath = INFINITY;

    /*std::cout << "Generating map" << std::endl;

    Map map = Map(NO_OF_NODES, new PheromoneAntSystem());

    std::cout << "Map generation finished, printing edges" << std::endl;

    for (int i = 0; i < NO_OF_NODES; i++)
    {
        for (int j = 0; j < NO_OF_NODES; j++)
        {
            if (i < j)
            {
                std::cout << "Edge from node " << i << " to node " << j << " with pheromone level: " << map.edges->getPheromone(i, j) << std::endl;
            }
        }
    }

    for (int iter = 0; iter < 10; iter++) {

        std::cout << "Running iteration" << std::endl;

        for (int i = 0; i < (NO_OF_NODES - 1); i++)
        {
            map.runIteration();// NO_OF_NODES nodes, (NO_OF_NODES - 1) moves
        }

        std::cout << "Printing ant paths" << std::endl;

        for (int i = 0; i < NO_OF_NODES; i++)
        {
            std::cout << "Ant " << i << " took the path:";

            for (unsigned int j = 0; j < map.ants.at(i)->nodesVisited.size(); j++)
            {
                std::cout << " " << map.ants.at(i)->nodesVisited.at(j);
            }

            std::cout << " (Length: " << map.ants.at(i)->getLengthOfPath() << ")" << std::endl;
        }

        std::cout << "Printing updated edges" << std::endl;

        for (int i = 0; i < NO_OF_NODES; i++)
        {
            for (int j = 0; j < NO_OF_NODES; j++)
            {
                if (i < j)
                {
                    std::cout << "Edge from node " << i << " to node " << j << " with pheromone level: " << map.edges->getPheromone(i, j) << std::endl;
                }
            }
        }

        for (int i = 0; i < NO_OF_NODES; i++)
        {
            map.ants.at(i)->reset();
        }
    }*/

    //Map map = Map(NO_OF_NODES, new EnvironmentAntSystem());
    //Map map = Map(NO_OF_NODES, new EnvironmentMaxMinAS(0.5f));
    Map map = Map(NO_OF_NODES, new EnvironmentRankBasedAS(14, 1));

    for (int iter = 0; iter < 2500; iter++)
    {
        /*std::cout << "Iteration " << iter << std::endl;

        for (int i = 0; i < NO_OF_NODES; i++)
        {
            for (int j = 0; j < NO_OF_NODES; j++)
            {
                if (i < j)
                {
                    std::cout << "Edge from node " << i << " to node " << j << " with pheromone level: " << map.edges->getPheromone(i, j) << std::endl;
                }
            }
        }
        */

        for (int i = 0; i < (NO_OF_NODES - 1); i++)
        {
            map.runIteration();// NO_OF_NODES nodes, (NO_OF_NODES - 1) moves
        }

        for (unsigned int i = 0; i < map.ants.size(); i++)
        {
            float actualLengthA = map.ants.at(i)->getLengthOfPath() + (map.edges->getLength(map.ants.at(i)->nodesVisited.at(0), map.ants.at(i)->nodesVisited.back()));// Move from final node to start node not accounted for ATM,

            /*std::cout << "Ant " << i << " took path:";

            for (unsigned int j = 0; j < map.ants.at(i)->nodesVisited.size(); j++)
            {
                std::cout << " " << map.ants.at(i)->nodesVisited.at(j);
            }

            std::cout << std::endl;*/

            if (actualLengthA < shortestKnownPath)
            {
                shortestKnownPath = actualLengthA;
                std::cout << "New shortest path, length: " << shortestKnownPath << " (iteration: " << iter << "):";

                for (unsigned int j = 0; j < map.ants.at(i)->nodesVisited.size(); j++)
                {
                    std::cout << " " << map.ants.at(i)->nodesVisited.at(j);
                }
                std::cout << std::endl;

                for (unsigned int j = 0; j < map.ants.at(i)->nodesVisited.size(); j++)
                {

                }
            }
            map.ants.at(i)->reset();
        }
    }
    return 0;
}
