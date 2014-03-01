#include "Node.h"

Node::Node(float x, float y, float z)
{
    coords[COORD_X] = x;
    coords[COORD_Y] = y;
    coords[COORD_Z] = z;
}

float Node::getCoord(int coord)
{
    if (coord <= COORD_Z && coord >= COORD_X)
    {
        return coords[coord];
    }
    else
    {
        return 0.0f;// This is technically a valid coord but I'm not sure what else to return.  NaN?
    }
}

void Node::render()
{

}
