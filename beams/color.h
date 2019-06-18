//
// Created by ponderosa on 6/10/19.
//

#ifndef TWILIGHT_COLOR_H
#define TWILIGHT_COLOR_H

#include "observer/observer.h"
#include "observer/dispatch.h"
#include "blend2d.h"

class Color {
public:
    Color(int channel, Dispatch *dispatch);
    void SetCount(int cnt);
    BLRgba32 GetNextColor();
    BLRgba32 HSVToRGB(double hue, double sat, double alpha);
private:
    Observer *window;
    Observer *hue;
    Observer *saturation;
    Observer *repeat;
    Observer *alpha;
    int current_color;
    int count;
};


#endif //TWILIGHT_COLOR_H
