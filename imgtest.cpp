#include <iostream>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 이미지를 텍스처로 변환하는 함수
GLuint loadTexture(const char* path) {
    
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, 4); // 4는 RGBA 채널을 나타냅니다.

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

// compile flag
// g++ -o imgtest imgtest.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl


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

    // 이미지 파일 로드 및 텍스처로 변환
    GLuint texture = loadTexture("heveuse.png");
    if (!texture) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 텍스처를 사용하여 사각형 그리기
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-0.5, -0.5);
        glTexCoord2f(1, 0); glVertex2f(0.5, -0.5);
        glTexCoord2f(1, 1); glVertex2f(0.5, 0.5);
        glTexCoord2f(0, 1); glVertex2f(-0.5, 0.5);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
