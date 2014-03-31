#version 330

uniform mat4 matrixTransform;

layout (location=0) in vec4 vertexPos;

void main(void)
{
    gl_Position = (matrixTransform * vertexPos);
}
