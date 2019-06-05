//
// Created by ponderosa on 6/5/19.
//

#include "subject.h"
#include "observer.h"

void Subject::Attach(Observer *obs) {
    views.push_back(obs);
}

void Subject::SetVal(double val) {
    value = val;
    Notify();
}

double Subject::GetVal() {
    return value;
}

void Subject::Notify() {
    for (int i = 0; i < views.size(); i++)
        views[i]->Update();
}