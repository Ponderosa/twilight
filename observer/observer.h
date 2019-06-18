//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_OBSERVER_H
#define TWILIGHT_OBSERVER_H

class Subject;

class Observer {
public:
    //Observer();
    Observer(Subject *mod);
    Observer(Subject *mod, double min = 0, double max = 0);
    void Update();
    double GetValue();
    double GetScaled();
    double GetMin();
    double GetMax();
protected:
    Subject *GetSubject();
    Subject *model;
    double value;
    double min;
    double max;
};


#endif //TWILIGHT_OBSERVER_H
