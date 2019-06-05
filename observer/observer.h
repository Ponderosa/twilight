//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_OBSERVER_H
#define TWILIGHT_OBSERVER_H

class Subject;

class Observer {
public:
    Observer(Subject *mod, int div);
    virtual void Update() = 0;
protected:
    Subject *GetSubject();
    int GetDivisor();
private:
    Subject *model;
    int denom;
};


#endif //TWILIGHT_OBSERVER_H
