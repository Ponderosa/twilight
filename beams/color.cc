//
// Created by ponderosa on 6/10/19.
//

#include "color.h"
#include <cmath>
#include <iostream>
#include "observer/animator.h"

Color::Color(int channel, Dispatch* dispatch) {
    repeat = new Animator(dispatch->GetParameter("repeat_ch" + std::to_string(channel)), 1, 8);
    saturation = new Animator(dispatch->GetParameter("saturation_ch" + std::to_string(channel)), 0, 127);
    hue = new Animator(dispatch->GetParameter("hue_ch" + std::to_string(channel)), 0, 127);
    window = new Animator(dispatch->GetParameter("window_ch" + std::to_string(channel)), 0, 127);
    alpha = new Animator(dispatch->GetParameter("intensity_ch" + std::to_string(channel)), 0, 127);

    count = 1;
    current_color = 0;
}

void Color::SetCount(int cnt) {
    count = cnt;
    current_color = 0;
}

BLRgba32 Color::GetNextColor() {
    /* Handle Repeat - Restart current_color */
    int current_color_repeat = current_color;
    int limit_range = count / (int)repeat->GetScaled();
    current_color_repeat = current_color_repeat % limit_range;

    /* Need an incremental angle */
    double range = window->GetScaled() * (360.0/128.0);
    double increment = range/count;
    double angle = hue->GetScaled() * (360.0/128.0) + (increment * current_color_repeat * (int)repeat->GetScaled());
    current_color++;
    if(angle >= 360.0) {
        angle = fmod(angle, 360.0);
    }
    double sat = saturation->GetScaled() / 127.0;
    double a = alpha->GetScaled() / 127.0;
    //std::cout << "alpha = " << a << std::endl;
    return HSVToRGB(angle, sat, a);
}

/* Given hue [0,360], sat [0,1], alpha [0,1]
 * Return BLRgba */
BLRgba32 Color::HSVToRGB(double hue, double sat, double alpha) {
    if (0 > hue || 360 < hue) {
        throw;
    }
    if (0 > sat || 1 < sat) {
        throw;
    }
    if (0 > alpha || 1 < alpha) {
        throw;
    }


    double V = 1.0;

    double C = V * sat;
    double X = C * (1.0 - std::abs((std::fmod((hue / 60.0), 2.0) - 1.0)));
    double m = V - C;

    double R, G, B;

    if(hue >= 0 && hue < 60) {
        R = C;
        G = X;
        B = 0;
    } else if (hue >= 60 && hue < 120) {
        R = X;
        G = C;
        B = 0;
    } else if (hue >= 120 && hue < 180) {
        R = 0;
        G = C;
        B = X;
    } else if (hue >= 180 && hue < 240) {
        R = 0;
        G = X;
        B = C;
    } else if (hue >= 240 && hue < 300) {
        R = X;
        G = 0;
        B = C;
    } else if (hue >= 300 && hue <360) {
        R = C;
        G = 0;
        B = X;
    }

    R = (R + m) * 255;
    G = (G + m) * 255;
    B = (B + m) * 255;

    BLRgba32 out;
    out.r = (uint8_t)R;
    out.g = (uint8_t)G;
    out.b = (uint8_t)B;
    out.a = (uint8_t)(alpha * 255.0);

    return out;
}