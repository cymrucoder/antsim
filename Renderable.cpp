#include "Renderable.h"

Renderable::~Renderable()
{

}

void Renderable::init(int noOfElements, Vector4 *vertPosArray, unsigned int *indexArray)
{
    this->noOfElements = noOfElements;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertPosArray), vertPosArray, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&indexArray), indexArray, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete vertPosArray;
    delete indexArray;
}

void Renderable::drawElements()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, noOfElements, GL_UNSIGNED_INT, (const GLvoid*)0);

    glBindVertexArray(0);
}
