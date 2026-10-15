#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GLFWwindow.h"
#include "Application.h"
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


    GLuint renderingProgram = createShaderProgram();
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices ,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader *vert = new Shader(app, APP_VERTEX, "test");
    Shader *frag = new Shader(app, APP_FRAGMENT, "test");
    ShaderProgram *prog = new ShaderProgram({vert, frag});

    glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
    while (!glfwWindowShouldClose(window->window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        prog->makeCurrent();
        glBindVertexArray(vao);
        glPointSize(30.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window->window);
    glfwTerminate();

    delete window;
    return 0;
}