
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
    
    
    srand(0);

    InitWindow(width, screenHeight, "Raycaster LLLLL");
    
    std::shared_ptr<L::RayCaster> caster = std::make_shared<L::RayCaster>(L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, M_PI_2, 500, 1000.f, BLACK});

    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, screenWidth, screenHeight});
    
    Rectangle boundaries2dRect = Rectangle{0.f,0.f,(float)screenWidth, (float)screenHeight};

    std::vector<std::shared_ptr<L::Ray>> boundaries = L::generateRaysFromRect(boundaries2dRect, true, RED);
    std::vector<std::shared_ptr<L::Ray>> block = L::generateRaysFromRect(Rectangle{100.0, 100.0, 100.0, 100.0}, true, BLUE);

    
    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(Rectangle{screenWidth, 0, screenWidth, screenHeight}, BLACK);
        float deltaTime = GetFrameTime();
        caster -> pointTo(GetMousePosition());
        caster -> follow(GetMousePosition(), 50.f, deltaTime);

        
        caster -> resetCollisions();
        caster -> update(boundaries);
        caster -> update(block);


        std::cout << caster-> rays[0]->angle << std::endl;

        


        for(auto& b : boundaries){

            b -> render();

        }

        for(auto& b : block){

            b -> render();

        }
        renderer.render();
        caster -> render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
