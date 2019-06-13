//
// Created by ponderosa on 6/5/19.
//

#include "observer.h"
#include "subject.h"

//Observer::Observer() {}

Observer::Observer(Subject *mod) {
    model = mod;
    model->Attach(this);
    value = model->GetVal();
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