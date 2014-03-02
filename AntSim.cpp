#include "AntSim.h"

AntSim::AntSim()
{
	window = NULL;

    programID = 0;
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

    window = SDL_CreateWindow("AntSim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window == NULL) {

        std::cout << "Window could not be created, error: " << SDL_GetError() << std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);

    if (context == NULL) {

        std::cout << "OpenGL context could not be created, error: " << SDL_GetError() << std::endl;
        return false;
    }

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
    }*/

    projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0, 1, 0));// Look from, look to
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

    controller = new Controller(31);

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
    glDeleteProgram(programID);

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

int AntSim::run()
{
    if (init() == false)
    {
        std::cout << "Initialisation failed" << std::endl;
        close();
        return 1;
    }

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
        SDL_GL_SwapWindow(window);
    }

    SDL_StopTextInput();
    close();

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
