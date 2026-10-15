#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GLFWwindow.h"
#include "Application.h"
#include "Shader.h"

GLuint createShaderProgram()
{
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    return vfProgram;
}

int main()
{

    Application *app = new Application();
    app->setShaderDir("shader");

    Shader *vert = new Shader(app, APP_VERTEX, "test");

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

    glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
    while (!glfwWindowShouldClose(window->window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(renderingProgram);
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