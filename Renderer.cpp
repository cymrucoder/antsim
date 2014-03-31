#include "Renderer.h"

Renderer::Renderer(int noOfVertices, int noOfIndices, Vector4 *vertPosArray, unsigned int *indexArray)
{
    // Take in vertex and index data, set up OpenGL specific memory

    this->noOfVertices = noOfVertices;
    this->noOfIndices = noOfIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, noOfVertices * sizeof(Vector4), vertPosArray, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfIndices * sizeof(unsigned int), indexArray, GL_STATIC_DRAW);

    glBindVertexArray(0);

    delete vertPosArray;
    delete indexArray;
}

void Renderer::drawElements()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, (const GLvoid*)0);

    glBindVertexArray(0);
}
