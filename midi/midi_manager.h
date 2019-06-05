//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_MIDI_MANAGER_H
#define TWILIGHT_MIDI_MANAGER_H

#include <map>
#include "midi_device.h"

class MidiManager {
public:
    MidiManager();
private:
    //bool CLISetup();
    bool AutoSetup();
    std::map<std::string, MidiDevice*> devices;
};


#endif //TWILIGHT_MIDI_MANAGER_H
