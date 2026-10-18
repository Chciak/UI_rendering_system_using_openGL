#pragma once

#include <vector>
#include <glad/gl.h>
#include <GL/glext.h>


#include "Shader.h"

class ShaderProgram
{

    public:
    std::vector<Shader*> shaders;
    GLuint shaderProgram;
    
    ShaderProgram(){};
    
    ShaderProgram(std::vector<Shader*> SHADERS);
    void makeCurrent();

};