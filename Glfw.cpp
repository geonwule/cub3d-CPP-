#include "Glfw.hpp"
#include "Event.hpp"

Glfw::Glfw()
{
    std::cout << "[Glfw] Default Constructor Called" << std::endl;

    // 맵데이터 초기화
    mapData = {
        {1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}
        //... 이하 생략
    };

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
    // 맥에서 필수 플래그 공부필요(231229)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "GLFW Example", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        throw(std::logic_error("glfw window"));
    }

    g_texture.push_back(loadTexture("textures/heveuse.png"));
    g_texture.push_back(loadTexture("textures/el.png"));
    for (int i = 0; i < g_texture.size(); i++)
    {
        if (!g_texture[i])
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            throw(std::logic_error("load Texture"));
        }
    }

    // GLFW 창의 OpenGL 컨텍스트를 현재 컨텍스트로 만듭니다.
    glfwMakeContextCurrent(window);
}

void Glfw::_glfwEventRegister()
{
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

void renderTexture(GLuint textureID, int x, int y, float width, float height)
{
    // 적절한 위치에 텍스처를 렌더링하는 코드
    // 쉐이더를 사용하여 좌표 및 크기 조절 가능
    // 간단한 경우에는 glTexCoord 및 glVertex 등을 사용 가능
    // 이 예시에서는 간단한 정사각형을 그리도록 가정
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Glfw::rendering()
{
    glClearColor(0.0f, 0.0f, 1.0f, 2.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int textureIndex = 0; // 표시할 텍스처의 인덱스, 여기서는 textures 벡터의 첫 번째 텍스처를 사용하도록 가정

    // 텍스처의 크기
    int textureWidth = 100;
    int textureHeight = 100;

    // 텍스처를 가운데로 이동하기 위한 좌표 계산
    int x = (WIN_WIDTH - textureWidth) / 2;
    int y = (WIN_HEIGHT - textureHeight) / 2;

    // 텍스처를 지정 위치에 렌더링
    glBindTexture(GL_TEXTURE_2D, g_texture[textureIndex]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2i(x, y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2i(x + textureWidth, y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2i(x + textureWidth, y + textureHeight);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2i(x, y + textureHeight);
    glEnd();

    // // 타일 크기 계산 (가로 세로 각 타일의 크기)
    // float tileWidth = WIN_WIDTH / static_cast<float>(mapData[0].size());
    // float tileHeight = WIN_HEIGHT / static_cast<float>(mapData.size());

    // for (int i = 0; i < mapData.size(); ++i)
    // {
    //     for (int j = 0; j < mapData[i].size(); ++j)
    //     {
    //         int textureIndex = mapData[i][j];
    //         if (textureIndex < g_texture.size())
    //         {
    //             // 타일의 좌표 계산
    //             float tileX = j * tileWidth;
    //             float tileY = WIN_HEIGHT - (i + 1) * tileHeight; // 창 상단이 0이므로 뒤집어주기

    //             renderTexture(g_texture[textureIndex], tileX, tileY, tileWidth, tileHeight);
    //         }
    //     }
    // }

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