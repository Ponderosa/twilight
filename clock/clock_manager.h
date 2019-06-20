//
// Created by ponderosa on 6/19/19.
//

#ifndef TWILIGHT_CLOCK_MANAGER_H
#define TWILIGHT_CLOCK_MANAGER_H

#include <stdint-gcc.h>
#include <vector>
#include "clock.h"
#include "observer/dispatch.h"

class ClockManager {
public:
    ClockManager(Dispatch *dispatch, int num_clocks);
    void UpdateTick(uint32_t tick);
    uint32_t GetTicks(int channel);
    uint32_t GetTickDiff(int channel);
private:
    uint32_t previous_tick;
    std::vector<Clock> clocks;
};


#endif //TWILIGHT_CLOCK_MANAGER_H
