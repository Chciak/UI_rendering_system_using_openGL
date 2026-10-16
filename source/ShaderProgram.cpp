#include "ShaderProgram.h"
#include "Shader.h"
#include <GL/gl.h>
#include <iostream>

ShaderProgram::ShaderProgram(std::vector<Shader*> SHADERS)
    :shaders(SHADERS)
{
    int success;
    char infoLog[512];

    shaderProgram = glCreateProgram();

    for(int i = shaders.size() -1; i >= 0; i--)
    {
        glAttachShader(shaderProgram, shaders.at(i)->shaderID);
    }

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    for(int i = 0; i < SHADERS.size(); i++)
    {
        glDeleteShader(SHADERS.at(i)->shaderID);
    }

    glUseProgram(shaderProgram);
}

void ShaderProgram::makeCurrent()
{
    glUseProgram(shaderProgram);
}