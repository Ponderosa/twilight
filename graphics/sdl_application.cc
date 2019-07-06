//
// Created by ponderosa on 6/3/19.
//


#include <math.h>

#include "twilight.h"
#include "sdl_application.h"


bool SDLApplication::CreateWindow(int w, int h) noexcept {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        printf("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!window)
        return false;

    if(SET_FULLSCREEN) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        printf("FAILED to create SDL_Renderer: %s\n", SDL_GetError());
        DestroyWindow();
        return false;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    if (!CreateSurface(w, h)) {
        DestroyWindow();
        return false;
    }

    cnt_beams = 0;

    return true;
}

void SDLApplication::DestroyWindow() noexcept{
    DestroySurface();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (!window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void SDLApplication::OnEvent(SDL_Event &event) noexcept{
    if (event.type == SDL_QUIT) {
        quitting = true;
    }

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            quitting = true;
        }
    }
}


bool SDLApplication::CreateSurface(int w, int h) noexcept{
    DestroySurface();

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!texture)
        return false;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);

    if (blSurface.create(w, h, BL_FORMAT_PRGB32) != BL_SUCCESS)
        return false;

    return true;
}

void SDLApplication::DestroySurface() noexcept{
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    blSurface.reset();
}

int SDLApplication::Run() noexcept{
    SDL_Event event;

    for (;;) {
        while (!quitting && SDL_PollEvent(&event))
            OnEvent(event);

        if (quitting)
            break;

        OnFrame();
        OnRender();
        Blit();
        UpdateFrameCounter();
    }

    return exitCode;
}

void SDLApplication::OnFrame() noexcept{
    for(int i = 0; i < cnt_beams; ++i) {
        beams[i]->OnFrame(SDL_GetTicks());
    }
    clocks->UpdateTick(SDL_GetTicks());
}

void SDLApplication::OnRender() noexcept{

    BLContext ctx(blSurface);

    ctx.setCompOp(BL_COMP_OP_SRC_COPY);
    ctx.fillAll();

    for(int i = 0; i < cnt_beams; ++ i) {
        BLContext ctx(blSurface);
        beams[i]->OnRender(&ctx);
    }

}

void SDLApplication::Blit() noexcept{
    BLImageData data;
    blSurface.getData(&data);

    SDL_UpdateTexture(texture, nullptr, data.pixelData, int(data.stride));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void SDLApplication::UpdateFrameCounter() noexcept{
    uint32_t ticks = SDL_GetTicks();
    if (++frameCounter >= 100) {
        fps = (1000.0 / double(ticks - frameTicks)) * double(frameCounter);
        frameCounter = 0;
        frameTicks = ticks;

        printf("FPS: %.2f\n", fps);
    }
}

double SDLApplication::FPS() noexcept{
    return fps;
}

void SDLApplication::AddBeam(Beam *beam) noexcept{
    beams[cnt_beams] = beam;
    cnt_beams++;
}



