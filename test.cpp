#include <iostream>
#include <GLFW/glfw3.h>

//compile flag
//g++ -o test test.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl


/*
이 코드는 GLFW를 초기화하고 창을 열어 키보드 입력과 마우스 입력을 처리하는
기본적인 예제입니다. GLFW 라이브러리의 초기화, 창 생성, 이벤트 콜백 함수 등이 
포함되어 있습니다. 이 코드를 빌드하고 실행하면 창이 열리며, 
키보드 입력 및 마우스 입력에 대한 정보가 터미널에 출력됩니다.
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << "Left mouse button pressed." << std::endl;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed." << std::endl;
        return -1;
    }

    // Set GLFW to not create an OpenGL context (we're not using it in this example)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Example", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
