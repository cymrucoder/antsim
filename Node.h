#ifndef _NODE_H_
#define _NODE_H_

#define COORD_X 0
#define COORD_Y 1
#define COORD_Z 2

#include <vector>
#include "Renderer.h"

class Node
{
public:

	Node(float x, float y, float z);

	float getCoord(int coord);

	const static float halfsize;

	void render();

private:

    float coords[3];
    Renderer *renderer;
};

#endif // _NODE_H_
