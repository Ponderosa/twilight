//
// Created by ponderosa on 6/19/19.
//

#include "clock_manager.h"

ClockManager::ClockManager(Dispatch *dispatch, int num_clocks) {
    for (int i = 0; i < num_clocks; ++i) {
        clocks.push_back(Clock(dispatch, i, 0));
    }
}

void ClockManager::UpdateTick(uint32_t tick) {
    uint32_t tick_diff = tick - previous_tick;
    previous_tick = tick;

    for (auto &i : clocks) {
        i.AddTicks(tick_diff);
    }
}

uint32_t ClockManager::GetTicks(int channel) {
    return clocks[channel].GetTicks();
}

uint32_t ClockManager::GetTickDiff(int channel) {
    return clocks[channel].GetTickDiff();
}