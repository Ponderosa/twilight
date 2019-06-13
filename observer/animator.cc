//
// Created by ponderosa on 6/13/19.
//

#include "animator.h"

double Animator::GetScaled() {
    // Scale value from [min, max] of Subject to [min, max] of Animator
    //((b - a) * (x - min)) / (max - min) + a
    // a = Animator.min, b = Animator.max, min = Subject.min, max = Subject.max, x = Animator.Value

    double sub_min = ((Parameter*)model)->GetMin();
    double sub_max = ((Parameter*)model)->GetMax();
    double ret_val = ((max - min) * (value - sub_min)) / (sub_max - sub_min) + min;

    if (ret_val > max) {
        ret_val = max;
    }
    if (ret_val < min) {
        ret_val = min;
    }

    return ret_val;

}

double Animator::GetMin() {
    return min;
}

double Animator::GetMax() {
    return max;
}