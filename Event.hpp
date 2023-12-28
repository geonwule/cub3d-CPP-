#ifndef EVENT_HPP
#define EVENT_HPP

#include "Glfw.hpp"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

#include "Event.cpp"

#endif

