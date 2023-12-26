#ifndef GLFW_HPP
#define GLFW_HPP

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

class Glfw
{
private:
    Glfw(const Glfw &other);
    Glfw &operator=(const Glfw &other);

    GLFWwindow *window;

public:
    Glfw();
    ~Glfw();

    void _glfwInit();
    void _glfwEventRegister();
    void _glfwRederingLoop();
};

#endif