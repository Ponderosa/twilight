//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_APC_40_H
#define TWILIGHT_APC_40_H

#include <vector>
#include "midi_device.h"
#include "observer/dispatch.h"


class MidiAPC40: public MidiDevice {
public:
    MidiAPC40();
    void UpdateMode(Dispatch* dispatch, unsigned char mode);
    void UpdateLed(unsigned char controlID, unsigned char channel, unsigned char state);
    void UpdateRingLed(std::vector<unsigned char> *buffer);
    void UpdateRingLed(Dispatch* dispatch);
    void UpdateClipLaunch(unsigned char row, unsigned char column, unsigned char state);
    void SetChannel(Dispatch *dispatch, int channel);
    static void HandleMidi(double deltatime, std::vector< unsigned char > *message, void *userData );
    void HandleMidiChannel(std::vector< unsigned char > *message, Dispatch *dispatch, int channel);
private:
    int channel;
};

typedef void (MidiAPC40::*HandleMidi)(double, std::vector<unsigned char>*, void*) const;

enum ControlID {
    NOTE_ON = 0x90,
    NOTE_OFF = 0x80,
    CONTINUOS = 0xB0,
};

enum LEDGeneric {
    G_OFF = 0,
    G_ON = 1,
};

enum LEDBlink {
    B_OFF = 0,
    B_ON = 1,
    B_BLINK = 2,
};

enum LEDClipLaunch {
    CL_OFF = 0,
    CL_GREEN = 1,
    CL_GREEN_BLINK = 2,
    CL_RED = 3,
    CL_RED_BLINK = 4,
    CL_YELLOW = 5,
    CL_YELLOW_BLINK = 6,
};

#endif //TWILIGHT_APC_40_H
