#include "Controller.h"

Controller::Controller(int noOfNodes, bool type, bool load)
{
    if (load == MAP_LOAD)// Random seed optional (make type non optional or overload or something)
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
    //EdgeArray *edges = new EdgeArray(noOfNodes);// This is messy which I why I liked the old way.  Will decide which to use later
    map = generateMap(noOfNodes, type);
    //map = new Map(noOfNodes, edges, new EnvironmentMaxMinAS(0.5f, edges));
    //generateMap(noOfNodes, edges, type);

    shortestKnownPath = INFINITY;
    iteration = 0;
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
    clock_gettime(CLOCK_REALTIME, &spec);// Start timing

    for (unsigned int i = 0; i < map->ants.size(); i++)
    {
        for (unsigned int j = 0; j < map->nodes.size() - 1; j++)
        {
            map->ants.at(i)->move();
        }
    }

    map->enviroBeh->updatePheromone();

    map->enviroBeh->processAntList(&map->ants, &map->processedAnts);// enviroBeh generates new list of ants that are able to update

    for (unsigned int i = 0; i < map->processedAnts.size(); i++)
    {
        map->processedAnts.at(i)->updatePheromone();
    }

    map->processedAnts.clear();

    // Unsure if I should stop timing here or if a result is found (this isn't technically part of the algorithms so I think here)

    clock_gettime(CLOCK_REALTIME, &specend);// Stop timing and add nanoseconds taken to total time count

    if (spec.tv_sec != specend.tv_sec)// tv_nsec gives nanoseconds since current second started, have to account for a new second starting between timings
    {
        totalTime += ((specend.tv_sec - spec.tv_sec) * 1.0e9) + (specend.tv_nsec - spec.tv_nsec);
    }
    else
    {
        totalTime += (specend.tv_nsec - spec.tv_nsec);
    }

    for (unsigned int i = 0; i < map->ants.size(); i++)
    {
        float actualLengthA = map->ants.at(i)->getLengthOfPath() + (map->edges->getLength(map->ants.at(i)->nodesVisited.at(0), map->ants.at(i)->nodesVisited.back()));// Move from final node to start node not accounted for ATM,

        if (actualLengthA < shortestKnownPath)
        {
            shortestKnownPath = actualLengthA;

            std::cout << "New shortest path found at " << (totalTime / 1.0e6) << "ms (length: " << shortestKnownPath << "), iteration " << iteration << std::endl;

            //std::ifstream fileOutput;
            //fileOutput.open("map.txt", std::ios::in);

            //std::cout << "New shortest path, length: " << shortestKnownPath << " (iteration: " << iter << "):";

            for (unsigned int j = 0; j < map->ants.at(i)->nodesVisited.size(); j++)
            {
                //std::cout << " " << map->ants.at(i)->nodesVisited.at(j);
            }
            //std::cout << std::endl;
        }
        map->ants.at(i)->reset();
    }
    iteration++;
}

void Controller::updateParams(struct paramData *data)
{
    map->enviroBeh->updateParams(data);

    for (unsigned int i = 0; i < map->ants.size(); i++)
    {
        map->ants.at(i)->updateParams(data);
    }
}

void Controller::regenerateMap(int noOfNodes, bool type, bool load)
{
    // Node and Edge are fine
    // Ant has new(bla) stuff (behaviours)
    if (map != NULL)
    {
        delete map;
    }

    map = generateMap(noOfNodes, type, load);

    shortestKnownPath = INFINITY;
    iteration = 0;
}

