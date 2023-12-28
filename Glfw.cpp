#include "Glfw.hpp"
#include "Event.hpp"

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

    // // 아래 코드가 없으면 창이 바로 안열리고, 창을 끌때 segfault가 뜸
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // OpenGL 버전 및 프로파일 설정 (코어 프로파일이 권장됨)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW Example", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        throw(std::logic_error("glfw window"));
    }

    // GLFW 창의 OpenGL 컨텍스트를 현재 컨텍스트로 만듭니다.
    glfwMakeContextCurrent(window);
    img_texture = loadTexture("heveuse.png");
    if (!img_texture) {
        glfwDestroyWindow(window);
        glfwTerminate();
        throw(std::logic_error("load Texture"));
    }
    

    // GLEW 또는 다른 OpenGL 로더 초기화 (필요한 경우)
    // ...

    // 아래 코드는 ESC 키 입력을 감지하기 위해 필요합니다.
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void Glfw::_glfwEventRegister()
{
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

void Glfw::rendering()
{
    glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, img_texture);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glfwSwapBuffers(window);
}

void Glfw::_glfwRederingLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        // window 그려주기
        rendering();

        // 마우스 움직이는 것. 이런것들 들고와서 필요한 window한테 보내주기
        glfwPollEvents();
    }
}