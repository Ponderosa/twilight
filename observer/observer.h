//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_OBSERVER_H
#define TWILIGHT_OBSERVER_H

class Subject;

class Observer {
public:
    Observer(Subject *mod, double value);
    void Update();
    double GetValue();
protected:
    Subject *GetSubject();
private:
    Subject *model;
    double value;
};


#endif //TWILIGHT_OBSERVER_H
