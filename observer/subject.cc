//
// Created by ponderosa on 6/5/19.
//

#include "subject.h"
#include "observer.h"

// Setters
void Subject::SetVal(double val) {
    value = val;
    Notify();
}

void Subject::SetValScaled(double val) {
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

void Subject::SetMidi(int midi) {
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


// Getters
double Subject::GetVal() {
    return value;
}

int Subject::GetMidi() {
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

double Subject::GetMin() {
    return min;
}

double Subject::GetMax() {
    return max;
}

// Observer Pattern
void Subject::Attach(Observer *obs) {
    views.push_back(obs);
}

void Subject::Notify() {
    for (auto i : views)
        i->Update();
}