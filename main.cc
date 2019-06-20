#include <blend2d.h>
#include <SDL.h>
#include <math.h>
#include <thread>
#include <mutex>
#include "twilight.h"
#include "graphics/sdl_application.h"
#include "beams/fps.h"
#include "beams/tunnel.h"
#include "midi/midi_manager.h"
#include "observer/dispatch.h"
#include "gui/gui.h"
#include "clock/clock_manager.h"


int main(int argc, char *argv[]) {

    // Create Dispatch - Do before beam creation!
    Dispatch dispatch;

    // Create Clock Manager
    ClockManager clocks(&dispatch, NUMBER_OF_CLOCKS);

    // Midi Setup
    MidiManager midi(&dispatch);

    // Graphics Setup
    SDLApplication sdl(&clocks);

    // Beam Setup
    Tunnel tunnel1(WIDTH,HEIGHT,1,&dispatch,&clocks);
    Tunnel tunnel2(WIDTH,HEIGHT,2,&dispatch,&clocks);
    Tunnel tunnel3(WIDTH,HEIGHT,3,&dispatch,&clocks);
    Tunnel tunnel4(WIDTH,HEIGHT,4,&dispatch,&clocks);
    Tunnel tunnel5(WIDTH,HEIGHT,5,&dispatch,&clocks);
    Tunnel tunnel6(WIDTH,HEIGHT,6,&dispatch,&clocks);
    Tunnel tunnel7(WIDTH,HEIGHT,7,&dispatch,&clocks);
    Tunnel tunnel8(WIDTH,HEIGHT,8,&dispatch,&clocks);
    FPS fps(&sdl.fps);

    // Make window
    if (!sdl.CreateWindow(WIDTH, HEIGHT))
        return 1;

    sdl.AddBeam(&tunnel1);
    sdl.AddBeam(&tunnel2);
    sdl.AddBeam(&tunnel3);
    sdl.AddBeam(&tunnel4);
    sdl.AddBeam(&tunnel5);
    sdl.AddBeam(&tunnel6);
    sdl.AddBeam(&tunnel7);
    sdl.AddBeam(&tunnel8);
    sdl.AddBeam(&fps);

    // Spin up GUI thread
    std::thread gui = std::thread(Gui(&dispatch));

    int ret_val = sdl.Run();
    gui.join();
    return ret_val;
}
