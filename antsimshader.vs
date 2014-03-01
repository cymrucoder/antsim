#version 330

uniform mat4 matrixTransform;

layout (location=0) in vec4 vertexPos;
//layout (location=1) in vec2 texCoord;

void main(void)
{
    gl_Position = (matrixTransform * vertexPos);
}
