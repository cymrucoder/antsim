#include "Map.h"

Map::Map(int noOfNodes, EdgeArray *edges, EnvironmentBehaviour *enviroBeh, bool type)
{
    this->edges = edges;
    this->enviroBeh = enviroBeh;
    this->type = type;
}

Map::~Map()
{
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        delete nodes.at(i);
    }
    for (unsigned int i = 0; i < renderableEdges.size(); i++)
    {
        delete renderableEdges.at(i);
    }

    for (unsigned int i = 0; i < ants.size(); i++)
    {
        delete ants.at(i);
    }

    delete enviroBeh;

    delete edges;
}

void Map::createNode(float x, float y, float z)
{
    nodes.push_back(new Node(x, y, z));
}

void Map::createEdge(int nodeA, int nodeB)
{
    float distance = sqrt(  pow((nodes.at(nodeA)->getCoord(COORD_X) - nodes.at(nodeB)->getCoord(COORD_X)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Y) - nodes.at(nodeB)->getCoord(COORD_Y)), 2.0f) +
                            pow((nodes.at(nodeA)->getCoord(COORD_Z) - nodes.at(nodeB)->getCoord(COORD_Z)), 2.0f));

    if (edges->addEdge(nodeA, nodeB, distance, 10.0f) == true)// Last argument needs to be default phero level whenever I add that
    {
        // If the edge is added, create an RenderableEdge to store its graphical data

        Vector4 *edgeVertices = new Vector4[4];

        //char sideA, sideB;// Which side of nodes A and B should the edge stick to (R - 0, U - 1, L - 2, D - 3, looking from above, U is negative Z) (maybe B should just be -A)

        if (abs(nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X)) >=  abs(nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z)))// L and R take points on the line between directions
        {
            // The eV[n] = Vec... bit could be shortened, there's a pattern.  Works for now though
            if ((nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X)) >= 0.0f)// R, on line between L and R => R
            {
                //sideA = 0;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
            }
            else// L
            {
                //sideA = 2;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
            }
        }
        else
        {
            if ((nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z)) >= 0.0f)// D, On line between U and D => D
            {
                //sideA = 3;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
            }
            else// U
            {
                //sideA = 1;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);

                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeB)->getCoord(COORD_Y),
                                          nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);

                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize,
                                          nodes.at(nodeA)->getCoord(COORD_Y),
                                          nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
            }
        }
        renderableEdges.push_back(new RenderableEdge(edgeVertices));
    }
}

void Map::createAnt(int node, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh)
{
    //ants.push_back(new Ant(i, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneAntSystem(edges, 100.0f)));
    ants.push_back(new Ant(node, edges, new MoveAntSystem(edges, 1.0f, 5.0f), new PheromoneMaxMinAS(edges, 4.0f)));
}

void setEnvironmentBehaviour(EnvironmentBehaviour *enviroBeh)
{
    delete this->enviroBeh;
    this->enviroBeh = enviroBeh;
}

void Map::render()
{
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        nodes.at(i)->render();
    }

    if (type == MAPTYPE_MAZE)// Rendering edges is pointless (all nodes connceted) and confusing for TSP type maps
    {
        for (unsigned int i = 0; i < renderableEdges.size(); i++)
        {
            renderableEdges.at(i)->render();
        }
    }
}
