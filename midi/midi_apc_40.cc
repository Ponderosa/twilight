//
// Created by ponderosa on 6/4/19.
//

#include <string>
#include <thread>
#include <chrono>
#include "midi_apc_40.h"
#include "observer/dispatch.h"
#include "midi_manager.h"

MidiAPC40::MidiAPC40() {
    channel = 0;
}

void MidiAPC40::UpdateMode(Dispatch* dispatch, unsigned char mode) {

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

    /* Turn on Channel 1 Led */
    //UpdateLed(NOTE_ON, 0x33, B_ON);

    for(int i = 7; i >= 0; --i) {
        SetChannel(dispatch, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

void MidiAPC40::UpdateRingLed(std::vector<unsigned char> *buffer) {

    for(unsigned char i = 0; i < buffer->size(); ++i) {
        if(i < 8) {
            UpdateLed(CONTINUOS, (i + 0x10), buffer->at(i));
        } else if (i < 16){
            UpdateLed(CONTINUOS, (i - 8 + 0x30), buffer->at(i));
        }
    }
}

void MidiAPC40::UpdateRingLed(Dispatch* dispatch) {
    /* Build buffer for current channel*/
    std::vector<unsigned char> buffer;
    unsigned char md;

    // DC 1
    md = (unsigned char) dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 2
    md = (unsigned char) dispatch->GetSubject("count_2_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 3
    md = (unsigned char) dispatch->GetSubject("velocity_1_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 4
    md = (unsigned char)dispatch->GetSubject("velocity_2_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 5
    md = (unsigned char) dispatch->GetSubject("size_1_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 6
    md = (unsigned char) dispatch->GetSubject("size_2_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // DC 7
    md = (unsigned char) dispatch->GetSubject("size_3_ch" + std::to_string(channel + 1))->GetMidi();
    //md = 0;
    buffer.push_back(md);
    // DC 8
    //md = (unsigned char)dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    md = 0;
    buffer.push_back(md);
    // TC 1
    md = (unsigned char) dispatch->GetSubject("hue_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // TC 2
    md = (unsigned char) dispatch->GetSubject("window_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // TC 3
    md = (unsigned char) dispatch->GetSubject("repeat_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // TC 4
    md = (unsigned char) dispatch->GetSubject("saturation_ch" + std::to_string(channel + 1))->GetMidi();
    buffer.push_back(md);
    // TC 5
    //md = (unsigned char)dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    md = 0;
    buffer.push_back(md);
    // TC 6
    //md = (unsigned char)dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    md = 0;
    buffer.push_back(md);
    // TC 7
    //md = (unsigned char)dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    md = 0;
    buffer.push_back(md);
    // TC 8
    //md = (unsigned char)dispatch->GetSubject("count_1_ch" + std::to_string(channel + 1))->GetMidi();
    md = 0;
    buffer.push_back(md);

    UpdateRingLed(&buffer);
}

void MidiAPC40::UpdateLed(unsigned char controlID, unsigned char channel, unsigned char state) {
    /* Create message */
    std::vector<unsigned char> message;

    message.push_back(controlID);
    message.push_back(channel);
    message.push_back(state);

    /* Send Message */
    midi_out->sendMessage(&message);
}

void MidiAPC40::UpdateClipLaunch(unsigned char row, unsigned char column, unsigned char state) {

}

void MidiAPC40::SetChannel(Dispatch* dispatch, int channel) {
    if(this->channel == channel) {
        return;
    }

    /* Change Channel Led */
    UpdateLed(NOTE_OFF | this->channel, 0x33, B_OFF);
    this->channel = channel;
    UpdateLed(NOTE_ON | this->channel, 0x33, B_ON);

    /* Load Channel ring data */
    UpdateRingLed(dispatch);
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
        midi_device->SetChannel(dispatch, channel);
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
        case 18:
            subject = "velocity_1_ch" + std::to_string(this->channel + 1);
            break;
        case 19:
            subject = "velocity_2_ch" + std::to_string(this->channel + 1);
            break;
        case 20:
            subject = "size_1_ch" + std::to_string(this->channel + 1);
            break;
        case 21:
            subject = "size_2_ch" + std::to_string(this->channel + 1);
            break;
        case 22:
            subject = "size_3_ch" + std::to_string(this->channel + 1);
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

    dispatch->GetSubject(subject)->SetMidi(message->at(2));
}