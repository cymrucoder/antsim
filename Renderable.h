#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <GL/glew.h>
#include "SDL2/SDL_opengl.h"
#include "Vector4.h"

class Renderable
{
public:

	virtual ~Renderable();

protected:

    virtual void render() = 0;

	void init(int noOfVertices, int noOfIndices, Vector4 *vertPosArray, unsigned int *indexArray);

	void drawElements();

private:

    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    GLuint noOfVertices;
    GLuint noOfIndices;

    // Need colour data somewhere (dynamic?)

};

#endif // _RENDERABLE_H_
