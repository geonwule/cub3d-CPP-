#include "Glfw.hpp"

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

Glfw::Glfw(const Glfw &other)
{
    std::cout << "[Glfw] Copy Constructor Called" << std::endl;
    // Copy member variables here
}

Glfw &Glfw::operator=(const Glfw &other)
{
    std::cout << "[Glfw] Copy Assignment Called" << std::endl;
    if (this != &other)
    {
        // Copy member variables here
    }
    return *this;
}

Glfw::Glfw()
{
    std::cout << "[Glfw] Default Constructor Called" << std::endl;

    _glfwInit();
    _glfwEventRegister();
    _glfwRederingLoop();
}

Glfw::~Glfw()
{
    std::cout << "[Glfw] Destructor Called" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Glfw::_glfwInit()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed." << std::endl;
        throw(std::logic_error("glfw init"));
    }

    // 아래 코드가 없으면 창이 바로 안열리고, 창을 끌때 segfault가 뜸
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW Example", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        throw(std::logic_error("glfw window"));
    }
}

void Glfw::_glfwEventRegister()
{
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Glfw::_glfwRederingLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        //rendering
    }
}