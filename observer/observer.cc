//
// Created by ponderosa on 6/5/19.
//

#include "observer.h"
#include "subject.h"

Observer::Observer(Subject *mod, int div) {
    model = mod;
    denom = div;
    model->Attach(this);
}

Subject* Observer::Observer::GetSubject() {
    return model;
}

int Observer::Observer::GetDivisor() {
    return denom;
}
