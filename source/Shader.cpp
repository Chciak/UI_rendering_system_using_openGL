#include "Shader.h"
#include "Application.h"
#include "debugInfo.h"
#include <glad/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <string>


static std::map<Shader_T, std::string> fExt = 
{
    {APP_VERTEX, ".vertex"},
    {APP_FRAGMENT, ".fragment"}
};

Shader::Shader(Application *APP, Shader_T TYPE)
{
    type = TYPE;
    app = APP;
}

Shader::Shader(Application *APP, Shader_T TYPE, std::string SHADERNAME)
{
    type = TYPE;
    app = APP;

    std::fstream shaderFile;
    std::string path = std::string(app->shaderDir) + '/' + SHADERNAME + fExt[type];

    shaderFile.open(path, std::ios::in | std::ios::out);

    if(!shaderFile.good()) { P_SHADERINFO("plik " << path << " nie istnieje"); }
    shaderFile.readsome(shader, std::filesystem::file_size(path));
    P_SHADERINFO("Załadowano program :\n" << shader);
}

void Shader::compileShader()
{
    shaderID = glCreateShader(GL_VERTEX_SHADER);

    const char* ptr = shader;
    glShaderSource(shaderID, 1, &ptr, NULL);
    glCompileShader(shaderID);
}