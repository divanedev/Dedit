#include <X11/Xlib.h>
#include <iomanip>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Debug.hpp"
#include "Buttons.hpp"
#include "Files.hpp"
#include "Draw.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    HMUL = (float)height / 640.0f;
    WMUL = (float)width / 640.0f;
    UpdateLeftAndUp();
    glViewport(0, 0, width, height);
    draw();
}

int main () {

    Lines.push_back("");
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    std::cout << "Screen Resoultion : " << s->height << " * " << s->width << std::endl;
    float WEF = ((float)s->height * (float)s->width) / (640.0f * 640.0f);
    int GlfwMajorVersion, GlfwMinorVersion, GlfwRevision;

    glfwGetVersion(&GlfwMajorVersion, &GlfwMinorVersion, &GlfwRevision);
    std::cout << std::endl;
    std:: cout << "GLFW version : " << ' ' << GlfwMajorVersion << "." << GlfwMinorVersion << ' ' << GlfwRevision << std::endl;
    
    std::cout << std::endl;
    if (!glfwInit()) {
        std::cout << "GLFW did not start properly!" << std::endl;
        return -1;
    }

    glfwSetErrorCallback(GlfwErrorHappened);

    EditorWindow = glfwCreateWindow(640, 640, "Dedit", NULL, NULL);

    if (!EditorWindow) {
        std::cout << "EditorWindow did not start correctly!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(EditorWindow);
    glfwSetFramebufferSizeCallback(EditorWindow, framebuffer_size_callback);
    glfwSwapInterval(1);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwSetWindowSizeLimits(EditorWindow, 300, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetCharCallback(EditorWindow, CharInput);
    glfwSetKeyCallback(EditorWindow, KeyInput);

    if (glewInit() != GLEW_OK) {
        std::cout << "Coud not Initilize GLEW" << std::endl;
    }

    glEnable(GL_DEBUG_OUTPUT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDebugMessageCallback(OpenGlErrorHappend, NULL);

    glGenVertexArrays(1, &va);
    glBindVertexArray(va);

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, WEF * 53 * 53 * 4 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, WEF * 53 * 53 * 2 * 3 * sizeof (unsigned int), nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    std::pair <std::string, std::string> p = ParseShader("../res/shaders/basic.shader");

    std::string VertexShaderCode = p.first;
    std::string FragmentShaderCode = p.second;

    Shader = CreateShaderProgram(VertexShaderCode, FragmentShaderCode);

    glUseProgram(0);

    unsigned int TXT = CreateTexture("../res/textures/TXT.png");

    BindTexture(TXT, 0);
    glClearColor(0.4f, 0.38f, 0.98f, 0);
    while (!glfwWindowShouldClose(EditorWindow)) {
        draw();
    }

    glfwTerminate();
}
