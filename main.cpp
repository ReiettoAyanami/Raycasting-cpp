
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
    
    // Fixed bug in LRay: Wrong collisions
    
    
    srand(0);

    InitWindow(width, screenHeight, "Raycaster LLLLL");
    
    std::shared_ptr<L::RayCaster> caster = std::make_shared<L::RayCaster>(L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, 1.0472, 0.01f, 500.f, BLACK});

    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, screenWidth, screenHeight});
    
    L::Ray obstacle(Vector2{100.f,100.f}, Vector2{300.f,300.f}, true, RED);
    L::Ray obstacle2(Vector2{200.f,100.f}, Vector2{400.f,300.f}, true, RED);

    // Disappearing ptr when passing a ptr;

    SetTargetFPS(60);              

    
    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(WHITE);
        float deltaTime = GetFrameTime();

        //std :: cout << obstacle2.isObstacle << std::endl;
        caster -> pointTo(GetMousePosition());
        caster -> follow(GetMousePosition(), 50.f, deltaTime);
    
        caster -> update(obstacle2);
        caster -> update(obstacle);

        obstacle2.render();
        obstacle.render();
        renderer.render();
        caster -> render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
