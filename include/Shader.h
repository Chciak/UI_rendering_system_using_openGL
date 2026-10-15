#pragma once

#include <string>
#include <glad/gl.h>
#include <GL/glext.h>

#include "Application.h"

#define MAX_SHADER_SIZE 1024

enum Shader_T
{
    APP_VERTEX = GL_VERTEX_SHADER,
    APP_FRAGMENT = GL_FRAGMENT_SHADER
};

class Shader
{
    Application *app;
    Shader_T type;
    char shader[MAX_SHADER_SIZE];
    
    public:

    unsigned int shaderID;
    Shader();
    Shader(Application *app, Shader_T type);
    Shader(Application *app, Shader_T type, std::string shaderName);
    void compileShader();

};