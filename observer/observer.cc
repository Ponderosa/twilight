//
// Created by ponderosa on 6/5/19.
//

#include "observer.h"
#include "subject.h"

Observer::Observer(Subject *mod, double value) {
    model = mod;
    this->value = value;
    model->Attach(this);
}

Subject* Observer::Observer::GetSubject() {
    return model;
}

double Observer::Observer::GetValue() {
    return value;
}

void Observer::Update() {
    value = model->GetVal();
}