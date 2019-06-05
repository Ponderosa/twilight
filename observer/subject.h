//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_SUBJECT_H
#define TWILIGHT_SUBJECT_H

#include <vector>

class Observer;

class Subject {
public:
    void attach(Observer *obs);
    void setVal(int val);
    int getVal();
    void notify();
protected:
    std::vector<Observer*> views;
    int value;
};


#endif //TWILIGHT_SUBJECT_H
