
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "src/LRaycaster.hpp"
#include "src/LRay.hpp"
#include "src/LRenderer.hpp"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    const int width = screenWidth * 2;
    const int height = screenHeight * 2;
    
    
    srand(0);

    InitWindow(width, height, "Raycaster LLLLL");
    
    L::RayCaster caster = L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, 1.0472, 0.01f, 50.f, BLACK};

    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, screenHeight, screenWidth, screenHeight});
    
    L::Ray obstacle(Vector2{100.f,100.f}, Vector2{300.f,300.f}, true, RED);
    L::Ray obstacle2(Vector2{200.f,100.f}, Vector2{400.f,300.f}, true, RED);

    // fix shit in L::Renderer

    SetTargetFPS(60);              

    
    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(WHITE);
        float deltaTime = GetFrameTime();

        
        caster.pointTo(GetMousePosition());
        caster.follow(GetMousePosition(), 50.f, deltaTime);
        
        caster.update(obstacle);
        caster.update(obstacle2);

        obstacle2.render();
        obstacle.render();
        renderer.render();
        caster.render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}