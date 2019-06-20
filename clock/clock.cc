//
// Created by ponderosa on 6/19/19.
//

#include <string>
#include "clock.h"
#include "twilight.h"

Clock::Clock(Dispatch *dispatch, unsigned int channel, unsigned int master_channel) {
    if(channel <= master_channel) {
        printf("Error - Clock inversion detected");
    }

    multiplier = new Observer(dispatch->GetSubject("clock_speed_ch" + std::to_string(channel)), 0, 2);
    master = new Observer(dispatch->GetSubject("clock_master_ch" + std::to_string(channel)), 0,  NUMBER_OF_CLOCKS);

    this->channel = channel;

    ticks = 0;
    ticks_diff = 0;
}

void Clock::AddTicks(uint32_t tick_add) {
    if((channel > 0) && (channel <= master->GetScaled())) {
        printf("Error - Clock inversion detected\n");
    }

    ticks_diff = (uint32_t)((double)tick_add * multiplier->GetScaled());
    ticks += ticks_diff;

}

uint32_t Clock::GetTicks() {
    return ticks;
}

uint32_t Clock::GetTickDiff() {
    return ticks_diff;
}

int Clock::GetChannel() {
    return channel;
}

int Clock::GetMasterChannel() {
    return (int)master->GetValue();
}