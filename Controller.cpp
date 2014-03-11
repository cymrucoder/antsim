#include "Controller.h"

Controller::Controller(int noOfNodes, char type)
{
    if (type == MAPTYPE_TSP_LOADED || type == MAPTYPE_MAZE_LOADED)// Would a type char and loaded/random bool work better?  Maybe.  Also random seed optional (make type non optional or overload or something)
    {
        std::ifstream fileMap;
        fileMap.open("map.txt", std::ios::in);// try/catch?
        if (fileMap.is_open() == true)
        {
            std::string line;
            getline(fileMap, line);// Badly formatted files could break this
            noOfNodes = atoi(line.c_str());
        }
        fileMap.close();
    }
    EdgeArray *edges = new EdgeArray(noOfNodes);// This is messy which I why I liked the old way.  Will decide which to use later
    //map = generateMap(noOfNodes, type);
    map = new Map(noOfNodes, edges, new EnvironmentMaxMinAS(0.5f, edges));
    generateMap(noOfNodes, edges, type);

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

void Controller::generateMap(int noOfNodes, EdgeArray *edges, char type)
{
    //EdgeArray *tempEdges = new EdgeArray(noOfNodes);// Would prefer to create this inside Map but if it's here than the behaviours can use it easier

    //Map *mapTemp = new Map(noOfNodes, tempEdges, new EnvironmentMaxMinAS(0.5f, tempEdges));

    if (type == MAPTYPE_TSP_RANDOM)// Generate random map for TSP type problem
    {
        std::random_device rd;
        std::mt19937 mt = std::mt19937(rd());
        std::uniform_real_distribution<float> randCoord(-5.0f, 5.0f);

        for (int i = 0; i < noOfNodes; i++)// Create set of random nodes
        {
            map->createNode(randCoord(mt), 0.0f, randCoord(mt));
        }

        for (int i = 0; i < noOfNodes; i++)// Create edges between all nodes
        {
            for (int j = 0; j < noOfNodes; j++)
            {
                if (i < j)// Only create one edge for each pair of nodes
                {
                    map->createEdge(i, j);
                }
            }
        }
    }
    else if (type == MAPTYPE_TSP_LOADED)// Load nodes for TSP type problem from file
    {
        std::ifstream fileMap;
        fileMap.open("map.txt", std::ios::in);
        if (fileMap.is_open() == true)
        {
            std::string line;
            int pos = 0;
            int oldPos = -1;

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            /* File should be in format of no. of nodes, then three comma separated floats per line (x,y,z):

            2
            0.5,5.6,4.7
            5.6,4.4,5.6

            etc

            May add option to only put two values in and the code will set height to 0
            */

            getline(fileMap, line);// Skip first line (number of nodes already read higher up)

            while (getline(fileMap, line))// Badly formatted files could break this
            {
                oldPos = pos;
                pos = line.find(',', 0);
                x = atof(line.substr(0, pos).c_str());

                // Looking from above (y axis is height in 3D graphics), but want to keep making files simple so swap values here

                oldPos = pos;
                pos = line.find(',', pos + 1);
                z = atof(line.substr(oldPos + 1, pos - oldPos).c_str());

                oldPos = pos;
                pos = line.find(',', pos + 1);
                y = atof(line.substr(oldPos + 1, pos - oldPos).c_str());

                map->createNode(x, y, z);
            }
        }
        fileMap.close();

        for (int i = 0; i < noOfNodes; i++)// Create edges between all nodes
        {
            for (int j = 0; j < noOfNodes; j++)
            {
                if (i < j)// Only create one edge for each pair of nodes
                {
                    map->createEdge(i, j);
                }
            }
        }
    }
    else if (type == MAPTYPE_MAZE_RANDOM)// Generate random maze
    {
        float mapSize = 15.0f;// Size of side of map (assuming it's a square may change later) in OpenGL space (this should be bigger if Node::halfsize is bigger)
        float mapOrigin[2] = {-5.0f, -5.0f};// These two need some sort of variance based on number of nodes I think
        // mapOrigin is stupid rework that (half of mapsize etc.)
        // Create a grid to make nodes space out reasonable (less overlaps and edge collisions)
        int gridSquares = ceil((float)noOfNodes / 2.0f);// Guess at how many squares needed to create a reasonale grid
        if (gridSquares < 2)
        {
            gridSquares = 2;
        }
        int nodeArray[gridSquares][gridSquares];

        for (int i = 0; i < gridSquares; i++)
        {
            for (int j = 0; j < gridSquares; j++)
            {
                nodeArray[i][j] = -1;
            }
        }

        float squareSize = mapSize / (float)gridSquares;// Size of side of one square of the grid

        std::random_device rd;
        std::mt19937 mt = std::mt19937(rd());
        std::uniform_real_distribution<float> randDisplacement(-squareSize / 2.0f, squareSize / 2.0f);// Maybe limit away from edges
        // Could have another rand dist for height or something (smaller range)

        int nodeCoords[noOfNodes][2];// Store co-ords of previous nodes, used to randomly pick node if queue is empty

        int startSquare = (ceil((float)gridSquares / 2.0f) - 1.0f);// Co-ord of first square, roughly central (assuming whole map is sqaure, same value for both)

        map->createNode((squareSize * startSquare) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * startSquare) + randDisplacement(mt) + mapOrigin[1]);// Randomly place first node within the bounds of the square
        nodeArray[startSquare][startSquare] = 0;
        int noOfNodesCreated = 1;
        nodeCoords[0][0] = startSquare;
        nodeCoords[0][1] = startSquare;

        int currentSquare[2] = {startSquare, startSquare};

        std::uniform_int_distribution<int> randNewNode(0, 99);// Chance of new node being created in a direction

        std::queue<int> nextNode;// Queue of nodes to be processed next

        #define CHANCE_OF_NEW_NODE 50

        while (noOfNodesCreated < noOfNodes)// Need to track new nodes and branch from them
        {
            for (int i = -1; i < 2; i += 2)// For up down left and right squares, runs for -1 and 1
            {
                if (noOfNodesCreated < noOfNodes && (currentSquare[0] + i) >= 0 && (currentSquare[0] + i) < gridSquares)
                {
                    int rnd = randNewNode(mt);
                    if (rnd < CHANCE_OF_NEW_NODE)
                    {
                        if (nodeArray[currentSquare[0] + i][currentSquare[1]] == -1)// No node in that square, create one and join with edge
                        {
                            map->createNode((squareSize * (currentSquare[0] + i)) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * (currentSquare[1])) + randDisplacement(mt) + mapOrigin[1]);
                            nodeArray[currentSquare[0] + i][currentSquare[1]] = noOfNodesCreated;
                            nextNode.push(noOfNodesCreated);
                            nodeCoords[noOfNodesCreated][0] = currentSquare[0] + i;
                            nodeCoords[noOfNodesCreated][1] = currentSquare[1];
                            noOfNodesCreated++;
                            map->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0] + i][currentSquare[1]]);
                        }
                        else// Node in that square, just join them
                        {
                            map->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0] + i][currentSquare[1]]);
                        }
                    }
                }
                if (noOfNodesCreated < noOfNodes && (currentSquare[1] + i) >= 0 && (currentSquare[1] + i) < gridSquares)
                {
                    int rnd = randNewNode(mt);
                    if (rnd < CHANCE_OF_NEW_NODE)
                    {
                        if (nodeArray[currentSquare[0]][currentSquare[1] + i] == -1)// No node in that square, create one and join with edge
                        {
                            map->createNode((squareSize * (currentSquare[0])) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * (currentSquare[1] + i)) + randDisplacement(mt) + mapOrigin[1]);
                            nodeArray[currentSquare[0]][currentSquare[1] + i] = noOfNodesCreated;
                            nextNode.push(noOfNodesCreated);
                            nodeCoords[noOfNodesCreated][0] = currentSquare[0];
                            nodeCoords[noOfNodesCreated][1] = currentSquare[1] + i;
                            noOfNodesCreated++;
                            map->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0]][currentSquare[1] + i]);
                        }
                        else// Node in that square, just join them
                        {
                            map->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0]][currentSquare[1] + i]);
                        }
                    }
                }
            }
            if (nextNode.empty() == false)
            {
                currentSquare[0] = nodeCoords[nextNode.front()][0];// Move onto next node in queue if any are in the queue
                currentSquare[1] = nodeCoords[nextNode.front()][1];
                nextNode.pop();
            }
            else
            {
                std::uniform_int_distribution<int> randNewStartNode(0, noOfNodesCreated - 1);// Queue is empty but not enough nodes created, randomly pick new node to start from

                int nodeTemp = randNewStartNode(mt);

                currentSquare[0] = nodeCoords[nodeTemp][0];
                currentSquare[1] = nodeCoords[nodeTemp][1];
            }

        }
    }
    else if (type == MAPTYPE_MAZE_LOADED)// Load maze from file
    {
        std::ifstream fileMap;
        fileMap.open("map.txt", std::ios::in);
        if (fileMap.is_open() == true)
        {
            std::string line;
            int pos = 0;
            int oldPos = -1;

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            int nodeA, nodeB;

            char mode = 0;// Read nodes (1) or edges (2)

            /* File should be in format of no. of nodes, then three comma separated floats per line (x,y,z) and two CS ints for edges:

            2
            NODES
            0.5,5.6,4.7
            5.6,4.4,5.6
            EDGES
            0,1
            0,2
            etc

            */

            while (getline(fileMap, line))// Badly formatted files could break this
            {
                if (line.compare("NODES") == 0)
                {
                    mode = 1;
                }
                else if (line.compare("EDGES") == 0)
                {
                    mode = 2;
                }
                else
                {
                    if (mode == 1)// Read node
                    {
                        oldPos = pos;
                        pos = line.find(',', 0);
                        x = atof(line.substr(0, pos).c_str());

                        // Looking from above (y axis is height in 3D graphics), but want to keep making files simple so swap values here

                        oldPos = pos;
                        pos = line.find(',', pos + 1);
                        z = atof(line.substr(oldPos + 1, pos - oldPos).c_str());

                        oldPos = pos;
                        pos = line.find(',', pos + 1);
                        y = atof(line.substr(oldPos + 1, pos - oldPos).c_str());

                        map->createNode(x, y, z);
                    }
                    else if (mode == 2)// Read edge
                    {
                        oldPos = pos;
                        pos = line.find(',', 0);
                        nodeA = atoi(line.substr(0, pos).c_str());

                        oldPos = pos;
                        pos = line.find(',', pos + 1);
                        nodeB = atoi(line.substr(oldPos + 1, pos - oldPos).c_str());

                        map->createEdge(nodeA, nodeB);
                    }
                }
            }
        }
        fileMap.close();
    }

    for (int i = 0; i < noOfNodes; i++)// For now, ant on every node.  May change later.
    {
        //ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneAntSystem(edges, 100.0f)));
        map->createAnt(i, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneMaxMinAS(edges, 4.0f));
    }

    //return mapTemp;
}

void Controller::render()
{
    map->render();
}
