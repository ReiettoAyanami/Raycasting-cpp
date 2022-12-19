
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <memory>
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
    
    std::shared_ptr<L::RayCaster> caster = std::make_shared<L::RayCaster>(L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, 1.0472, 0.005f, 500.f, BLACK});

    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, screenWidth, screenHeight});
    
    std::shared_ptr<L::Ray> obstacle = std::make_shared<L::Ray>(L::Ray{Vector2{100.f,100.f}, Vector2{300.f,300.f}, true, RED});
    std::shared_ptr<L::Ray> obstacle2 = std::make_shared<L::Ray>(L::Ray(Vector2{200.f,100.f}, Vector2{400.f,300.f}, true, RED));

    
    SetTargetFPS(60);              

    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(WHITE);
        float deltaTime = GetFrameTime();

        
        caster -> pointTo(GetMousePosition());
        caster -> follow(GetMousePosition(), 50.f, deltaTime);

        caster -> resetCollisions();

        caster -> update(obstacle);
        caster -> update(obstacle2);



        obstacle2-> render();
        obstacle -> render();
        renderer.render();
        caster -> render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
