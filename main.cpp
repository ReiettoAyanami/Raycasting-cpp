
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "src/LRay.hpp"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    LRay r = LRay{Vector2{screenWidth/2.0, screenHeight/2.0 + 100}, 100.f};
    LRay obstacle1 = LRay{Vector2{0, 0},Vector2{(float)screenWidth, (float)screenHeight}, true, RED};

    SetTargetFPS(60);              

    
    while (!WindowShouldClose())   
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto coords = std::get<1>(r.getSegmentIntersection(obstacle1));
        r.pointTo(GetMousePosition());
        


        r.render();
        obstacle1.render();
        DrawCircleV(coords, 5, BLUE);
        


        EndDrawing();
    }

    CloseWindow();

    return 0;
}