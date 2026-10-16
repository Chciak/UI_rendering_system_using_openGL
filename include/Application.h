#pragma once

#include "GLFWwindow.h"
#include <functional>

#define CLEA_COLOUR 0.33f, 0.33f, 0.33f, 1.0f
#define XREZ 800
#define YREZ 600

class Application
{

    public:
    char *shaderDir;
    GLFWWindow *window;
    
    Application();
    void setShaderDir(const char sDir[]);  
    std::function<void()> prepress;
    std::function<void()> postpress;
    std::function<void()> onQuit;
};