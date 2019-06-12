//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_MIDI_MANAGER_H
#define TWILIGHT_MIDI_MANAGER_H

#include <map>
#include "midi_device.h"
#include "observer/dispatch.h"

struct MidiDispatch {
    Dispatch* dispatch;
    MidiDevice* midi_device;
};

class MidiManager {
public:
    MidiManager(Dispatch *dispatch);
private:
    //bool CLISetup();
    bool AutoSetup(Dispatch * dispatch);
    std::map<std::string, MidiDevice*> devices;
};


#endif //TWILIGHT_MIDI_MANAGER_H
