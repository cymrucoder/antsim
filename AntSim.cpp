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

void AntSim::push_generateMap(Fl_Widget *w, void* v)
{
    if (w)
    {
        AntSim* caller = (AntSim*)v;

        int noOfNodes = atoi(caller->inputNoOfNodes->value());

        if (caller->buttonTSP->value() == 1)
        {
            caller->controller->regenerateMap(noOfNodes, MAPTYPE_TSP, MAP_GENERATE);
        }
        else if (caller->buttonMaze->value() == 1)
        {
            caller->controller->regenerateMap(noOfNodes, MAPTYPE_MAZE, MAP_GENERATE);
        }
    }
}

void AntSim::push_loadMap(Fl_Widget *w, void* v)
{
    if (w)
    {
        AntSim* caller = (AntSim*)v;

        if (caller->buttonTSP->value() == 1)
        {
            caller->controller->regenerateMap(0, MAPTYPE_TSP, MAP_LOAD);
        }
        else if (caller->buttonMaze->value() == 1)
        {
            caller->controller->regenerateMap(0, MAPTYPE_MAZE, MAP_LOAD);
        }
    }
}

void AntSim::push_run(Fl_Widget *w, void *v)// Shows the graphical representation and runs through maxIteration iterations of the algorithm
{
    AntSim *caller = (AntSim*)v;

    SDL_ShowWindow(caller->windowGraphics);

    Controller *controller = (caller->controller);

    controller->iteration = 0;
    controller->totalTime = 0;
    controller->shortestKnownPath = INFINITY;

    controller->maxIterations = atoi(caller->inputIterations->value());

    bool maptype = MAPTYPE_TSP;

    if (caller->buttonMaze->value() == 1)
    {
        maptype = MAPTYPE_MAZE;
    }

    while(controller->iteration < controller->maxIterations)
    {
        controller->runIteration(maptype);
        caller->render();
        SDL_GL_SwapWindow(caller->windowGraphics);
    }

    controller->map->edges->reset();

    SDL_HideWindow(caller->windowGraphics);
}

void AntSim::push_runIteration(Fl_Widget *w, void *v)
{
    bool maptype = MAPTYPE_TSP;

    if (((AntSim*)v)->buttonMaze->value() == 1)
    {
        maptype = MAPTYPE_MAZE;
    }

    //SDL_ShowWindow(((AntSim*)v)->windowGraphics);
    ((AntSim*)v)->controller->runIteration(maptype);
    //((AntSim*)v)->showMap();
}

void AntSim::push_updateMoveBehaviour(Fl_Widget *w, void *v)
{
    if (w)
    {
        ((AntSim*)v)->controller->updateMoveBehaviour(((AntSim*)v)->menuAntMoveBeh->value());
        ((AntSim*)v)->updateParams();
    }
}

void AntSim::push_updatePheromoneBehaviour(Fl_Widget *w, void *v)
{
    if (w)
    {
        ((AntSim*)v)->controller->updatePheromoneBehaviour(((AntSim*)v)->menuAntPheroBeh->value());
        ((AntSim*)v)->updateParams();
    }
}

void AntSim::push_updateEnvironmentBehaviour(Fl_Widget *w, void *v)
{
    if (w)
    {
        ((AntSim*)v)->controller->updateEnvironmentBehaviour(((AntSim*)v)->menuEnviroBeh->value());
        ((AntSim*)v)->updateParams();
    }
}

