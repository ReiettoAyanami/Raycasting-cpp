## How to include the files.
In order to run this code on Windows using `Visual Studio Code`, you need to `add this folder to the workspace` and install `raylib 4.2 Windows Installer (with MinGW compiler)` from [the raylib website](https://www.raylib.com/).

## Eventual errors you might encounter

In the files where IntelliSense gives you this error:
    `M_PI_2 identifier is undefined`
    
Add this two headers in this order:
```c++
#define _USE_MATH_DEFINES
#include <math.h>
```
**NOTE**: 
    even if you can't get rid of this error, the code will compile just fine.
