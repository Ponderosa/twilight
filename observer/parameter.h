//
// Created by ponderosa on 6/10/19.
//

#ifndef TWILIGHT_PARAMETER_H
#define TWILIGHT_PARAMETER_H

#include "observer.h"

class Parameter: public Observer {
public:
    Parameter();
    int GetMidi();
    double GetScalar();
    double GetScalarAnimated();
private:
    double max;
    double min;
    //Animator
};


#endif //TWILIGHT_PARAMETER_H
