#pragma once

#include <GL/gl.h>
#include <GL/glext.h>
#include <string>

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

    GLuint shaderID;
    char shaderProgram[];
    
    public:
    Shader();
    Shader(Application *app, Shader_T type);
    Shader(Application *app, Shader_T type, std::string shaderName);

};