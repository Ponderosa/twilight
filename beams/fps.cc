//
// Created by ponderosa on 6/3/19.
//

#include "fps.h"
#include "stdio.h"

#define ARRAY_SIZE(X) uint32_t(sizeof(X) / sizeof(X[0]))

FPS::FPS(double *fps) {
    face.createFromFile("../aerial.ttf");
    font.createFromFace(face, 20.f);
    this->fps = fps;
}

void FPS::OnFrame(uint32_t tick) {
}

void FPS::OnRender(BLContext *ctx) {
    // FPS
    char buf[128];
    snprintf(buf, ARRAY_SIZE(buf), "FPS: %.2f", *fps);

    ctx->setFillStyle(BLRgba32(0xFFFF0000u));
    ctx->fillUtf8Text(BLPoint(5, 20), font, buf);
}

//void FPS::SetFPS(double fps) {
//    this->fps = fps;
//}

