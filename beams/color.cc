//
// Created by ponderosa on 6/10/19.
//

#include "color.h"
#include <cmath>
#include <iostream>

Color::Color(int channel, Dispatch* dispatch) {
    repeat = new Observer(dispatch->GetParameter("repeat_ch" + std::to_string(channel)));
    saturation = new Observer(dispatch->GetParameter("saturation_ch" + std::to_string(channel)));
    hue = new Observer(dispatch->GetParameter("hue_ch" + std::to_string(channel)));
    window = new Observer(dispatch->GetParameter("window_ch" + std::to_string(channel)));
    alpha = new Observer(dispatch->GetParameter("intensity_ch" + std::to_string(channel)));

    count = 1;
    current_color = 0;
}

void Color::SetCount(int cnt) {
    count = cnt;
    current_color = 0;
}

BLRgba32 Color::GetNextColor() {
    /* Need an incremental angle */
    double range = window->GetValue() * (360.0/128.0);
    double increment = range/count;
    double angle = hue->GetValue() * (360.0/128.0) + (increment * current_color);
    current_color++;
    if(angle >= 360.0) {
        angle -= 360.0;
    }
    double sat = saturation->GetValue() / 127.0;
    double a = alpha->GetValue() / 127.0;
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