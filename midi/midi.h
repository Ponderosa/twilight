//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_MIDI_H
#define TWILIGHT_MIDI_H


#include <RtMidi.h>

class Midi {
public:
    Midi();
    void CreateAPC();
    bool ChooseMidiPort(RtMidiOut*);

private:
    RtMidiOut *MidiOut[4];
    RtMidiIn  *MidiIn[4];
};


#endif //TWILIGHT_MIDI_H
