//
// Created by ponderosa on 6/4/19.
//

#include "midi_device.h"

MidiDevice::MidiDevice() {
    midi_in = nullptr;
    midi_out = nullptr;
}

void MidiDevice::SetMidiIn(RtMidiIn *midi_in){
    this->midi_in = midi_in;
}

void MidiDevice::SetMidiOut(RtMidiOut *midi_out){
    this->midi_out = midi_out;
}

bool MidiDevice::SetupComplete() {
    return midi_in && midi_out;
}

void MidiDevice::SetCallBack(void (*mycallback)( double deltatime, std::vector< unsigned char > *message, void */*userData*/ )) {
    midi_in->setCallback(mycallback);
}