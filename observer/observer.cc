//
// Created by ponderosa on 6/5/19.
//

#include "observer.h"
#include "subject.h"

Observer::Observer(Subject *mod, int div) {
    model = mod;
    denom = div;
    model->attach(this);
}

Subject* Observer::Observer::getSubject() {
    return model;
}

int Observer::Observer::getDivisor() {
    return denom;
}
