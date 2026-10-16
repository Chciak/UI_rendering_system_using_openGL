#pragma once

#include <functional>
#include <iostream>
#include <GLFW/glfw3.h>

#define WINDOW_NAME "UI_APP"

class GLFWWindow
{
    public :
    GLFWwindow* window;
    std::function<void()> windowHint;

    GLFWWindow(){};
    GLFWWindow(int rezx,int rezy);
    ~GLFWWindow();
};