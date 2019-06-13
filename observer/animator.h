//
// Created by ponderosa on 6/13/19.
//

#ifndef TWILIGHT_ANIMATOR_H
#define TWILIGHT_ANIMATOR_H


#include "observer.h"
#include "parameter.h"

class Animator : public Observer{
public:
    Animator(Parameter *mod, double min = 0, double max = 0) : Observer(mod), min(min), max(max) {}
    double GetScaled();
    double GetMin();
    double GetMax();
private:
    double min;
    double max;
};


#endif //TWILIGHT_ANIMATOR_H
