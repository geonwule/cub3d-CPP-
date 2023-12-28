#ifndef EVENT_HPP
#define EVENT_HPP

#include "Glfw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

//image load
static GLuint loadTexture(const char* path);

#include "Event.cpp"

#endif

