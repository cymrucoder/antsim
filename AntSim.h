#ifndef _ANTSIM_H_
#define _ANTSIM_H_

#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Int_Input.h>
#include <FL/Fl_Float_Input.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Round_Button.h>
#include <FL/Fl_Choice.h>
#include <FL/Fl_Menu_Item.h>

//#include "SDL2/SDL.h"
#include <GL/glew.h>
//#include "SDL2/SDL_opengl.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <vector>
#include <iostream>

#include "Controller.h"

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 700

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

    //void handle_menu2(Fl_Widget *w, void *v);
    //void push_cb(Fl_Widget *w, void* v);

    static void push_updateParams(Fl_Widget *w, void *v);
    void updateParams();

    static void push_updateMap(Fl_Widget *w, void *v);

    static void push_run(Fl_Widget *w, void *v);
    static void push_runIteration(Fl_Widget *w, void *v);

private:

    /*SDL_Window* window;
    SDL_GLContext context;*/
    Fl_Window *window;
    Fl_Box *box;
    Fl_Float_Input *inputAlpha;
    Fl_Float_Input *inputBeta;
    Fl_Float_Input *inputEvapRate;
    Fl_Float_Input *inputPheroNumerator;

    Fl_Int_Input *inputElitistAnts;
    Fl_Int_Input *inputRankedAnts;
    Fl_Float_Input *inputMaxPheromone;
    Fl_Float_Input *inputMinPhermone;

    Fl_Button *buttonUpdateParams;

    Fl_Int_Input *inputNoOfNodes;

    Fl_Round_Button *buttonTSP;
    Fl_Round_Button *buttonMaze;
    Fl_Button *buttonGenerateMap;
    Fl_Button *buttonLoadMap;

    Fl_Int_Input *inputIterations;

    Fl_Button *buttonRunIteration;
    Fl_Button *buttonRun;

    Fl_Choice *menuAntMoveBeh;
    Fl_Choice *menuAntPheroBeh;
    Fl_Choice *menuEnviroBeh;

    Fl_Menu_Item *moveBehAS;

    GLuint programID;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 mvpMatrix;

    GLint uniformMatrix;

    Controller *controller;
};

#endif // _ANTSIM_H_
