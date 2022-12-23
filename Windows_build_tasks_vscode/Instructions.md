In order to run this code on [Windows] using `Visual Studio Code`, you need to `add this folder to the workspace` and install `raylib 4.2 Windows Installer (with MinGW compiler)` from [https://www.raylib.com/].
In the files where IntelliSense gives you this error:
    `M_PI_2 identifier is undefined`
add this two headers in this order:
    #define _USE_MATH_DEFINES
    #include <math.h>
[Note]: even if you get this error, the code should compile the same.