//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_BEAM_H
#define TWILIGHT_BEAM_H

#include "blend2d.h"

// This class is a placeholder until we add more beams.
class Beam {
public:
    virtual void OnFrame(uint32_t tick) = 0;
    virtual void OnRender(BLContext *ctx) = 0;
};


#endif //TWILIGHT_BEAM_H
