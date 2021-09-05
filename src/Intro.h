//
// Created by kot on 30.08.2021.
//

#ifndef CIAPASGFX_INTRO_H
#define CIAPASGFX_INTRO_H

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

class Intro
{
public:
    Texture2D bill{};
    Vector3 billPosition = { 0.0f, 0.0f, 0.0f };
    Camera camera = { 0 };
    Vector3 XAxisLineStart = { 0.0f, 0.0f, 0.0f };
    Vector3 XAxisLineEnd = { 1.0f, 0.0f, 0.0f };
    Vector3 XAxisPointPosition = { 1.0f, 0.0f, 0.0f };
    Vector3 YAxisPointPosition = { 0.0f, 1.0f, 0.0f };
    Vector3 ZAxisPointPosition = { 0.0f, 0.0f, 1.0f };
    Vector3 cubePosition = { 0 };
    Vector3 center = { 0 };
    Vector2 MousePosition = { 0.0f, 0.0f };
    char chbuf_mouseX[10]{};
    char chbuf_mouseY[10]{};

    struct nk_context *ctx;

    Intro(int gw, int gh, const char* title);

    void Run();
    void UpdateKeyboard();
    void Draw3D();
    void Draw();
    void DrawHUD();
    void CleanResources();

};


#endif //CIAPASGFX_INTRO_H
