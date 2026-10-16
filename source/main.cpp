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

    Application *app = new Application();
    app->setShaderDir("shader");
    
    if (!glfwInit())
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW!\n";
        return -1;
    }

    GLFWWindow *window = new GLFWWindow(800, 600);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD!\n";
        glfwTerminate();
        return -1;
    }

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // float vertices[] = {
    // -0.5f, -0.5f, 0.0f,
    //  0.5f, -0.5f, 0.0f,
    //  0.0f,  0.5f, 0.0f
    // };  

    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices ,GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    
    Shader vert {app, APP_VERTEX, "test"};
    Shader frag {app, APP_FRAGMENT, "test"};
    ShaderProgram prog {{&vert, &frag}};

    std::vector<MeshData<3>> mesh1 = {
        {{-0.5f, -0.5f, 0.0f}, {{1.0f, 0.0f, 0.0f}}},
        {{0.5f, -0.5f, 0.0f}, {{0.0f, 1.0f, 0.0f}}},
        {{0.0f,  0.5f, 0.0f}, {{0.0f, 0.0f, 1.0f}}}
    };

    MeshObject<3, BASIC> triangle{prog, mesh1};

    glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
    while (!glfwWindowShouldClose(window->window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // glBindVertexArray(vao);
        // prog.makeCurrent();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        triangle.render();

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window->window);
    glfwTerminate();

    delete window;
    return 0;
}