#include "Event.hpp"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // WASD 키에 대한 예제
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        std::cout << "W key pressed." << std::endl;
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        std::cout << "A key pressed." << std::endl;
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        std::cout << "S key pressed." << std::endl;
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        std::cout << "D key pressed." << std::endl;

    // SPACE 키에 대한 예제
    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
        std::cout << "Space key pressed." << std::endl;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << "Left mouse button pressed." << std::endl;
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}