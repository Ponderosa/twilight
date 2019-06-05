//
// Created by ponderosa on 6/4/19.
//

#include "midi_apc_40.h"

MidiAPC40::MidiAPC40() {
}


void MidiAPC40::UpdateMode(unsigned char mode) {

    std::vector<unsigned char> message {0xF0,
                                        0x47,
                                        0x00,
                                        0x73,
                                        0x60,
                                        0x00,
                                        0x04,
                                        (0x40), /* Add mode here, address = 7 */
                                        0x08,
                                        0x04,
                                        0x01,
                                        0xF7};

    message[7] += mode;

    midi_out->sendMessage(&message);
}

void MidiAPC40::UpdateLed(unsigned char controlID, unsigned char channel, unsigned char state) {

}

void MidiAPC40::UpdateClipLaunch(unsigned char row, unsigned char column, unsigned char state) {

}