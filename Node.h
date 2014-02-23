#ifndef _NODE_H_
#define _NODE_H_

#define COORD_X 0
#define COORD_Y 1
#define COORD_Z 2

#include <vector>

class Node
{
public:

	Node(float x, float y, float z);
	//~Node();

	float getCoord(int coord);

private:

    float coords[3];
};

#endif // _NODE_H_