Map* Controller::generateMap(int noOfNodes, bool type, bool load)
{
    EdgeArray *tempEdges = new EdgeArray(noOfNodes);// Would prefer to create this inside Map but if it's here than the behaviours can use it easier

    //Map *mapTemp = new Map(noOfNodes, tempEdges, new EnvironmentAntSystem(tempEdges, 0.7f), MAPTYPE_TSP);
    Map *mapTemp = new Map(noOfNodes, tempEdges, environmentBehFactory.makeEnvironmentBehaviour(ENVIRONMENT_BEH_TYPE_AS, tempEdges), MAPTYPE_TSP);
    if (type == MAPTYPE_TSP)// Map for TSP type problem
    {
        if (load == MAP_GENERATE)// Generate randomly
        {
            std::random_device rd;
            std::mt19937 mt = std::mt19937(rd());
            std::uniform_real_distribution<float> randCoord(-5.0f, 5.0f);

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
        }
        else if (load == MAP_LOAD)// Load nodes for TSP type problem from file
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

                    mapTemp->createNode(x, y, z);
                }
            }

            fileMap.close();

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
        }
    }
    else if (type == MAPTYPE_MAZE)// Map for maze
    {
        if (load == MAP_GENERATE)
        {
            float mapSize = 8.0f;// Size of side of map (assuming it's a square may change later) in OpenGL space (this should be bigger if Node::halfsize is bigger)
            float mapOrigin[2] = {-2.0f, -2.0f};// These two need some sort of variance based on number of nodes I think
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

            mapTemp->createNode((squareSize * startSquare) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * startSquare) + randDisplacement(mt) + mapOrigin[1]);// Randomly place first node within the bounds of the square
            nodeArray[startSquare][startSquare] = 0;
            int noOfNodesCreated = 1;
            nodeCoords[0][0] = startSquare;
            nodeCoords[0][1] = startSquare;

            int currentSquare[2] = {startSquare, startSquare};

            std::uniform_int_distribution<int> randNewNode(0, 99);// Chance of new node being created in a direction

            std::queue<int> nextNode;// Queue of nodes to be processed next

            #define CHANCE_OF_NEW_NODE 30

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
                                mapTemp->createNode((squareSize * (currentSquare[0] + i)) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * (currentSquare[1])) + randDisplacement(mt) + mapOrigin[1]);
                                nodeArray[currentSquare[0] + i][currentSquare[1]] = noOfNodesCreated;
                                nextNode.push(noOfNodesCreated);
                                nodeCoords[noOfNodesCreated][0] = currentSquare[0] + i;
                                nodeCoords[noOfNodesCreated][1] = currentSquare[1];
                                noOfNodesCreated++;
                                mapTemp->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0] + i][currentSquare[1]]);
                            }
                            else// Node in that square, just join them
                            {
                                mapTemp->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0] + i][currentSquare[1]]);
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
                                mapTemp->createNode((squareSize * (currentSquare[0])) + randDisplacement(mt) + mapOrigin[0], 0.0f, (squareSize * (currentSquare[1] + i)) + randDisplacement(mt) + mapOrigin[1]);
                                nodeArray[currentSquare[0]][currentSquare[1] + i] = noOfNodesCreated;
                                nextNode.push(noOfNodesCreated);
                                nodeCoords[noOfNodesCreated][0] = currentSquare[0];
                                nodeCoords[noOfNodesCreated][1] = currentSquare[1] + i;
                                noOfNodesCreated++;
                                mapTemp->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0]][currentSquare[1] + i]);
                            }
                            else// Node in that square, just join them
                            {
                                mapTemp->createEdge(nodeArray[currentSquare[0]][currentSquare[1]], nodeArray[currentSquare[0]][currentSquare[1] + i]);
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
        else if (load == MAP_LOAD)// Load maze from file
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

                            mapTemp->createNode(x, y, z);
                        }
                        else if (mode == 2)// Read edge
                        {
                            oldPos = pos;
                            pos = line.find(',', 0);
                            nodeA = atoi(line.substr(0, pos).c_str());

                            oldPos = pos;
                            pos = line.find(',', pos + 1);
                            nodeB = atoi(line.substr(oldPos + 1, pos - oldPos).c_str());

                            mapTemp->createEdge(nodeA, nodeB);
                        }
                    }
                }
            }
            fileMap.close();
        }
    }

    for (int i = 0; i < noOfNodes; i++)// For now, ant on every node.  May change later.
    {
        //ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneAntSystem(edges, 100.0f)));
        //mapTemp->createAnt(i, new MoveAntSystem(tempEdges, 1.0f, 5.0f), new PheromoneAntSystem(tempEdges, 1.0f));
        mapTemp->createAnt(i, moveBehFactory.makeMoveBehaviour(MOVE_BEH_TYPE_AS, tempEdges), pheromoneBehFactory.makePheromoneBehaviour(PHEROMONE_BEH_TYPE_AS, tempEdges));
    }

    return mapTemp;
}

void Controller::render()
{
    map->render();
}
