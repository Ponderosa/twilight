//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_MIDI_H
#define TWILIGHT_MIDI_H


#include <RtMidi.h>

class MidiDevice {
public:
    MidiDevice();
    void SetMidiOut(RtMidiOut* midi_out);
    void SetMidiIn(RtMidiIn* midi_in);
    bool SetupComplete();
    void SetCallBack(void (*mycallback)( double deltatime, std::vector< unsigned char > *message, void */*userData*/ ));

//protected:
    RtMidiOut* midi_out;
    RtMidiIn* midi_in;
};


#endif //TWILIGHT_MIDI_H
