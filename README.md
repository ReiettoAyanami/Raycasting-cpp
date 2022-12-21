# Raycasting-cpp
Raycasting visualizer made in C++ and Raylib. Just an adaptation of the raycaster i did a few months ago, i will do a serious re-work or maybe just a total re-do of the original raycaster in Rust.
# Build:
You'll need [raylib](https://github.com/raysan5/raylib) to run this.
I use the g++ compiler on ubuntu. This is the command i run to get the `.out` file:

```g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11``` 

after running the command above just type: 

```./a.out```

I've never ran this on windows nor MacOs.

# Difference from the Rust raycasting project.

- Now rays can be rendered with different colors.
- No fisheye effect.
- Added a Wall class.
