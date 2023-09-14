#pragma once

#include <GL/glew.h>
#include "Buttons.hpp"
int frame = 0;
unsigned int va, vb, ib;
unsigned int Shader;
const int OUP = 3, OLEFT = 3;

void draw () {
    frame++;
    HandleKeys();
    sz = std::max(sz, 0.06f);
    sz = std::min(sz, 0.3f);
    UpdateLeftAndUp();
    CursorX = std::min(CursorX, (int)Lines.size() - 1);
    CursorX = std::max(CursorX, 0);
    CursorY = std::min(CursorY, (int)Lines[CursorX].size());
    CursorY = std::max(CursorY, 0);
    float CAMX = CameraX / sz + HMUL / sz;
    float CAMY = CameraY / sz + WMUL / sz;
    int MxSz = (int)(std::to_string((int)Lines.size() - 1)).size();
    float MXSZ = MxSz;
    float CursornX = CursorX;
    float CursornY = CursorY + MxSz + 1;
    float MinY = MxSz + 1;
    CAMY *= 528.0f / 261.0f;
    if (CursornX < CAMX - UP - HMUL) {
        CAMX = CursornX + UP + HMUL;
    }
    if (CursornX > CAMX + UP) {
        CAMX = CursornX - UP;
    }
    if (CursornY < CAMY - LEFT + MXSZ) {
        CAMY = CursornY + LEFT - MXSZ;
    }
    if (CursornY > CAMY + LEFT) {
        CAMY = CursornY - LEFT;
    }
    CAMY *= 261.0f / 528.0f;
    CAMY -= WMUL / sz;
    CAMX -= HMUL / sz;
    CameraX = CAMX * sz;
    CameraY = CAMY * sz;
//    std::cout << CameraX << ' ' << CameraY << std::endl;
//    CameraX = CameraY = 0;
    CursornX = CameraX / sz + HMUL / sz;
    CursornY = CameraY / sz + WMUL / sz;
    CursornY *= 528.0f / 261.0f;
    int NumberOfChars = 0;
    for (int i = 0; i < (Lines.size()); i++) {
        if (abs(CursornX - i) <= UP + OUP) {
            NumberOfChars += MxSz + 1;
            for (int j = MxSz + 1; j < Lines[i].size() + MxSz + 1; j++) {
                if (abs (CursornY - (j)) <= LEFT + OLEFT && CursornY - (j) <= LEFT - MxSz + 1)
                    NumberOfChars++;
            }
        }
    }
    // << NumberOfChars << '\n';
    
    float newPositions [16 + NumberOfChars * 16];
    unsigned int newElements [6 + NumberOfChars * 6];
    NumberOfChars = 1;
    for (int i = 0; i < (Lines.size()); i++) {
        if (!(abs(CursornX - i) <= UP + OUP))
            continue;
        std::string S = std::to_string(i);
        while (S.size() < MxSz) {
            S = ' ' + S;
        }
        S += (' ');
        for (int j = 0; j < (S.size()); j++) {
            // if (!(abs(CursornX - i) <= UP + 5 && abs (CursornY - j) <= LEFT + 5))
            //     continue;
            int x, y;
            int Code = S[j] - ' ';
            y = Code / 11;
            x = Code % 11;
            y = 8 - y;
            float wy = -sz * (i + 1) + HMUL;
            float wx = sz * (j) * 261.0f / 528.0f - WMUL;
            float newChar [16] = {
                CameraY + wx + 261.0f / 528.0f * sz, wy, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * y,
                CameraY + wx, wy, 1.0f / 11.0f * x, 1.0f / 9.0f * y,
                CameraY + wx, wy + sz, 1.0f / 11.0f * x, 1.0f / 9.0f * (y + 1),
                CameraY + wx + 261.0f / 528.0f * sz, wy + sz, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * (y + 1)
            };
            for (int k = 0; k < 16; k++) {
                newPositions[NumberOfChars * 16 + k] = newChar[k];
            }
            for (int k = 0; k < 6; k++) {
                newElements[NumberOfChars * 6 + k] = NumberOfChars * 4 + (k < 3 ? k : (k < 5 ? k - 1 : 0));
            }
            // << NumberOfChars << '\n';
            NumberOfChars++;
        }
        for (int j = 0; j < (Lines[i].size()); j++) {
            if (!(abs (CursornY - (j + MxSz + 1)) <= LEFT + OLEFT && CursornY - (j + MxSz + 1) <= LEFT - MxSz + 1))
                continue;
            int x, y;
            int Code = Lines[i][j] - ' ';
            y = Code / 11;
            x = Code % 11;
            y = 8 - y;
            float wy = -sz * (i + 1) + HMUL;
            float wx = sz * (MxSz + 1 + j) * 261.0f / 528.0f - WMUL;
            float newChar [16] = {
                wx + 261.0f / 528.0f * sz, wy, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * y,
                wx, wy, 1.0f / 11.0f * x, 1.0f / 9.0f * y,
                wx, wy + sz, 1.0f / 11.0f * x, 1.0f / 9.0f * (y + 1),
                wx + 261.0f / 528.0f * sz, wy + sz, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * (y + 1)
            };
            for (int k = 0; k < 16; k++) {
                newPositions[NumberOfChars * 16 + k] = newChar[k];
            }
            for (int k = 0; k < 6; k++) {
                newElements[NumberOfChars * 6 + k] = NumberOfChars * 4 + (k < 3 ? k : (k < 5 ? k - 1 : 0));
            }
            // << NumberOfChars << '\n';
            NumberOfChars++;
        }
    }
    float wy = -sz * (CursorX + 1) + HMUL;
    float wx = sz * (MxSz + 1 + CursorY) * 261.0f / 528.0f - WMUL;
    int x = 10;
    int y = 0;
    if (frame % 70 < 35) {
        x -= 2;
    }
    float CursorPosition[16] = {
        wx + 26.0f / 528.0f * sz, wy, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * y,
        wx, wy, 1.0f / 11.0f * x, 1.0f / 9.0f * y,
        wx, wy + sz, 1.0f / 11.0f * x, 1.0f / 9.0f * (y + 1),
        wx + 26.0f / 528.0f * sz, wy + sz, 1.0f / 11.0f * (x + 1), 1.0f / 9.0f * (y + 1)
    };

    for (int i = 0; i < 16; i++) {
        newPositions[i] = CursorPosition[i];
    }
    for (int i = 0; i < NumberOfChars * 16; i += 4) {
        newPositions[i] -= CameraY;
        newPositions[i + 1] += CameraX;
        newPositions[i] /= WMUL;
        newPositions[i + 1] /= HMUL; 
    }

    newElements[0] = 0;
    newElements[1] = 1;
    newElements[2] = 2;
    newElements[3] = 2;
    newElements[4] = 3;
    newElements[5] = 0;

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Shader);
    glBindVertexArray(va);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);


    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newPositions), newPositions);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(newElements), newElements);
    glDrawElements(GL_TRIANGLES, NumberOfChars * 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(EditorWindow);
    glfwPollEvents();
}
