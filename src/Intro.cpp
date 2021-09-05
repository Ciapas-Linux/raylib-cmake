//
// Created by kot on 30.08.2021.
//

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"


#include "Intro.h"


Intro::Intro (int gw, int gh, const char *title)
{

    // config flags for raylib
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);


    // fullscreen flag ensure that we got full screen
    // for mobile devices so gw, and gh does nothing here.
    // if you set fullscreen to false then you can
    // select gw and gh dimensions, like before.
    InitWindow(gw, gh, title,false);

    // Create the Nuklear Context
    int fontSize = 20;
    ctx = InitNuklear(fontSize);


    
    // Notepad:
    // int display = GetCurrentMonitor();
    // SetWindowSize(screenWidth, screenHeight);
    // SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    // if(IsWindowResized() && !IsWindowFullscreen())
    // {
    //     screenWidth = GetScreenWidth();
    //     screenHeight = GetScreenHeight();
    // }


    // get real size of mobile device screen.
    int height = GetScreenHeight();
    int width = GetScreenWidth();

    // example billboard image file.
    bill = LoadTexture("ciapas.png");

    camera.position = (Vector3){ 3.0f, 1.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    EnableCursor();

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60);
}

void Intro::UpdateKeyboard()
{
    if (IsKeyDown(KEY_LEFT))
    {
        camera.position.z += 0.02f;
        camera.target.z += 0.02f;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        camera.position.z -= 0.02f;
        camera.target.z -= 0.02f;
    }

    if (IsKeyDown(KEY_UP))
    {
        camera.position.x -= 0.02f;
        camera.target.x -= 0.02f;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        camera.position.x += 0.02f;
        camera.target.x += 0.02f;
    }

}

void Intro::DrawHUD()
{
    snprintf( chbuf_mouseX, 5 + 1, "%d", GetMouseX() );
    snprintf( chbuf_mouseY, 5 + 1, "%d", GetMouseY() );
    DrawText("Movie studio v0.001", 10, 70, 60, GREEN);
    DrawText(chbuf_mouseX, 10, 140, 60, GREEN);
    DrawText(chbuf_mouseY, 10, 200, 60, GREEN);
    DrawFPS(10, 10);
}

void Intro::Draw3D()
{
    BeginMode3D(camera);

        DrawLine3D(XAxisLineStart ,XAxisLineEnd, BLUE);
        DrawSphere(center, 0.05f, PURPLE);
        DrawCube(XAxisPointPosition, 0.05f, 0.05f, 0.05f, GREEN);
        DrawCube(YAxisPointPosition, 0.05f, 0.05f, 0.05f, RED);
        DrawCube(ZAxisPointPosition, 0.05f, 0.05f, 0.05f, BLUE);
        DrawCubeWires(cubePosition, 0.5f, 0.5f, 0.5f, MAROON);
        DrawGrid(20, 1.0f);
        DrawBillboard(camera, bill, billPosition, 2.0f, WHITE);

    EndMode3D();
}

void Intro::Draw()
{
    BeginDrawing();

        ClearBackground(BLACK);

        Draw3D();
        DrawHUD();

        // Render the Nuklear GUI
        DrawNuklear(ctx);

    EndDrawing();
}

void Intro::Run()
{
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateNuklear(ctx);

        // Nuklear GUI Code
        // https://github.com/Immediate-Mode-UI/Nuklear/wiki/Window
        if (nk_begin(ctx, "Window", nk_rect(100, 100, 280, 280),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE))
        {
            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
            {
        
            }
        }
        nk_end(ctx);


        UpdateKeyboard();
        UpdateCamera(&camera);
        Draw();
    }

    // free memory data
    CleanResources();
    CloseWindow();
}

void Intro::CleanResources()
{
    UnloadNuklear(ctx);
    UnloadTexture(bill);
 
}
