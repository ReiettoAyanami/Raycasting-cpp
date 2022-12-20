
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "src/LWall.hpp"
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

    InitWindow(width, screenHeight, "Raycaster");
    
    std::shared_ptr<L::RayCaster> caster = std::make_shared<L::RayCaster>(L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, M_PI_2, 500, 1000.f, BLACK});
    std::shared_ptr<L::Wall> wall = std::make_shared<L::Wall>(L::Wall(Vector2{300.f, 300.f},100.f, 10.f,PI, PURPLE));
    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, width, screenHeight});
    Rectangle boundaries2dRect = Rectangle{0.f,0.f,(float)screenWidth, (float)screenHeight};

    std::vector<std::shared_ptr<L::Ray>> boundaries = L::generateRaysFromRect(boundaries2dRect, true, RED);
    

    
    while (!WindowShouldClose())   
    {   

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(Rectangle{screenWidth, 0, screenWidth, screenHeight}, BLACK);
        float deltaTime = GetFrameTime();
        caster -> resetCollisions();
        caster -> pointTo(GetMousePosition());
        caster -> follow(GetMousePosition(), 50.f, deltaTime);
        
        caster -> update(boundaries);
        caster -> update(wall);

        for(auto& b : boundaries){

            b -> render();

        }
        wall -> render();    
        renderer.render();
        caster -> render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
