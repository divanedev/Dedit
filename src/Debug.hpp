#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void APIENTRY OpenGlErrorHappend (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data) {
    std::cout << "OpenGL Error : " << source << ' ' << type << ' ' << id << ' ' << severity << ' ' << length << ' ' << msg << ' ' << data << std::endl;
}

void GlfwErrorHappened (int code, const char* notes) {
    std::cout << "GLFW Error : " << code << ' ' << notes << std::endl;
}
