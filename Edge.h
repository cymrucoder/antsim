#ifndef _EDGE_H_
#define _EDGE_H_

#include "Renderable.h"

class Edge : public Renderable
{
public:

	Edge(Vector4 *coordArray);

    void render();

protected:

private:

};

#endif // _EDGE_H_
