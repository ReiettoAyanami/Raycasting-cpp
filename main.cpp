
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "src/LRaycaster.hpp"
#include "src/LRay.hpp"
#include "src/LRenderer.hpp"


//void f();

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    const int width = screenWidth * 2;
    const int height = screenHeight * 2;
    
    // Fixed bug in LRay: Wrong collisions
    //f();
    
    srand(0);

    InitWindow(width, screenHeight, "Raycaster LLLLL");
    
    L::RayCaster caster = L::RayCaster{Vector2{screenWidth / 2.f,screenHeight / 2.f}, M_PI_2, 1.0472, 0.01f, 500.f, BLACK};

    L::Renderer renderer = L::Renderer(caster, Rectangle{screenWidth, 0, screenWidth, screenHeight});
    
    L::Ray obstacle(Vector2{100.f,100.f}, Vector2{300.f,300.f}, true, RED);
    L::Ray obstacle2(Vector2{200.f,100.f}, Vector2{400.f,300.f}, true, RED);

    // fix shit in L::Renderer

    SetTargetFPS(60);              

    
    while (!WindowShouldClose())   
    {
        
        

        BeginDrawing();
        ClearBackground(WHITE);
        float deltaTime = GetFrameTime();

        //std :: cout << obstacle2.isObstacle << std::endl;
        caster.pointTo(GetMousePosition());
        caster.follow(GetMousePosition(), 50.f, deltaTime);
    
        caster.update(obstacle2);
        caster.update(obstacle);

        obstacle2.render();
        obstacle.render();
        renderer.render();
        caster.render();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// void f(){

//     int a[10];
//     int n;
//     bool c = false;

//     for(int i = 0; i < 10; ++i){
//         do{
//             std::cout << i << " - Inserire numero: " << std::endl;
//             std::cin >> n;
            

            
//             for(int j = 0; j < i; ++j){
//                 if(n == a[j]){
//                     c = true;
//                     break;
//                 }
//                 else c = false;
//             }
//             if(c){
//                 std::cout <<  " il numero " << n << " è già è presente" << std::endl;   
//             }
//         }while(c);
//         a[i] = n;
        

        
        

//     }


//}
