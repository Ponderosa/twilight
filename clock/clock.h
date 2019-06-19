//
// Created by ponderosa on 6/19/19.
//

#ifndef TWILIGHT_CLOCK_H
#define TWILIGHT_CLOCK_H


#include <stdint-gcc.h>
#include <observer/observer.h>
#include <observer/dispatch.h>

class Clock {
public:
    Clock(Dispatch *dispatch, unsigned int channel, unsigned int master);
    void AddTicks(uint32_t ticks);
    uint32_t GetTicks();
    int GetChannel();
    int GetMasterChannel();
private:
    Observer *multiplier;
    Observer *master;
    uint32_t ticks;
    unsigned int channel;
};

#endif //TWILIGHT_CLOCK_H
