#ifndef _RENDERABLEEDGE_H_
#define _RENDERABLEEDGE_H_

#include "Renderer.h"

class RenderableEdge
{
public:

	RenderableEdge(Vector4 *coordArray);

    void render();

private:

    Renderer *renderer;

};

#endif // _RENDERABLEEDGE_H_
