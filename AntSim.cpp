#include "AntSim.h"

AntSim::AntSim()
{
	windowGraphics = 0;
	windowUI = 0;

    programID = 0;
}

void AntSim::push_updateParams(Fl_Widget *w, void* v)
{
    ((AntSim*)v)->updateParams();
}

void AntSim::updateParams()
{
    paramData *data = new paramData;

    data->importancePhero = atof(inputAlpha->value());
    data->importanceDistance = atof(inputBeta->value());
    data->evapRate = atof(inputEvapRate->value());
    data->pheroNumerator = atoi(inputPheroNumerator->value());

    data->noOfElitistAnts = atoi(inputElitistAnts->value());
    data->noOfRankedAnts = atoi(inputRankedAnts->value());
    data->pheroMax = atof(inputMaxPheromone->value());
    data->pheroMin = atof(inputMinPhermone->value());

    controller->updateParams(data);
}

void AntSim::push_updateMap(Fl_Widget *w, void* v)
{
    if (w)
    {
        AntSim* caller = (AntSim*)v;

        int noOfNodes = atoi(caller->inputNoOfNodes->value());

        bool type = 0;

        if (caller->buttonTSP->value() == 1)
        {
            type = MAPTYPE_TSP;
        }
        else if (caller->buttonMaze->value() == 1)
        {
            type = MAPTYPE_MAZE;
        }

        bool load = *(bool*)(w->user_data());
        caller->controller->regenerateMap(noOfNodes, type, load);
    }
}

void AntSim::push_run(Fl_Widget *w, void *v)
{
    ((AntSim*)v)->controller->run(atoi(((AntSim*)v)->inputIterations->value()));
}

void AntSim::push_runIteration(Fl_Widget *w, void *v)
{
    SDL_ShowWindow(((AntSim*)v)->windowGraphics);
    ((AntSim*)v)->controller->runIteration();
    ((AntSim*)v)->showMap();
}

