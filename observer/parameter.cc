//
// Created by ponderosa on 6/10/19.
//

#include "parameter.h"

void Parameter::SetValScaled(double val) {
    if(max > min) {
        if (val > max) {
            val = max;
        }
        if (val < min) {
            val = min;
        }
    }

    Subject::SetVal(val);
}

void Parameter::SetMidi(int midi) {
    // Scale value from [0, 127] to [min, max]
    //((b - a) * (x - min)) / (max - min) + a
    // a = min, b = max, min = 0, max = 127, x = midi

    double scaled = ((max - min) * (double)(midi)) / 127.0 + min;
    if (scaled > max) {
        scaled = max;
    }
    if (scaled < min) {
        scaled = min;
    }

    Subject::SetVal(scaled);
}

int Parameter::GetMidi() {
    // Scale value from [min, max] to [0, 127]
    //((b - a) * (x - min)) / (max - min) + a
    // a = 0, b = 127, min = this.min, max = this.max, x = value

    int ret_val = ((127.0) * (value - min)) / (max - min);
    if (ret_val > 127) {
        return 127;
    }
    if (ret_val < 0) {
        return 0;
    }
    return ret_val;
}

double Parameter::GetMin() {
    return min;
}

double Parameter::GetMax() {
    return max;
}