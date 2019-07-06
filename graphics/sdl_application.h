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

    bool CreateWindow(int w, int h) noexcept;
    void DestroyWindow() noexcept;
    void OnEvent(SDL_Event &event) noexcept;
    bool CreateSurface(int w, int h) noexcept;
    void DestroySurface() noexcept;
    int Run() noexcept;
    void OnFrame() noexcept;
    void OnRender() noexcept;
    void Blit() noexcept;
    void UpdateFrameCounter() noexcept;
    double FPS() noexcept;
    void AddBeam(Beam*) noexcept;
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

    Beam *beams[9];
    int cnt_beams;

    ClockManager *clocks;
};

#endif //TWILIGHT_SDL_APPLICATION_H
