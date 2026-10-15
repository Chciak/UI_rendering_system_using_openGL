#include "Shader.h"
#include "Application.h"
#include "debugInfo.h"
#include <iostream>
#include <fstream>
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

    int bufCout = 0;
    char buf[MAX_SHADER_SIZE];
    std::fstream shaderFile;
    std::string path = std::string(app->shaderDir) + '/' + SHADERNAME + fExt[type];

    shaderFile.open(path, std::ios::in | std::ios::out);

    if(!shaderFile.good())
    {
        P_SHADERINFO("plik " << path << " nie istnieje");
    }

    
}