#pragma once

#include <string>
#include <glad/gl.h>
#include <GL/glext.h>

#include "Application.h"

#define MAX_SHADER_SIZE 1024

enum Shader_T
{
    APP_VERTEX = 0x8B31,
    APP_FRAGMENT = 0x8B30
};

class Shader
{
    Application *app;
    Shader_T type;

    unsigned int shaderID;
    char shader[MAX_SHADER_SIZE];
    
    public:
    Shader();
    Shader(Application *app, Shader_T type);
    Shader(Application *app, Shader_T type, std::string shaderName);
    void compileShader();

};