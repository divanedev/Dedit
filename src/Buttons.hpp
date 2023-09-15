#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Files.hpp"

float sz = 0.1f;
float CameraX = 0.0, CameraY = 0.0;
int CursorX = 0, CursorY = 0;
float UP = 1.0f / sz - 1;
float LEFT = 1.0f / sz * 528.0f / 261.0f - 1;
float HMUL = 1.0f, WMUL = 1.0f;
GLFWwindow* EditorWindow;

void UpdateLeftAndUp() {
    UP = 1.0f / sz;
    LEFT = 1.0f / sz * 528.0f / 261.0f;
    UP *= HMUL;
    LEFT *= WMUL;
    UP -= 1;
    LEFT -= 1;
}

void CharInput (GLFWwindow* EditorWindow, unsigned int key) {
    std::string s;
    s += (char)key;
    Lines[CursorX].insert(CursorY, s);
    CursorY++;
}

void KeyInput(GLFWwindow* EditorWindow, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_HOME) {
        CursorY = 0;
    }
    if (action == GLFW_PRESS && key == GLFW_KEY_END) {
        CursorY = Lines[CursorX].size();
    }
}

class Key {
public:
    Key(void (*Function)(), int FirstKey, int SecondKey = -1) 
        :m_Time(60), m_FirstKey(FirstKey), m_SecondKey(SecondKey), m_Function(Function) {};
    void Update();
private:
    int m_Time = 60;
    int m_FirstKey = -1;
    int m_SecondKey = -1;
    void (*m_Function)();
};

void CtrlPos () {
    sz *= 1.111f;
    UpdateLeftAndUp();
}

void CtrlNeg () {
    sz *= 0.9f;
    UpdateLeftAndUp();
}

void CtrlO () {
    OpenFile();
}

void CtrlS () {
    SaveFile();
}

void Up () {
    CursorX--;
}

void Down() {
    CursorX++;
}

void Right() {
    CursorY++;
    if (CursorY > (int)Lines[CursorX].size() && CursorX < ((int)Lines.size() - 1)) {
        CursorX++;
        CursorY = 0;
    }
}

void Left () {
    CursorY--;
    if (CursorY < 0 && CursorX > 0) {
        CursorX--;
        CursorY = (int)Lines[CursorX].size();
    }
}

void Enter() {
    int siz = Lines[CursorX].size() - CursorY;
    Lines.insert(Lines.begin() + CursorX + 1, Lines[CursorX].substr(CursorY, siz));
    Lines[CursorX].erase(CursorY, siz);
    CursorX++;
    CursorY = 0;
}

void BackSpace() {
    if (CursorY) { 
        Lines[CursorX].erase(CursorY - 1, 1);
        CursorY--;
    } else {
        std::string s = Lines[CursorX];
        CursorY = Lines[CursorX - 1].size();
        Lines[CursorX - 1] += s;
        Lines.erase(Lines.begin() + CursorX);
        CursorX--;
    }
}

void Key::Update () {
    int state = glfwGetKey(EditorWindow, m_FirstKey);
    int state2 = (m_SecondKey == -1 ? GLFW_PRESS : glfwGetKey(EditorWindow, m_SecondKey));
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (m_Time == 0) {
            m_Function();
            m_Time = 2;
        } else {
            m_Time--;
            if (m_Time % 12 == 11) {
                m_Function();
            }
        }
    } else {
        m_Time = 60;
    }
}

Key Ctrl_Pos(CtrlPos, GLFW_KEY_RIGHT_CONTROL, GLFW_KEY_EQUAL);
Key Ctrl_Neg(CtrlNeg, GLFW_KEY_RIGHT_CONTROL, GLFW_KEY_MINUS);
Key GoUp(Up, GLFW_KEY_UP, -1);
Key GoDown(Down, GLFW_KEY_DOWN, -1);
Key GoRight(Right, GLFW_KEY_RIGHT, -1);
Key GoLeft(Left, GLFW_KEY_LEFT, -1);
Key Backspace (BackSpace, GLFW_KEY_BACKSPACE, -1);
Key EnterKey (Enter, GLFW_KEY_ENTER, -1);
Key Ctrl_O (CtrlO, GLFW_KEY_LEFT_CONTROL, GLFW_KEY_O);
Key Ctrl_S (CtrlS, GLFW_KEY_LEFT_CONTROL, GLFW_KEY_S);

void HandleKeys() {
    Ctrl_Pos.Update();  
    Ctrl_Neg.Update();  
    GoDown.Update();
    GoRight.Update();
    GoUp.Update();
    GoLeft.Update();
    Backspace.Update();
    EnterKey.Update();
    Ctrl_O.Update();
    Ctrl_S.Update();
}