#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GLFWwindow.h"
#include "Application.h"
#include "MeshObject.h"
#include "Shader.h"
#include "ShaderProgram.h"

int main()
{
   
    if (!glfwInit())
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW!\n";
        return -1;
    }

    Application app{};
    app.setShaderDir("shader");
    
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD!\n";
        glfwTerminate();
        return -1;
    }    
    
    Shader vert {&app, APP_VERTEX, "test"};
    Shader frag {&app, APP_FRAGMENT, "test"};
    ShaderProgram prog {{&vert, &frag}};

    std::vector<MeshData<3>> mesh = {
        {{ 0.5f,  0.5f, 0.0f},{{1.0f, 0.0f, 0.0f}}},
        {{ 0.5f, -0.5f, 0.0f},{{0.0f, 1.0f, 0.0f}}},
        {{-0.5f, -0.5f, 0.0f},{{0.0f, 1.0f, 0.0f}}},
        {{-0.5f,  0.5f, 0.0f},{{0.0f, 0.0f, 1.0f}}}
    };

    std::vector<int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    std::vector<glm::mat4> transformation
    {

        glm::mat4(
        0.3f, 0.0f, 0.0f, 0.0f,  // 1. kolumna
        0.0f, 0.3f, 0.0f, 0.0f,  // 2. kolumna
        0.0f, 0.0f, 0.3f, 0.0f,  // 3. kolumna
        0.0f, 0.0f, 0.0f, 1.0f   // 4. kolumna
        ),

        glm::mat4(
        0.3f, 0.0f, 0.0f, 0.0f,  // 1. kolumna
        0.0f, 0.3f, 0.0f, 0.0f,  // 2. kolumna
        0.0f, 0.0f, 0.3f, 0.0f,  // 3. kolumna
        0.5f, 0.5f, 0.0f, 1.0f   // 4. kolumna
        ),

        glm::mat4(
        0.3f, 0.0f, 0.0f, 0.0f,  // 1. kolumna
        0.0f, 0.3f, 0.0f, 0.0f,  // 2. kolumna
        0.0f, 0.0f, 0.3f, 0.0f,  // 3. kolumna
        0.0f, 0.5f, 0.0f, 1.0f   // 4. kolumna
        )

    };

    MeshObject<3, INSTANCED, false> triangle{prog, mesh, indices, transformation};

    app.prepress();
    while (!glfwWindowShouldClose(app.window->window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        triangle.render();
        app.postpress();
    }
    app.onQuit();

    return 0;
}