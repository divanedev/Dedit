#include <X11/Xlib.h>
#include <iomanip>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Debug.hpp"
#include "Buttons.hpp"
#include "Files.hpp"
#include "Render.hpp"

int main () {

    Lines.push_back("");
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    std::cout << "Screen Resoultion : " << s->height << " * " << s->width << std::endl;
    WEF = ((float)s->height * (float)s->width) / (640.0f * 640.0f);

    Init();

    unsigned int TXT = CreateTexture("../res/textures/TXT.png");

    BindTexture(TXT, 0);
    glClearColor(0.4f, 0.38f, 0.98f, 0);
    while (!glfwWindowShouldClose(EditorWindow)) {
        Draw();
    }

    glfwTerminate();
}