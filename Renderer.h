#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <GL/glew.h>
#include "SDL2/SDL_opengl.h"
#include "Vector4.h"

class Renderer
{
public:

	Renderer(int noOfVertices, int noOfIndices, Vector4 *vertPosArray, unsigned int *indexArray);

	void init(int noOfVertices, int noOfIndices, Vector4 *vertPosArray, unsigned int *indexArray);

	void drawElements();

private:

    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    GLuint noOfVertices;
    GLuint noOfIndices;
};

#endif // _RENDERER_H_
