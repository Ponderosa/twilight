//
// Created by ponderosa on 6/5/19.
//

#include "observer.h"
#include "subject.h"

//Observer::Observer() {}

Observer::Observer(Subject *mod, double min, double max) {
    model = mod;
    model->Attach(this);
    value = model->GetVal();
    this->min = min;
    this->max = max;
}

double Observer::GetScaled() {
    // Scale value from [min, max] of Subject to [min, max] of Animator
    //((b - a) * (x - min)) / (max - min) + a
    // a = Animator.min, b = Animator.max, min = Subject.min, max = Subject.max, x = Animator.Value

    double sub_min = model->GetMin();
    double sub_max = model->GetMax();
    double ret_val = ((max - min) * (value - sub_min)) / (sub_max - sub_min) + min;

    if (ret_val > max) {
        ret_val = max;
    }
    if (ret_val < min) {
        ret_val = min;
    }

    return ret_val;

}

Subject* Observer::Observer::GetSubject() {
    return model;
}

double Observer::Observer::GetValue() {
    return value;
}

double Observer::GetMin() {
    return min;
}

double Observer::GetMax() {
    return max;
}

void Observer::Update() {
    value = model->GetVal();
}