#pragma once

#include <iostream>

#include "debugInfo.h"\

class Application
{

    public:
    char *shaderDir;
    
    Application();
    void setShaderDir(const char sDir[]);  

};