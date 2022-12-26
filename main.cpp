
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <memory>
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

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, screenHeight, "Raycaster C++");
   
    
    std::shared_ptr<L::RayCaster> caster = std::make_shared<L::RayCaster>(L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, PI / 2,PI / 2, 800, 1000.f, WHITE});
    //std::shared_ptr<L::Wall> wall = std::make_shared<L::Wall>(L::Wall(Vector2{300.f, 300.f},100.f, 10.f,PI, PURPLE));
    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, screenWidth, screenHeight});
    Rectangle boundaries2dRect = Rectangle{0.f,0.f,(float)screenWidth, (float)screenHeight};

    std::vector<std::shared_ptr<L::Ray>> rRays;

    for(int i = 0; i < 10; ++i){

        L::Ray temp(Vector2{(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)}, (float)GetRandomValue(50,200),(float)GetRandomValue(0,100) / 100.f * 2 * PI, true, PURPLE);

        rRays.push_back(std::make_shared<L::Ray>(temp));

    } 


    std::vector<std::shared_ptr<L::Ray>> boundaries = L::generateRaysFromRect(boundaries2dRect, true, RED);
    
    //SetTargetFPS(60);
    
    
    while (!WindowShouldClose())   
    {   

        BeginDrawing();
        ClearBackground(BLACK);
        
        float deltaTime = GetFrameTime();
        caster -> resetCollisions();
        caster -> pointTo(GetMousePosition());
        caster -> follow(GetMousePosition(),50.f, deltaTime);

        caster -> constrainTo(boundaries2dRect);
        caster -> update(boundaries);
        caster -> update(rRays);

        
        for(auto& r : rRays){

            r -> render();

        }

        for(auto& b : boundaries){

            b -> render();

        }
          
        DrawRectangleRec(Rectangle{screenWidth, 0, screenWidth, screenHeight}, BLACK);


        auto s = std::to_string(GetFPS()).c_str();
        DrawText(s, screenWidth / 2, 0, 20, RAYWHITE);
        renderer.render();
        caster -> renderFOV();

        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
