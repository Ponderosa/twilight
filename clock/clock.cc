//
// Created by ponderosa on 6/19/19.
//

#include <string>
#include "clock.h"

Clock::Clock(Dispatch *dispatch, unsigned int channel, unsigned int master_channel) {
    // Ensure master is less then current channel
    if (channel == 0) {
        master_channel = 0;
    } else {
        if((master_channel > 0) && (master_channel >= channel)) {
            master_channel = channel - 1;
        }
    }

    multiplier = new Observer(dispatch->GetSubject("clock_speed_" + std::to_string(channel)), 0, 2);
    master = new Observer(dispatch->GetSubject("clock_master_" + std::to_string(channel)), 0, master_channel);

    this->channel = channel;
}

void Clock::AddTicks(uint32_t ticks) {
    ticks += (uint32_t)((double)ticks * multiplier->GetScaled());
}

uint32_t Clock::GetTicks() {
    return ticks;
}

int Clock::GetChannel() {
    return channel;
}

int Clock::GetMasterChannel() {
    return (int)master->GetValue();
}