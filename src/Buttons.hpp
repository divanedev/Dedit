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
int timerBS = 60, timerUP = 60, timerDW = 60, timerLF = 60, timerRG = 60, timerEN = 60, timerCP = 60, timerCN = 60, timerSV = 60, timerOP = 60;

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

void HandleBackSpace () {
    if (CursorY || CursorX) {
        int state = glfwGetKey(EditorWindow, GLFW_KEY_BACKSPACE);
        // << (state == GLFW_PRESS) << std::endl;
        if (state == GLFW_PRESS) {
            if (timerBS == 0) {
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
                timerBS = 2;
            } else {
                timerBS--;
                if (timerBS % 10 == 9) {
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
                if (timerBS == 0)
                    state = 1;
            }
        } else {
            
            timerBS = 60;
        }
    }
}

void HandleDown () {
    
    if (CursorX != (Lines.size() - 1)) {
        int state = glfwGetKey(EditorWindow, GLFW_KEY_DOWN);
        // << (state == GLFW_PRESS) << std::endl;
        if (state == GLFW_PRESS) {
            if (timerDW == 0) {
                CursorX++;
                timerDW = 2;
            } else {
                timerDW--;
                if (timerDW % 10 == 9) {
                    CursorX++;
                }
            }
        } else {
            
            timerDW = 60;
        }
    }
}

void HandleUp () {
    
    if (CursorX != 0) {
        int state = glfwGetKey(EditorWindow, GLFW_KEY_UP);
        // << (state == GLFW_PRESS) << std::endl;
        if (state == GLFW_PRESS) {
            if (timerUP == 0) {
                CursorX--;
                timerUP = 2;
            } else {
                timerUP--;
                if (timerUP % 10 == 9) {
                    CursorX--;
                }
            }
        } else {
            
            timerUP = 60;
        }
    }
}

void HandleLeft () {
    
    if (CursorY != 0) {
        int state = glfwGetKey(EditorWindow, GLFW_KEY_LEFT);
        // << (state == GLFW_PRESS) << std::endl;
        if (state == GLFW_PRESS) {
            if (timerLF == 0) {
                CursorY--;
                timerLF = 2;
            } else {
                timerLF--;
                if (timerLF % 10 == 9) {
                    CursorY--;
                }
            }
        } else {
            
            timerLF = 60;
        }
    }
}

void HandleRight () {
    
    if (CursorY != (Lines[CursorX].size())) {
        int state = glfwGetKey(EditorWindow, GLFW_KEY_RIGHT);
        // << (state == GLFW_PRESS) << std::endl;
        if (state == GLFW_PRESS) {
            if (timerRG == 0) {
                CursorY++;
                timerRG = 2;
            } else {
                timerRG--;
                if (timerRG % 10 == 9) {
                    CursorY++;
                }
            }
        } else {
            
            timerRG = 60;
        }
    }
}


void HandleEnter () {
    int state = glfwGetKey(EditorWindow, GLFW_KEY_ENTER);
    // << (state == GLFW_PRESS) << std::endl;
    if (state == GLFW_PRESS) {
        if (timerEN == 0) {
            int siz = Lines[CursorX].size() - CursorY;
            
            Lines.insert(Lines.begin() + CursorX + 1, Lines[CursorX].substr(CursorY, siz));
            Lines[CursorX].erase(CursorY, siz);
            CursorX++;
            CursorY = 0;
            timerEN = 2;
        } else {
            timerEN--;
            if (timerEN % 12 == 11) {
                int siz = Lines[CursorX].size() - CursorY;

                Lines.insert(Lines.begin() + CursorX + 1, Lines[CursorX].substr(CursorY, siz));
                Lines[CursorX].erase(CursorY, siz);
                CursorX++;
                CursorY = 0;
            }
        }
    } else {
        
        timerEN = 60;
    }
}

void HandleCtrlNeg () {
    int state = glfwGetKey(EditorWindow, GLFW_KEY_RIGHT_CONTROL);
    int state2 = glfwGetKey(EditorWindow, GLFW_KEY_MINUS);

    // << (state == GLFW_PRESS) << std::endl;
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (timerCN == 0) {
            sz *= 0.9f;
            UpdateLeftAndUp();
            timerCN = 59;
        } else {
            timerCN--;
            if (timerCN % 12 == 11) {
                sz *= 0.9f;
                UpdateLeftAndUp();
            }

        }
    } else {
        
        timerCN = 60;
    }
}

void HandleCtrlPos () {
    int state = glfwGetKey(EditorWindow, GLFW_KEY_RIGHT_CONTROL);
    int state2 = glfwGetKey(EditorWindow, GLFW_KEY_EQUAL);
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (timerCP == 0) {
            sz *= 1.111f;
            UpdateLeftAndUp();
            timerCP = 59;
        } else {
            timerCP--;
            if (timerCP % 12 == 11) {
                sz *= 1.111f;
                UpdateLeftAndUp();
            }
        }
    } else {
        timerCP = 60;
    }
}

void HandleSave () {
    int state = glfwGetKey(EditorWindow, GLFW_KEY_LEFT_CONTROL);
    int state2 = glfwGetKey(EditorWindow, GLFW_KEY_S);
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (timerSV == 60) {
            SaveFile();
        }
        timerSV--;
    } else {
        timerSV = 60;
    }
}

void HandleOpen () {
    int state = glfwGetKey(EditorWindow, GLFW_KEY_LEFT_CONTROL);
    int state2 = glfwGetKey(EditorWindow, GLFW_KEY_O);
    if (state == GLFW_PRESS && state2 == GLFW_PRESS) {
        if (timerOP == 60) {
            OpenFile();
        }
        timerOP--;
    } else {
        timerOP = 60;
    }
}

void HandleKeys() {
    HandleBackSpace();
    HandleUp();
    HandleDown();
    HandleLeft();
    HandleRight();
    HandleEnter();
    HandleCtrlNeg();
    HandleCtrlPos();
    HandleSave();
    HandleOpen();
}