#include "Application.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include "GLFWwindow.h"
#include "debugInfo.h"

Application::Application()
{
    shaderDir = nullptr;
}

void Application::setShaderDir(const char sDir[])
{
    window = nullptr;
    try {
        window = new GLFWWindow(XREZ, YREZ);
    } catch (const std::exception& e) {
        std::cerr << "Blad inicjalizacji okna: " << e.what() << std::endl;
    }

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
        glfwSwapBuffers(window->window);
        glfwPollEvents();
    };

    onQuit = [this] ()
    {
        delete this->window;
        glfwDestroyWindow(this->window->window);
        glfwTerminate();
    };
}