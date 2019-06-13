//
// Created by ponderosa on 6/4/19.
//

#include <string>
#include "midi_apc_40.h"
#include "observer/dispatch.h"
#include "midi_manager.h"

MidiAPC40::MidiAPC40() {
    channel = 0;
}

void MidiAPC40::UpdateMode(unsigned char mode) {

    /* Sanitize input */
    if (mode > 2) {
        mode = 2;
    }

    /* Create mode change packet */
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

    /* Add mode change */
    message[7] += mode;

    /* Send Message */
    midi_out->sendMessage(&message);


    /* Create mode change packet */
    message.clear();
    message = std::vector<unsigned char> {0x90,
                                        0x33,
                                        B_ON};

    /* Send Message */
    midi_out->sendMessage(&message);
}

void MidiAPC40::UpdateLed(unsigned char controlID, unsigned char channel, unsigned char state) {

}

void MidiAPC40::UpdateClipLaunch(unsigned char row, unsigned char column, unsigned char state) {

}

void MidiAPC40::SetChannel(int channel) {
    if(this->channel == channel) {
        return;
    }

    /* Create mode change packet */
    std::vector<unsigned char> message {0x80,
                                        0x33,
                                        0x00};

    message[0] |= this->channel;

    /* Send Message */
    midi_out->sendMessage(&message);

    this->channel = channel;

    message[0] = this->channel | 0x90;
    message[2] = B_ON;

    /* Send Message */
    midi_out->sendMessage(&message);
}

void MidiAPC40::HandleMidi(double deltatime, std::vector< unsigned char > *message, void *userData)
{
    MidiDispatch* md = (MidiDispatch*) userData;
    Dispatch* dispatch = md->dispatch;
    MidiAPC40* midi_device = (MidiAPC40*)md->midi_device;
    
    /* Print Message */
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if ( nBytes > 0 )
        std::cout << "stamp = " << deltatime << std::endl;

    /* Decode byte 0 */
    unsigned char type = ((unsigned char)message->at(0)) >> 4;
    unsigned char channel = (unsigned char)0x0F & ((unsigned char)message->at(0));

    if (nBytes != 3) {
        std::cout << "Unknown length of midi message received!" << std::endl;
        return;
    }

    /* Handle Channel Change */
    if(message->at(1) == 51 && (type == 0x09 || type == 0x08)) {
        midi_device->SetChannel(channel);
    }

    /* Handle Beam Update */
    else {
        midi_device->HandleMidiChannel(message, dispatch, channel);
    }
}

void MidiAPC40::HandleMidiChannel(std::vector< unsigned char > *message, Dispatch *dispatch, int channel) {
    std::string subject;

    switch ((int)message->at(1))
    {
        case 7:
            subject = "intensity_ch" + std::to_string(channel + 1);
            break;
        case 16:
            subject = "count_1_ch" + std::to_string(this->channel + 1);
            break;
        case 17:
            subject = "count_2_ch" + std::to_string(this->channel + 1);
            break;
        case 20:
            subject = "size_1_ch" + std::to_string(this->channel + 1);
            break;
        case 21:
            subject = "size_2_ch" + std::to_string(this->channel + 1);
            break;
        case 48:
            subject = "hue_ch" + std::to_string(this->channel + 1);
            break;
        case 49:
            subject = "window_ch" + std::to_string(this->channel + 1);
            break;
        case 50:
            subject = "repeat_ch" + std::to_string(this->channel + 1);
            break;
        case 51:
            subject = "saturation_ch" + std::to_string(this->channel + 1);
            break;
        default:
            std::cout << "Unknown midi message received!" << std::endl;
            return;
    }

    dispatch->GetParameter(subject)->SetVal((double) message->at(2));
}