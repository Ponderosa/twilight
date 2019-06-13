//
// Created by ponderosa on 6/10/19.
//

#ifndef TWILIGHT_PARAMETER_H
#define TWILIGHT_PARAMETER_H

#include "observer.h"
#include "subject.h"

class Parameter: public Subject {
public:
    Parameter(double value, double min = 0, double max = 1) : Subject(value),  min(min), max(max) {}
    void SetValScaled(double val);
    void SetMidi(int val);
    double GetMin();
    double GetMax();
    int GetMidi();
private:
    double max;
    double min;
};


#endif //TWILIGHT_PARAMETER_H
