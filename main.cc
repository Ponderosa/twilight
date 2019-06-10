#include <blend2d.h>
#include <SDL.h>
#include <math.h>
#include "twilight.h"
#include "graphics/sdl_application.h"
#include "beams/fps.h"
#include "beams/tunnel.h"
#include "midi/midi_manager.h"
#include "observer/dispatch.h"

//#define ARRAY_SIZE(X) uint32_t(sizeof(X) / sizeof(X[0]))


int main(int argc, char *argv[]) {
    // Create Dispatch - Do before beam creation!
    Dispatch dispatch;

    // Midi Setup
    MidiManager midi(&dispatch);

    // Graphics Setup
    SDLApplication sdl;

    // Beam Setup
    Tunnel tunnel1(WIDTH,HEIGHT,1,&dispatch);
    Tunnel tunnel2(WIDTH,HEIGHT,2,&dispatch);
    Tunnel tunnel3(WIDTH,HEIGHT,3,&dispatch);
    Tunnel tunnel4(WIDTH,HEIGHT,4,&dispatch);
    FPS fps(&sdl.fps);

    // Make window
    if (!sdl.CreateWindow(WIDTH, HEIGHT))
        return 1;

    sdl.AddBeam(&tunnel1);
    sdl.AddBeam(&tunnel2);
    sdl.AddBeam(&tunnel3);
    sdl.AddBeam(&tunnel4);
    sdl.AddBeam(&fps);

    return sdl.Run();
}
