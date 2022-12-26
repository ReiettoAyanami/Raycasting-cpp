# Raycasting-cpp
Raycasting visualizer made in C++ and Raylib. Just an adaptation of the raycaster i did a few months ago, i will do a serious re-work or maybe just a total re-do of the original raycaster in Rust.

[Rust version](https://github.com/ReiettoAyanami/Raycasting-rs)
# Build:
## Linux and MacOS
You'll need [raylib](https://github.com/raysan5/raylib) to run this.
I use the g++ compiler on ubuntu. This is the command i run to get the `.out` file:

```g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11``` 

after running the command above just type: 

```./a.out```

## Windows
Use task file in the [`Windows_build_tasks_vscode`](https://github.com/ReiettoAyanami/Raycasting-cpp/tree/main/Windows_build_tasks_vscode) folder in the repository, the task files are intended to use with MinGW compiler, there are also [more detailed instructions](https://github.com/ReiettoAyanami/Raycasting-cpp/blob/main/Windows_build_tasks_vscode/Instructions.md) in the folder.

# Difference from the Rust raycasting project.

- Now rays can be rendered with different colors.
- No fisheye effect.
- Added a Wall class.

## Problems with this version
This version suffers from a very poor performance issues in the current version(26/12/2022).


# Showcase video.
[![Mh something went wrong ig](https://github.com/ReiettoAyanami/Raycasting-cpp/blob/main/videoThumb.png?raw=true)](https://youtu.be/e5O7VMGqcTY)

# Special thanks
[@Massimo Sandretti](https://github.com/MassimoSandre) for helping to fix some memory related bugs, and helping to fix the fisheye effect.

[@Alessandro Rollone](https://www.instagram.com/_alerollo_) for giving moral support throughout the making of the project (He was looking at TikToks and playing online chess).

[@Rondoni Edoardo]() for providing windows build instructions, and the tasks files.

My psichiatrist for the idea and for telling me everything's alright.
