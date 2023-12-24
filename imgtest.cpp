// #include <iostream>
// #include <GLFW/glfw3.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// // 이미지를 텍스처로 변환하는 함수
// GLuint loadTexture(const char* path) {
    
//     int width, height, channels;
//     unsigned char *data = stbi_load(path, &width, &height, &channels, 4); // 4는 RGBA 채널을 나타냅니다.

//     if (!data) {
//         std::cerr << "Failed to load image: " << path << std::endl;
//         return 0;
//     }

//     GLuint textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     stbi_image_free(data);

//     return textureID;
// }

// // compile flag
// // g++ -o imgtest imgtest.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl


// int main() {
//     if (!glfwInit()) {
//         std::cerr << "GLFW initialization failed." << std::endl;
//         return -1;
//     }

//     GLFWwindow* window = glfwCreateWindow(800, 600, "Texture Example", nullptr, nullptr);
//     if (!window) {
//         std::cerr << "Failed to create GLFW window." << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);

//     // 이미지 파일 로드 및 텍스처로 변환
//     GLuint texture = loadTexture("heveuse.png");
//     if (!texture) {
//         glfwDestroyWindow(window);
//         glfwTerminate();
//         return -1;
//     }

//     while (!glfwWindowShouldClose(window)) {
//         glClear(GL_COLOR_BUFFER_BIT);

//         // 텍스처를 사용하여 사각형 그리기
//         glEnable(GL_TEXTURE_2D);
//         glBindTexture(GL_TEXTURE_2D, texture);

//         glBegin(GL_QUADS);
//         glTexCoord2f(0, 0); glVertex2f(-0.5, -0.5);
//         glTexCoord2f(1, 0); glVertex2f(0.5, -0.5);
//         glTexCoord2f(1, 1); glVertex2f(0.5, 0.5);
//         glTexCoord2f(0, 1); glVertex2f(-0.5, 0.5);
//         glEnd();

//         glDisable(GL_TEXTURE_2D);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);
//     glfwTerminate();

//     return 0;
// }


#include <iostream>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint loadTexture(const char* path) {
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

    if (!data) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureID;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed." << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Texture Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLuint texture = loadTexture("heveuse.png");
    if (!texture) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // 정점 좌표와 텍스처 좌표 설정
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,  // 왼쪽 아래
         1.0f, -1.0f, 1.0f, 0.0f,  // 오른쪽 아래
         1.0f,  1.0f, 1.0f, 1.0f,  // 오른쪽 위
        -1.0f,  1.0f, 0.0f, 1.0f   // 왼쪽 위
    };

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex Attribute 설정
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 해제
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
