#include "Application.h"
#include <cstdlib>
#include <cstring>

Application::Application()
{
    shaderDir = nullptr;
}

void Application::setShaderDir(const char sDir[])
{
    int size = 0;
    while(sDir[size] != '\0') { size ++; }
    shaderDir = (char *)malloc(sizeof(*sDir) * size);
    strcpy(shaderDir, sDir);

    P_APPINFO("Shader directory : " << shaderDir);
}