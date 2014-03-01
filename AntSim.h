#ifndef _ANTSIM_H_
#define _ANTSIM_H_

#include "SDL2/SDL.h"
#include <GL/glew.h>
#include "SDL2/SDL_opengl.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <SOIL/SOIL.h>

#include <vector>
#include <iostream>

#define NO_OF_NODES 31

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class AntSim
{
public:

	AntSim();

	bool init();
    void handleKeys(unsigned char key, int x, int y);
    void update();
    void render();
    void close();

    int run();

    GLuint shaderLoadFromFile(std::string path, GLenum shaderType);
    void printProgramLog(GLuint program);// Once the shader definitely works can probably get rid of the two printing bits
    void printShaderLog(GLuint shader);

private:

    SDL_Window* window;
    SDL_GLContext context;

    GLuint programID ;

    GLuint VAO;
    GLuint VBOvec;
    GLuint VBOtex;
    GLuint IBO;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 mvpMatrix;

    GLint uniformMatrix;
};

#endif // _ANTSIM_H_
