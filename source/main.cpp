#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GLFWwindow.h"
#include "Application.h"
#include "MeshObject.h"
#include "Shader.h"
#include "ShaderProgram.h"

int init()
{
    if (!glfwInit())
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW!\n";
        return -1;
    }

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD!\n";
        glfwTerminate();
        return -1;
    }
}

int main()
{
    
    if(!init()) return -1;

    Application app{};
    app.setShaderDir("shader");
    
    Shader vert {&app, APP_VERTEX, "test"};
    Shader frag {&app, APP_FRAGMENT, "test"};
    ShaderProgram prog {{&vert, &frag}};

    std::vector<MeshData<3>> mesh1 = {
        {{-0.5f, -0.5f, 0.0f}, {{1.0f, 0.0f, 0.0f}}},
        {{0.5f, -0.5f, 0.0f}, {{0.0f, 1.0f, 0.0f}}},
        {{0.0f,  0.5f, 0.0f}, {{0.0f, 0.0f, 1.0f}}}
    };
    MeshObject<3, BASIC> triangle{prog, mesh1};

    app.prepress();
    while (!glfwWindowShouldClose(app.window->window))
    {
        triangle.render();
        app.postpress();
    }
    app.onQuit();

    return 0;
}