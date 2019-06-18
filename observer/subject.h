//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_SUBJECT_H
#define TWILIGHT_SUBJECT_H

#include <vector>

class Observer;

class Subject {
public:
    // Constructors
    //Subject(double value) : value(value) {}
    Subject(double value, double min = 0, double max = 1) : value(value), min(min), max(max) {}

    // Set Value
    void SetVal(double val);
    void SetValScaled(double val);
    void SetMidi(int val);

    // Get Value
    double GetVal();
    double GetMin();
    double GetMax();
    int GetMidi();

    // Observer Pattern
    void Attach(Observer *obs);
    void Notify();

protected:
    std::vector<Observer*> views;
    double value;
    double max;
    double min;
};


#endif //TWILIGHT_SUBJECT_H
