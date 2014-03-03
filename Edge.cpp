#include "Edge.h"

Edge::Edge(Vector4 *coordData)
{
    int noOfVertices = 4;
    int noOfIndices = 2 * 3;

    Vector4 *vertPosArray = new Vector4[noOfVertices];
    unsigned int *indexArray = new unsigned int[noOfIndices];

    //float halfsize = 0.5f;

    vertPosArray[0] = coordData[0];
    vertPosArray[1] = coordData[1];
    vertPosArray[2] = coordData[2];
    vertPosArray[3] = coordData[3];

    indexArray[0] = 0;
    indexArray[1] = 1;
    indexArray[2] = 2;
    indexArray[3] = 0;
    indexArray[4] = 2;
    indexArray[5] = 3;

    /*indexArray[0] = 0;
    indexArray[1] = 3;
    indexArray[2] = 0;
    indexArray[3] = 0;
    indexArray[4] = 3;
    indexArray[5] = 0;*/

    init(noOfVertices, noOfIndices, vertPosArray, indexArray);
}

void Edge::render()
{
    drawElements();
}
