//
// Created by ponderosa on 6/5/19.
//

#include "subject.h"
#include "observer.h"

void Subject::attach(Observer *obs) {
    views.push_back(obs);
}

void Subject::setVal(int val) {
    value = val;
    notify();
}

int Subject::getVal() {
    return value;
}

void Subject::notify() {
    for (int i = 0; i < views.size(); i++)
        views[i]->update();
}