bool AntSim::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {

        std::cout << "SDL failed to initialse, error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    windowGraphics = SDL_CreateWindow("AntSim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (windowGraphics == NULL) {

        std::cout << "Window could not be created, error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_HideWindow(windowGraphics);

    context = SDL_GL_CreateContext(windowGraphics);

    if (context == NULL) {

        std::cout << "OpenGL context could not be created, error: " << SDL_GetError() << std::endl;
        return false;
    }

    windowUI = new Fl_Window(SCREEN_WIDTH, SCREEN_HEIGHT);

    #define INPUTFIELD_HEIGHT 20
    #define INPUTFIELD_WIDTH 50
    #define INPUTFIELD_X (SCREEN_WIDTH - INPUTFIELD_WIDTH - 20)

    /*inputAlpha = new Fl_Float_Input(INPUTFIELD_X, 30, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone importance");//50, 605, 50, 20
    inputAlpha->value("1.0");
    inputBeta = new Fl_Float_Input(INPUTFIELD_X, 60, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Distance importance");
    inputBeta->value("1.0");
    inputEvapRate = new Fl_Float_Input(INPUTFIELD_X, 90, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Evaporation rate");
    inputEvapRate->value("0.5");
    inputPheroNumerator = new Fl_Float_Input(INPUTFIELD_X, 120, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone numerator");
    inputPheroNumerator->value("1.0");
    inputElitistAnts = new Fl_Int_Input(INPUTFIELD_X, 180, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. elitist ants");
    inputElitistAnts->value("0");
    inputRankedAnts = new Fl_Int_Input(INPUTFIELD_X, 210, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. ranked ants");
    inputRankedAnts->value("0");
    inputMaxPheromone = new Fl_Float_Input(INPUTFIELD_X, 240, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. pheromone");
    inputMaxPheromone->value("0.0");
    inputMinPhermone = new Fl_Float_Input(INPUTFIELD_X, 270, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Min. pheromone");
    inputMinPhermone->value("0.0");
    buttonUpdateParams = new Fl_Button(INPUTFIELD_X - 70, 300, 120, 30, "Update");

    buttonUpdateParams->callback((Fl_Callback *) push_updateParams, this);

    box = new Fl_Box(250, 0, 800, 600, "Where OpenGL will go");
    box->box(FL_UP_BOX);
    inputNoOfNodes = new Fl_Int_Input(INPUTFIELD_X, 340, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. nodes");
    inputNoOfNodes->value("20");
    buttonMaze = new Fl_Round_Button(INPUTFIELD_X - 70, 405, INPUTFIELD_WIDTH, 10, "Maze type map");
    buttonMaze->type(FL_RADIO_BUTTON);
    buttonTSP = new Fl_Round_Button(INPUTFIELD_X - 70, 380, INPUTFIELD_WIDTH, 10, "TSP type map");
    buttonTSP->type(FL_RADIO_BUTTON);
    buttonTSP->setonly();

    bool mapUserData;

    buttonGenerateMap = new Fl_Button(INPUTFIELD_X - 70, 430, 120, 30, "Generate map");
    mapUserData = MAP_GENERATE;
    buttonGenerateMap->user_data(&mapUserData);

    buttonGenerateMap->callback((Fl_Callback *) push_updateMap, this);

    buttonLoadMap = new Fl_Button(INPUTFIELD_X - 70, 470, 120, 30, "Load map");
    mapUserData = MAP_LOAD;
    buttonLoadMap->user_data(&mapUserData);

    buttonLoadMap->callback((Fl_Callback *) push_updateMap, this);

    inputIterations = new Fl_Int_Input(INPUTFIELD_X, 525, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. iterations");
    inputIterations->value("1000");
    buttonRunIteration = new Fl_Button(INPUTFIELD_X - 70, 560, 120, 30, "Run iteration");

    buttonRunIteration->callback((Fl_Callback *) push_runIteration, this);

    buttonRun = new Fl_Button(INPUTFIELD_X - 70, 600, 120, 30, "Run");

    buttonRun->callback((Fl_Callback *) push_run, this);*/

    inputAlpha = new Fl_Input(INPUTFIELD_X, 30, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone importance");//50, 605, 50, 20
    inputAlpha->value("1.0");
    inputBeta = new Fl_Input(INPUTFIELD_X, 60, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Distance importance");
    inputBeta->value("1.0");
    inputEvapRate = new Fl_Input(INPUTFIELD_X, 90, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Evaporation rate");
    inputEvapRate->value("0.5");
    inputPheroNumerator = new Fl_Input(INPUTFIELD_X, 120, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone numerator");
    inputPheroNumerator->value("1.0");
    inputElitistAnts = new Fl_Input(INPUTFIELD_X, 180, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. elitist ants");
    inputElitistAnts->value("0");
    inputRankedAnts = new Fl_Input(INPUTFIELD_X, 210, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. ranked ants");
    inputRankedAnts->value("0");
    inputMaxPheromone = new Fl_Input(INPUTFIELD_X, 240, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. pheromone");
    inputMaxPheromone->value("0.0");
    inputMinPhermone = new Fl_Input(INPUTFIELD_X, 270, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Min. pheromone");
    inputMinPhermone->value("0.0");
    buttonUpdateParams = new Fl_Button(INPUTFIELD_X - 70, 300, 120, 30, "Update");

    buttonUpdateParams->callback((Fl_Callback *) push_updateParams, this);

    /*box = new Fl_Box(250, 0, 800, 600, "Where OpenGL will go");
    box->box(FL_UP_BOX);*/
    inputNoOfNodes = new Fl_Input(INPUTFIELD_X, 340, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. nodes");
    inputNoOfNodes->value("20");
    buttonMaze = new Fl_Round_Button(INPUTFIELD_X - 70, 405, INPUTFIELD_WIDTH, 10, "Maze type map");
    buttonMaze->type(FL_RADIO_BUTTON);
    buttonTSP = new Fl_Round_Button(INPUTFIELD_X - 70, 380, INPUTFIELD_WIDTH, 10, "TSP type map");
    buttonTSP->type(FL_RADIO_BUTTON);
    buttonTSP->setonly();

    bool mapUserData;

    buttonGenerateMap = new Fl_Button(INPUTFIELD_X - 70, 430, 120, 30, "Generate map");
    mapUserData = MAP_GENERATE;
    buttonGenerateMap->user_data(&mapUserData);

    buttonGenerateMap->callback((Fl_Callback *) push_updateMap, this);

    buttonLoadMap = new Fl_Button(INPUTFIELD_X - 70, 470, 120, 30, "Load map");
    mapUserData = MAP_LOAD;
    buttonLoadMap->user_data(&mapUserData);

    buttonLoadMap->callback((Fl_Callback *) push_updateMap, this);

    inputIterations = new Fl_Input(INPUTFIELD_X, 525, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. iterations");
    inputIterations->value("1000");
    buttonRunIteration = new Fl_Button(INPUTFIELD_X - 70, 560, 120, 30, "Run iteration");

    buttonRunIteration->callback((Fl_Callback *) push_runIteration, this);

    buttonRun = new Fl_Button(INPUTFIELD_X - 70, 600, 120, 30, "Run");

    buttonRun->callback((Fl_Callback *) push_run, this);

    // Current iteration count somewhere?  Along buttom with other results?
    menuAntMoveBeh = new Fl_Choice(90, 30, 120, 30, "Move beh");
    /*moveBehAS = new Fl_Menu_Item[1];
    moveBehAS[0] =
    {"AS", 0, 0, 0}
    ;*/
    menuAntMoveBeh->add("AS", 0, 0);
    menuAntPheroBeh = new Fl_Choice(90, 80, 120, 30, "Phero beh");
    menuEnviroBeh = new Fl_Choice(90, 130, 120, 30, "Enviro beh");
    // Fl_File_Browser for loading files

    windowUI->end();
    windowUI->show();


    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if (glewError != GLEW_OK) {

        std::cout << "GLEW could not be initialised, error : " << glewGetErrorString(glewError) << std::endl;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {

        std::cout << "Unable to set vsync, error: " << SDL_GetError() << std::endl;
    }

    /*glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);*/

    programID = glCreateProgram();

    GLuint vertexShader = shaderLoadFromFile("antsimshader.vs", GL_VERTEX_SHADER);

    if (vertexShader == 0)
    {
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    glAttachShader(programID, vertexShader);

    GLuint fragmentShader = shaderLoadFromFile("antsimshader.fs", GL_FRAGMENT_SHADER);

    if (fragmentShader == 0)
    {
        glDeleteProgram(programID);
        return false;
    }

    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint linked;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);

    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);

    if (programSuccess != GL_TRUE) {

        std::cout << "Could not link program" << std::endl;
        printProgramLog(programID);
        return false;
    }

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        std::cout << "Failed to initialise OpenGL, error - " << gluErrorString(error);
    }*///NOPE

    projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 15.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));// Look from, look to
    //(for some reason looking at straight down means nothing renders and looking from 0 to 0.1f makes everything backwards)
    //modelMatrix = glm::translate<GLfloat>(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    uniformMatrix = glGetUniformLocation(programID, "matrixTransform");
    if (uniformMatrix  == -1) {

        std::cout << "Could not bind uniform " << uniformMatrix << std::endl;
        return false;
    }

    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(programID);

    glUniformMatrix4fv(uniformMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glUseProgram(0);

    controller = new Controller(3, MAPTYPE_MAZE, MAP_GENERATE);

    return true;
}

void AntSim::handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        //
    }
    if (key == 'm')
    {
        //
    }
}

void AntSim::update()
{

}

void AntSim::render()
{
    /*glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindBuffer(GL_UNIFORM_BUFFER, uniformDataUBO);
    glUseProgram(programID);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, NO_OF_DRAWING_INDICES, GL_UNSIGNED_INT, (const GLvoid*)0);

    glBindVertexArray(0);
    glUseProgram(0);*/

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    controller->render();

    glUseProgram(0);
}

void AntSim::close()
{
    /*glDeleteProgram(programID);*/

    /*SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();*/
    SDL_HideWindow(windowGraphics);
}

int AntSim::run()
{
    if (init() == false)
    {
        std::cout << "Initialisation failed" << std::endl;
        close();
        return 1;
    }

    Fl::run();

    return 0;
}

void AntSim::showMap()
{
    bool running = true;

    SDL_Event e;
    SDL_StartTextInput();

    while (running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                int x = 0, y = 0;
                SDL_GetMouseState(&x, &y);
                handleKeys(e.text.text[0], x, y);
            }
        }
        render();
        SDL_GL_SwapWindow(windowGraphics);
    }

    SDL_StopTextInput();
    close();
}

GLuint AntSim::shaderLoadFromFile(std::string path, GLenum shaderType)
{
    std::string stringShader;
    std::ifstream fileShader(path.c_str());

    if (fileShader)
    {
        stringShader.assign((std::istreambuf_iterator<char>(fileShader)), std::istreambuf_iterator<char>());

        GLuint shader = glCreateShader(shaderType);

        const GLchar* pntStringSource = stringShader.c_str();

        glShaderSource(shader, 1, static_cast<const GLchar**>(&pntStringSource), 0);
        glCompileShader(shader);

        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

        if (shaderCompiled != GL_TRUE)
        {
            std::cout << "Unable to compile shader " << shader << " (path: " << path << ")" << std::endl;
            printShaderLog(shader);
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }
    else
    {
        std::cout << "Could not open file " << path.c_str() << std::endl;
        return 0;
    }
}

void AntSim::printProgramLog(GLuint program)
{
    // Nothing right now
}

void AntSim::printShaderLog(GLuint shader)
{
    if (glIsShader(shader))
    {
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

        if (infoLogLength > 0)
        {
            std::cout << infoLog << std::endl;
        }

        delete[] infoLog;
    }
}

int main(void)
{
    AntSim antsim;
    return antsim.run();
}
