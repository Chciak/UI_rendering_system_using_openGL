#include "GLFWwindow.h"
#include <iostream>


GLFWWindow::GLFWWindow(int rezx, int rezy)
{
    windowHint = []()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    };

    windowHint();

    window = glfwCreateWindow(rezx, rezy, WINDOW_NAME, NULL, NULL);

    if (!window)
    {
        std::cerr << "Nie udalo sie utworzyc okna GLFW!\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

}

void GLFWWindow::sayHello()
{
    std::cout << "[WINDOW ] : Hello\n"; 
}

GLFWWindow::~GLFWWindow()
{
}
