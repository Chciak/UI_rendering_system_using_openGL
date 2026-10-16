#include "Application.h"
#include <cstdlib>
#include <cstring>

#include "debugInfo.h"

Application::Application()
{
    shaderDir = nullptr;
}

void Application::setShaderDir(const char sDir[])
{
    window = new GLFWWindow(XREZ, YREZ);
    int size = 0;
    while(sDir[size] != '\0') { size ++; }
    shaderDir = (char *)malloc(sizeof(*sDir) * size);
    strcpy(shaderDir, sDir);

    P_APPINFO("Shader directory : " << shaderDir);

    prepress = []()
    {
        glClearColor(CLEA_COLOUR);
    };

    postpress = [this]()
    {
        glfwSwapBuffers(this->window->window);
        glfwPollEvents();
    };

    onQuit = [this] ()
    {
        delete this->window;
        glfwDestroyWindow(this->window->window);
        glfwTerminate();
    };
}