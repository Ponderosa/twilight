//
// Created by ponderosa on 6/19/19.
//

#ifndef TWILIGHT_CLOCK_MANAGER_H
#define TWILIGHT_CLOCK_MANAGER_H

#include <stdint-gcc.h>

class ClockManager {
public:
    ClockManager(int num_clocks);
    void UpdateTick(uint32_t tick);
    uint32_t GetTicks(int channel);
private:
    uint32_t previous_tick;
};


#endif //TWILIGHT_CLOCK_MANAGER_H
