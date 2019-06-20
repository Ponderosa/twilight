//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_SDL_APPLICATION_H
#define TWILIGHT_SDL_APPLICATION_H

#include <blend2d.h>
#include <SDL.h>
#include "../beams/beam.h"
#include "clock/clock_manager.h"

class SDLApplication {
public:
    SDLApplication(ClockManager* clocks)
            : window(nullptr),
              renderer(nullptr),
              texture(nullptr),
              blSurface(),
              quitting(false),
              exitCode(0),
              frameCounter(0),
              frameTicks(0),
              clocks(clocks) {}
    ~SDLApplication() { DestroyWindow(); }

    bool CreateWindow(int w, int h);
    void DestroyWindow();
    void OnEvent(SDL_Event &event);
    bool CreateSurface(int w, int h);
    void DestroySurface();
    int Run();
    void OnFrame();
    void OnRender();
    void Blit();
    void UpdateFrameCounter();
    double FPS();
    void AddBeam(Beam*);
    double fps;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    BLImage blSurface;

    bool quitting;
    int exitCode;
    int frameCounter;
    int frameTicks;
    //double fps;

    Beam *beams[9];
    int cnt_beams;

    ClockManager *clocks;
};

#endif //TWILIGHT_SDL_APPLICATION_H
