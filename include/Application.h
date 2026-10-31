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
    char *textureDir;
    char *meshDir;

    GLFWWindow *window;
    
    Application();
    void setShaderDir(const char sDir[]);  
    void setTextureDir(const char tDir[]);
    void setMeshDir(const char mDir);

    virtual inline void prepress();
    virtual inline void postpress();
    virtual inline void onQuit();
};