#include "Map.h"

Map::Map(int noOfNodes, EdgeArray *edges, EnvironmentBehaviour *enviroBeh)
{
    this->edges = edges;

    /*nodes.push_back(new Node(54.0f, 67.0f, 0.0f));
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
    nodes.push_back(new Node(58.0f, 69.0f, 0.0f));*/

    /*nodes.push_back(new Node(37.950f, 27.364f, 0.0f));// 1 - Temple of Artemis, Greece
    nodes.push_back(new Node(29.979f, 31.134f, 0.0f));// 2 - Pyramids, Egypt
    nodes.push_back(new Node(37.177f, -3.591f, 0.0f));// 3 - Alhambra, Spain
    nodes.push_back(new Node(15.073f, 102.219f, 0.0f));// 4 - Great Wall of China, China
    nodes.push_back(new Node(-13.166f, -72.544f, 0.0f));// 5 - Machu Pichu, Peru
    nodes.push_back(new Node(40.800f, -73.968f, 0.0f));// 6 - Broadway, USA
    nodes.push_back(new Node(43.643f, -79.387f, 0.0f));// 7 - CN Tower, Canada
    nodes.push_back(new Node(-33.858f, 151.215f, 0.0f));// 8 - SOH, Straya
    nodes.push_back(new Node(52.516f, 13.178f, 0.0f));// 9 - Brandenburg Gate, Germany
    nodes.push_back(new Node(-7.603f, 110.204f, 0.0f));// 10 - bhruveiuebiuriuer, Java
    nodes.push_back(new Node(41.008f, 28.976f, 0.0f));// 11 - Hagia Sophia, Turkey
    nodes.push_back(new Node(38.871f, -77.056f, 0.0f));// 12 - The Pentagon, USA
    nodes.push_back(new Node(51.508f, -0.097f, 0.0f));// 13 - Globe Theatre, UK
    nodes.push_back(new Node(39.916f, 116.397f, 0.0f));// 14 - The Forbidden Palace, China
    nodes.push_back(new Node(34.849f, 134.694f, 0.0f));// 15 - Himji Castle, Japan
    nodes.push_back(new Node(47.558f, 10.750f, 0.0f));// 16 - Castell Nwchy, Germany
    nodes.push_back(new Node(54.439f, 13.757f, 0.0f));// 17 - Prora, Germany
    nodes.push_back(new Node(28.656f, 77.242f, 0.0f));// 18 - Red Fort, India
    nodes.push_back(new Node(55.752f, 37.618f, 0.0f));// 19 - The Kremlin, Russia
    nodes.push_back(new Node(13.426f, 103.860f, 0.0f));// 20 - Ankor Wat, Cambodia
    nodes.push_back(new Node(43.768f, 11.255f, 0.0f));// 21 - Uffizi, Italy
    nodes.push_back(new Node(49.043f, 2.506f, 0.0f));// 22 - The Louvre, France
    nodes.push_back(new Node(13.905f, -4.556f, 0.0f));// 23 - Great Mosque of Dijenne, Mali
    nodes.push_back(new Node(27.173f, 78.042f, 0.0f));// 24 - Taj Mahal, India
    nodes.push_back(new Node(20.684f, -88.568f, 0.0f));// 25 - Chitzen Itza, Mexico
    nodes.push_back(new Node(48.853f, 2.350f, 0.0f));// 26 - Notre Dame, France
    nodes.push_back(new Node(41.903f, 12.454f, 0.0f));// 27 - Sistine Chapel, Italy
    nodes.push_back(new Node(43.723f, 10.397f, 0.0f));// 28 - Leaning Tower, Italy
    nodes.push_back(new Node(-22.952f, -43.210f, 0.0f));// 29 - Christo Redendor, Brazil
    nodes.push_back(new Node(34.384f, 109.278f, 0.0f));// 30 - Terracota Army, China
    nodes.push_back(new Node(37.970f, 23.722f, 0.0f));// 31 - The Parthanon, Greece*/

    /*nodes.push_back(new Node(37.950f, 0.0f, 27.364f));// 1 - Temple of Artemis, Greece
    nodes.push_back(new Node(29.979f, 0.0f, 31.134f));// 2 - Pyramids, 0.0f, Egypt
    nodes.push_back(new Node(37.177f, 0.0f, -3.591f));// 3 - Alhambra, 0.0f, Spain
    nodes.push_back(new Node(15.073f, 0.0f, 102.219f));// 4 - Great Wall of China, 0.0f, China
    nodes.push_back(new Node(-13.166f, 0.0f, -72.544f));// 5 - Machu Pichu, 0.0f, Peru
    nodes.push_back(new Node(40.800f, 0.0f, -73.968f));// 6 - Broadway, 0.0f, USA
    nodes.push_back(new Node(43.643f, 0.0f, -79.387f));// 7 - CN Tower, 0.0f, Canada
    nodes.push_back(new Node(-33.858f, 0.0f, 151.215f));// 8 - SOH, 0.0f, Straya
    nodes.push_back(new Node(52.516f, 0.0f, 13.178f));// 9 - Brandenburg Gate, 0.0f, Germany
    nodes.push_back(new Node(-7.603f, 0.0f, 110.204f));// 10 - bhruveiuebiuriuer, 0.0f, Java
    nodes.push_back(new Node(41.008f, 0.0f, 28.976f));// 11 - Hagia Sophia, 0.0f, Turkey
    nodes.push_back(new Node(38.871f, 0.0f, -77.056f));// 12 - The Pentagon, 0.0f, USA
    nodes.push_back(new Node(51.508f, 0.0f, -0.097f));// 13 - Globe Theatre, 0.0f, UK
    nodes.push_back(new Node(39.916f, 0.0f, 116.397f));// 14 - The Forbidden Palace, 0.0f, China
    nodes.push_back(new Node(34.849f, 0.0f, 134.694f));// 15 - Himji Castle, 0.0f, Japan
    nodes.push_back(new Node(47.558f, 0.0f, 10.750f));// 16 - Castell Nwchy, 0.0f, Germany
    nodes.push_back(new Node(54.439f, 0.0f, 13.757f));// 17 - Prora, 0.0f, Germany
    nodes.push_back(new Node(28.656f, 0.0f, 77.242f));// 18 - Red Fort, 0.0f, India
    nodes.push_back(new Node(55.752f, 0.0f, 37.618f));// 19 - The Kremlin, 0.0f, Russia
    nodes.push_back(new Node(13.426f, 0.0f, 103.860f));// 20 - Ankor Wat, 0.0f, Cambodia
    nodes.push_back(new Node(43.768f, 0.0f, 11.255f));// 21 - Uffizi, 0.0f, Italy
    nodes.push_back(new Node(49.043f, 0.0f, 2.506f));// 22 - The Louvre, 0.0f, France
    nodes.push_back(new Node(13.905f, 0.0f, -4.556f));// 23 - Great Mosque of Dijenne, 0.0f, Mali
    nodes.push_back(new Node(27.173f, 0.0f, 78.042f));// 24 - Taj Mahal, 0.0f, India
    nodes.push_back(new Node(20.684f, 0.0f, -88.568f));// 25 - Chitzen Itza, 0.0f, Mexico
    nodes.push_back(new Node(48.853f, 0.0f, 2.350f));// 26 - Notre Dame, 0.0f, France
    nodes.push_back(new Node(41.903f, 0.0f, 12.454f));// 27 - Sistine Chapel, 0.0f, Italy
    nodes.push_back(new Node(43.723f, 0.0f, 10.397f));// 28 - Leaning Tower, 0.0f, Italy
    nodes.push_back(new Node(-22.952f, 0.0f, -43.210f));// 29 - Christo Redendor, 0.0f, Brazil
    nodes.push_back(new Node(34.384f, 0.0f, 109.278f));// 30 - Terracota Army, 0.0f, China
    nodes.push_back(new Node(37.970f, 0.0f, 23.722f));// 31 - The Parthanon, Greece*/
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
        // If the edge is added, create an Edge to store its graphical data

        /*float angle = (atan2(nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z),
                             nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X))
                       * (180.0f / 3.1415926535897));// Get math.h PI

       float halfsize = 0.5f;

        Vector4 *edgeVertices = new Vector4[4];

        // Work out the coordinates of each vertex.  Not sure if this is faster or if doing the trig for each would be faster, test if get a chance (or just use ratio between coords to work it out?)
        // Going to use all trig to make it work properly for now

        edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - (halfsize * sin(90.0f - angle)), nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) + (halfsize * sin(angle)));
        //edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - edgeVertices[0].x, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - edgeVertices[0].z);

        //edgeVertices[1] = Vector4(edgeVertices[0].x + (nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X)), nodes.at(nodeB)->getCoord(COORD_Y), edgeVertices[0].z + (nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z)));
        //edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - edgeVertices[1].x, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - edgeVertices[1].z);

        edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + (halfsize * sin(90.0f - angle)), nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - (halfsize * sin(angle)));

        edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + (halfsize * sin(90.0f - angle)), nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) + (halfsize * sin(angle)));
        edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - (halfsize * sin(90.0f - angle)), nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - (halfsize * sin(angle)));
        */

        Vector4 *edgeVertices = new Vector4[4];

        //char sideA, sideB;// Which side of nodes A and B should the edge stick to (R - 0, U - 1, L - 2, D - 3, looking from above, U is negative Z) (maybe B should just be -A)

        if (abs(nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X)) >=  abs(nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z)))// L and R take points on the line between directions
        {
            // The eV[n] = Vec... bit could be shortened, there's a pattern.  Works for now though
            if ((nodes.at(nodeB)->getCoord(COORD_X) - nodes.at(nodeA)->getCoord(COORD_X)) >= 0.0f)// R, on line between L and R => R
            {
                //sideA = 0;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
            }
            else// L
            {
                //sideA = 2;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
            }
        }
        else
        {
            if ((nodes.at(nodeB)->getCoord(COORD_Z) - nodes.at(nodeA)->getCoord(COORD_Z)) >= 0.0f)// D, On line between U and D => D
            {
                //sideA = 3;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) + Node::halfsize);
            }
            else// U
            {
                //sideA = 1;
                edgeVertices[0] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
                edgeVertices[1] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) + Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[2] = Vector4(nodes.at(nodeB)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeB)->getCoord(COORD_Y), nodes.at(nodeB)->getCoord(COORD_Z) + Node::halfsize);
                edgeVertices[3] = Vector4(nodes.at(nodeA)->getCoord(COORD_X) - Node::halfsize, nodes.at(nodeA)->getCoord(COORD_Y), nodes.at(nodeA)->getCoord(COORD_Z) - Node::halfsize);
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

void Map::render()
{
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        nodes.at(i)->render();
    }
    for (unsigned int i = 0; i < renderableEdges.size(); i++)
    {
        renderableEdges.at(i)->render();
    }
}
