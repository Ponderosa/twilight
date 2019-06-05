//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_SUBJECT_H
#define TWILIGHT_SUBJECT_H

#include <vector>

class Observer;

class Subject {
public:
    void Attach(Observer *obs);
    void SetVal(double val);
    double GetVal();
    void Notify();
protected:
    std::vector<Observer*> views;
    double value;
};


#endif //TWILIGHT_SUBJECT_H
