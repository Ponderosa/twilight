//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_FPS_H
#define TWILIGHT_FPS_H

#include "beam.h"
#include "blend2d.h"

class FPS: public Beam {
private:
    BLFontFace face;
    BLFont font;
    double *fps;
public:
    FPS(double*);
    void OnFrame(uint32_t tick) override;
    void OnRender(BLContext *ctx) override;
    //void SetFPS(double*);
};


#endif //TWILIGHT_FPS_H
