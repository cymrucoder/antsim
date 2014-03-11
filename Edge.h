#ifndef _EDGE_H_
#define _EDGE_H_

#include "Renderer.h"

class Edge
{
public:

	Edge(Vector4 *coordArray);

    void render();

protected:

private:

    Renderer *renderer;

};

#endif // _EDGE_H_
