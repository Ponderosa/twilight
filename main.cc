#include <blend2d.h>
#include <SDL.h>
#include <math.h>
#include "sdl_application.h"
#include "fps.h"
#include "tunnel.h"

#define ARRAY_SIZE(X) uint32_t(sizeof(X) / sizeof(X[0]))
#define WIDTH 1024
#define HEIGHT 1024

int main(int argc, char *argv[]) {
    SDLApplication sdl;
    Tunnel tunnel(WIDTH,HEIGHT);
    FPS fps(&sdl.fps);

    if (!sdl.CreateWindow(WIDTH, HEIGHT))
        return 1;

    sdl.AddBeam(&tunnel);
    sdl.AddBeam(&fps);

    return sdl.Run();
}