bool AntSim::init()// Set up window and graphics
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

    inputAlpha = new Fl_Input(INPUTFIELD_X, 20, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone importance");//50, 605, 50, 20
    inputAlpha->value("1.0");
    inputBeta = new Fl_Input(INPUTFIELD_X, 50, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Distance importance");
    inputBeta->value("5.0");
    inputEvapRate = new Fl_Input(INPUTFIELD_X, 80, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Evaporation rate");
    inputEvapRate->value("0.01");
    inputPheroNumerator = new Fl_Input(INPUTFIELD_X, 110, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Pheromone numerator");
    inputPheroNumerator->value("100.0");
    inputElitistAnts = new Fl_Input(INPUTFIELD_X, 150, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. elitist ants");
    inputElitistAnts->value("7");
    inputRankedAnts = new Fl_Input(INPUTFIELD_X, 180, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. ranked ants");
    inputRankedAnts->value("5");
    inputMaxPheromone = new Fl_Input(INPUTFIELD_X, 210, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. pheromone");
    inputMaxPheromone->value("20.0");
    inputMinPhermone = new Fl_Input(INPUTFIELD_X, 240, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Min. pheromone");
    inputMinPhermone->value("0.005");
    buttonUpdateParams = new Fl_Button(INPUTFIELD_X - 70, 270, 120, 30, "Update");

    buttonUpdateParams->callback((Fl_Callback *) push_updateParams, this);

    inputNoOfNodes = new Fl_Input(INPUTFIELD_X, 310, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "No. nodes");
    inputNoOfNodes->value("20");
    buttonTSP = new Fl_Round_Button(INPUTFIELD_X - 70, 350, INPUTFIELD_WIDTH, 10, "TSP type map");
    buttonTSP->type(FL_RADIO_BUTTON);
    buttonMaze = new Fl_Round_Button(INPUTFIELD_X - 70, 375, INPUTFIELD_WIDTH, 10, "Maze type map");
    buttonMaze->type(FL_RADIO_BUTTON);
    buttonTSP->setonly();

    buttonGenerateMap = new Fl_Button(INPUTFIELD_X - 70, 400, 120, 30, "Generate map");
    buttonGenerateMap->callback((Fl_Callback *) push_generateMap, this);

    buttonLoadMap = new Fl_Button(INPUTFIELD_X - 70, 440, 120, 30, "Load map");
    buttonLoadMap->callback((Fl_Callback *) push_loadMap, this);

    inputIterations = new Fl_Input(INPUTFIELD_X, 490, INPUTFIELD_WIDTH, INPUTFIELD_HEIGHT, "Max. iterations");
    inputIterations->value("1000");

    buttonRunIteration = new Fl_Button(INPUTFIELD_X - 70, 525, 120, 30, "Run iteration");
    buttonRunIteration->callback((Fl_Callback *) push_runIteration, this);

    buttonRun = new Fl_Button(INPUTFIELD_X - 70, 565, 120, 30, "Run");
    buttonRun->callback((Fl_Callback *) push_run, this);

    menuAntMoveBeh = new Fl_Choice(90, 30, 120, 30, "Move beh");
    menuAntMoveBeh->callback((Fl_Callback *) push_updateMoveBehaviour, this);

    menuAntMoveBeh->add("Ant System", 0, 0);
    menuAntMoveBeh->value(0);

    menuAntPheroBeh = new Fl_Choice(90, 80, 120, 30, "Phero beh");
    menuAntPheroBeh->callback((Fl_Callback *) push_updatePheromoneBehaviour, this);
    menuAntPheroBeh->add("Ant System", 0, 0);
    menuAntPheroBeh->add("Max-min AS", 0, 0);
    menuAntPheroBeh->value(0);

    menuEnviroBeh = new Fl_Choice(90, 130, 120, 30, "Enviro beh");
    menuEnviroBeh->callback((Fl_Callback *) push_updateEnvironmentBehaviour, this);
    menuEnviroBeh->add("Ant System", 0, 0);
    menuEnviroBeh->add("Max-min AS", 0, 0);
    menuEnviroBeh->add("Rank Based AS", 0, 0);
    menuEnviroBeh->value(0);

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
    }*///Doesn't work, don't know why

    projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 20.0f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0));// Look from, look to
    //(for some reason looking at straight down means nothing renders and looking from 0 to 0.1f makes everything backwards)
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

    uniformMatrix = glGetUniformLocation(programID, "matrixTransform");
    if (uniformMatrix  == -1) {

        std::cout << "Could not bind uniform " << uniformMatrix << std::endl;
        return false;
    }

    glUseProgram(programID);

    glUniformMatrix4fv(uniformMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glUseProgram(0);

    controller = new Controller(3, 0, 30, MAPTYPE_MAZE, MAP_GENERATE);

    return true;
}

void AntSim::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    controller->render();

    glUseProgram(0);
}

int AntSim::run()
{
    if (init() == false)
    {
        std::cout << "Initialisation failed" << std::endl;
        return 1;
    }

    Fl::run();

    return 0;
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
