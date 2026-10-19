#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        {{-1.0f,  1.0f, 0.0f}, {{0.0f, 1.0f, 0.0f}}},
        {{-1.0f, -1.0f, 0.0f}, {{0.0f, 0.0f, 0.0f}}},
        {{ 1.0f, -1.0f, 0.0f}, {{1.0f, 0.0f, 0.0f}}},
        {{ 1.0f,  1.0f, 0.0f}, {{1.0f, 1.0f, 0.0f}}}
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    std::vector<glm::mat4> transformation
    {
        //glm::mat4(1.0f),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f)),
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