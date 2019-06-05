#include <blend2d.h>
#include <SDL.h>
#include <math.h>
#include "graphics/sdl_application.h"
#include "beams/fps.h"
#include "beams/tunnel.h"
#include "midi/midi_device.h"
#include "observer/dispatch.h"

#define ARRAY_SIZE(X) uint32_t(sizeof(X) / sizeof(X[0]))
#define WIDTH 2560
#define HEIGHT 1440

int main(int argc, char *argv[]) {
    // Midi Setup
    MidiDevice Midi;

    // Create Dispatch
    Dispatch dispatch;

    SDLApplication sdl;
    Tunnel tunnel(WIDTH,HEIGHT);
    FPS fps(&sdl.fps);

    if (!sdl.CreateWindow(WIDTH, HEIGHT))
        return 1;

    sdl.AddBeam(&tunnel);
    sdl.AddBeam(&fps);

    return sdl.Run();
}
