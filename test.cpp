#include <iostream>
#include <GLFW/glfw3.h>

// compile flag
// g++ -o test test.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

/*
이 코드는 GLFW를 초기화하고 창을 열어 키보드 입력과 마우스 입력을 처리하는
기본적인 예제입니다. GLFW 라이브러리의 초기화, 창 생성, 이벤트 콜백 함수 등이
포함되어 있습니다. 이 코드를 빌드하고 실행하면 창이 열리며,
키보드 입력 및 마우스 입력에 대한 정보가 터미널에 출력됩니다.
*/

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // WASD 키에 대한 예제
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        std::cout << "W key pressed." << std::endl;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        std::cout << "A key pressed." << std::endl;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        std::cout << "S key pressed." << std::endl;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        std::cout << "D key pressed." << std::endl;

    // SPACE 키에 대한 예제
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        std::cout << "Space key pressed." << std::endl;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << "Left mouse button pressed." << std::endl;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed." << std::endl;
        return -1;
    }

    // Set GLFW to not create an OpenGL context (we're not using it in this example)
    // 아래 코드가 없으면 창이 바로 안열리고, 창을 끌때 segfault가 뜸
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Example", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        std::cout << ++i << '\n';
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "normal end\n";

    return 0;
}
