#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <GL/glew.h>
#include "SDL2/SDL_opengl.h"

struct Vector4 {

    float x, y, z, w;

    Vector4() {}

    Vector4(float x, float y, float z, float w = 1.0f) {

        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

class Renderable
{
public:

	virtual ~Renderable();

protected:

    virtual void render() = 0;

	void init(int noOfElements, Vector4 *vertPosArray, unsigned int *indexArray);

	void drawElements();

private:

    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    GLuint noOfElements;

    // Need colour data somewhere (dynamic?)

};

#endif // _RENDERABLE_H_
