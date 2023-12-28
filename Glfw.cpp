#include "Glfw.hpp"
#include "Event.hpp"

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