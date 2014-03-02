#include "Node.h"

Node::Node(float x, float y, float z)
{
    coords[COORD_X] = x;
    coords[COORD_Y] = y;
    coords[COORD_Z] = z;

    int noOfElements = 2 * 3;// For now, this is a square.  Change to a circle later.  GL_TRIANGLES, for now (2 triangles with 3 verts each)

    Vector4 *vertPosArray = new Vector4 [noOfElements];
    unsigned int *indexArray = new unsigned int [noOfElements];

    float halfsize = 0.5f;

    /*vertPosArray[0] = Vector4(x - halfsize, 0.0f, z - halfsize);
    vertPosArray[1] = Vector4(x - halfsize, 0.0f, z + halfsize);
    vertPosArray[2] = Vector4(x + halfsize, 0.0f, z + halfsize);
    vertPosArray[3] = Vector4(x + halfsize, 0.0f, z - halfsize);*/

    vertPosArray[0] = Vector4(-0.5f, 0.0f, -0.5f);
    vertPosArray[1] = Vector4(-0.5f, 0.0f, 0.5f);
    vertPosArray[2] = Vector4(0.5f, 0.0f, 0.5f);
    vertPosArray[3] = Vector4(0.5f, 0.0f, -0.5f);

    indexArray[0] = 0;
    indexArray[1] = 1;
    indexArray[2] = 2;
    indexArray[3] = 0;
    indexArray[4] = 2;
    indexArray[5] = 3;

    init(noOfElements, vertPosArray, indexArray);
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
    drawElements();
}
