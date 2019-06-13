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
    void Update();
    double GetValue();
protected:
    Subject *GetSubject();
    Subject *model;
    double value;
};


#endif //TWILIGHT_OBSERVER_H
