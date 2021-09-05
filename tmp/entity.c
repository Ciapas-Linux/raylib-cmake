/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

typedef struct 
{
    bool Active;
    Vector2 Postion;
    Vector2 Direction;
    float Lifetime;
    Color Tint;
}Entity;

#define MAX_ENTITIES 100


const int screenWidth = 800;
const int screenHeight = 450;

Entity Bullets[MAX_ENTITIES];
Entity Baddies[MAX_ENTITIES];

float ShotSpeed = 200;
float ShotLifetime = 5;
Vector2 BaddieSize = { 25, 25 };
float BaddieSpeed = 100;
int Score = 0;

int FindEmptyEntity(Entity* list)
{
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (!list[i].Active)
            return i;
    }

    return -1;
}

int NewBullet(Vector2 postion, Vector2 direction, float lifetime, Color tint)
{
    int id = FindEmptyEntity(Bullets);
    if (id == -1)
        return -1; // nope

    Bullets[id].Active = true;
    Bullets[id].Postion = postion;
    Bullets[id].Direction = direction;
    Bullets[id].Lifetime = lifetime;
    Bullets[id].Tint = tint;

    return id;
}

int NewBaddie(Vector2 postion, Vector2 direction, float lifetime, Color tint)
{
    int id = FindEmptyEntity(Baddies);
    if (id == -1)
        return -1; // nope

    Baddies[id].Active = true;
    Baddies[id].Postion = postion;
    Baddies[id].Direction = direction;
    Baddies[id].Lifetime = lifetime;
    Baddies[id].Tint = tint;

    return id;
}

void UpdateBullet(int id)
{
    Bullets[id].Lifetime -= GetFrameTime();    // expire shots
    if (Bullets[id].Lifetime <= 0)
    {
        Bullets[id].Active = false;
        return;
    }
    Bullets[id].Postion = Vector2Add(Bullets[id].Postion, Vector2Scale(Bullets[id].Direction, GetFrameTime()));
}

void RandomBaddie()
{
    // new baddie

    int xPos = GetRandomValue(800, 900);
    int yPos = GetRandomValue(0, screenHeight - (int)BaddieSize.y);
    NewBaddie((Vector2) { (float)xPos, (float)yPos }, (Vector2) { (float)(-BaddieSpeed), 0 }, GetRandomValue(0, 1000)/ 1000.0f, MAROON);
}

void UpdateBaddie(int id)
{
    if (Baddies[id].Lifetime < 0)
    {
        Baddies[id].Active = false;
        return;
    }

    Baddies[id].Lifetime += GetFrameTime();
    Baddies[id].Postion = Vector2Add(Baddies[id].Postion, Vector2Scale(Baddies[id].Direction, GetFrameTime()));

    if (Baddies[id].Postion.x <= 0)
    {
        // they got through
        Baddies[id].Active = false;
        Score -= 10;
        RandomBaddie();
        return;
    }

    Rectangle baddieRect = { Baddies[id].Postion.x,Baddies[id].Postion.y, BaddieSize.x, BaddieSize.y };

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (Bullets[i].Active)
        {
            if (CheckCollisionPointRec(Bullets[i].Postion, baddieRect))
            {
                // I die
                Baddies[id].Lifetime = -1;
                Bullets[i].Active = false;

                Score++;
                RandomBaddie();
                return;
            }
        }
    }

    if (Baddies[id].Lifetime > 2)
    {
        NewBullet(Baddies[id].Postion, (Vector2) { -ShotSpeed, 0 }, ShotLifetime, RED);
        Baddies[id].Lifetime = 0;
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic game");

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        Bullets[i].Active = false;
        Baddies[i].Active = false;
    }

    int count = 5;// GetRandomValue(10, MAX_ENTITIES / 10);
    for (int i = 0; i < count; i++)
    {
        RandomBaddie();
    }
        
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Vector2 playerPos = { 100,100 };
    double lastShootTime = -1;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // player movement and shooting
        float speed = 100 * GetFrameTime();
        if (IsKeyDown(KEY_SPACE))
        {
            if (GetTime() - lastShootTime > 0.25f)
            {
                lastShootTime = GetTime();

                NewBullet((Vector2) { playerPos.x + 20, playerPos.y }, (Vector2) { ShotSpeed, 0 }, ShotLifetime + 0.1f, GREEN);
            }
        }
        else
            speed *= 2;

        if (IsKeyDown(KEY_UP))
            playerPos.y -= speed;
        if (IsKeyDown(KEY_DOWN))
            playerPos.y += speed;
        if (IsKeyDown(KEY_LEFT))
            playerPos.x -= speed;
        if (IsKeyDown(KEY_RIGHT))
            playerPos.x += speed;

        // update any baddies and bullets

        // badies
        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            if (!Baddies[i].Active)
                continue;

            UpdateBaddie(i);
        }

        bool gotHit = false;
        // bullets
        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            if (!Bullets[i].Active)
                continue;
            UpdateBullet(i);

            if (CheckCollisionPointCircle(playerPos, Bullets[i].Postion, 15 + 2))
            {
                // I was shot
                Bullets[i].Active = false;
                Score--;
                gotHit = true;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(playerPos, 15, gotHit ? YELLOW : BLUE);

        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            if (!Bullets[i].Active)
                continue;

            DrawCircleV(Bullets[i].Postion, 2, Bullets[i].Tint);
        }

        for (int i = 0; i < MAX_ENTITIES; i++)
        {
            if (!Baddies[i].Active)
                continue;

            DrawRectangleV(Baddies[i].Postion, BaddieSize , Baddies[i].Lifetime >= 0 ? Baddies[i].Tint : YELLOW);
        }

        DrawText("Arrows to Move, Press Space to Fire", 10, 10, 20, LIGHTGRAY);
        DrawText(TextFormat("Score %d", Score), 30, 30, 20, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
