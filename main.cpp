
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "src/LRaycaster.hpp"
#include "src/LRay.hpp"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raycaster LLLLL");
    
    LRayCaster caster = LRayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, 1.0472, 0.1f};
    LRay obstacle1 = LRay{Vector2{0, 0},Vector2{(float)screenWidth, (float)screenHeight}, true, RED};

    SetTargetFPS(60);              

    
    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(RAYWHITE);
        float deltaTime = GetFrameTime();

        caster.pointTo(GetMousePosition());
        caster.follow(GetMousePosition(), 50.f, deltaTime);
        caster.update(obstacle1);
        caster.render();
        obstacle1.render();
        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}