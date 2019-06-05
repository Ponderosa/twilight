//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_OBSERVER_H
#define TWILIGHT_OBSERVER_H

class Subject;

class Observer {
public:
    Observer(Subject *mod, int div);
    virtual void update() = 0;
protected:
    Subject *getSubject();
    int getDivisor();
private:
    Subject *model;
    int denom;
};


#endif //TWILIGHT_OBSERVER_H
