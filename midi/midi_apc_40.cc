//
// Created by ponderosa on 6/4/19.
//

#include <string>
#include "midi_apc_40.h"
#include "observer/dispatch.h"

MidiAPC40::MidiAPC40() {

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
}

void MidiAPC40::UpdateLed(unsigned char controlID, unsigned char channel, unsigned char state) {

}

void MidiAPC40::UpdateClipLaunch(unsigned char row, unsigned char column, unsigned char state) {

}

void MidiAPC40::HandleMidi(double deltatime, std::vector< unsigned char > *message, void *userData)
{
    Dispatch* dispatch = (Dispatch*) userData;

    /* Print Message */
    unsigned int nBytes = message->size();
    for ( unsigned int i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if ( nBytes > 0 )
        std::cout << "stamp = " << deltatime << std::endl;

    /* Handle Channel Change */



    /* Handle Beam Bin */

    /* Handle State Update */
    /* Check that we have a valid packet */
    if ( nBytes == 3) {
        switch ((int)message->at(0))
        {
            /* Channel 1 */
            case 176:
                HandleMidiChannel(message, dispatch, 1);
                break;
            /* Channel 2 */
            case 177:
                HandleMidiChannel(message, dispatch, 2);
                break;
            /* Channel 3 */
            case 178:
                HandleMidiChannel(message, dispatch, 3);
                break;
            /* Channel 4 */
            case 179:
                HandleMidiChannel(message, dispatch, 4);
                break;
            /* Channel 5 */
            case 180:
                HandleMidiChannel(message, dispatch, 5);
                break;
            /* Channel 6 */
            case 181:
                HandleMidiChannel(message, dispatch, 6);
                break;
            /* Channel 7 */
            case 182:
                HandleMidiChannel(message, dispatch, 7);
                break;
            /* Channel 8 */
            case 183:
                HandleMidiChannel(message, dispatch, 8);
                break;
            default:
                std::cout << "Unknown midi message received!" << std::endl;
        }
    }
}

void MidiAPC40::HandleMidiChannel(std::vector< unsigned char > *message, Dispatch *dispatch, int channel) {
    std::string subject;

    switch ((int)message->at(1))
    {
        /* Count 1 */
        case 7:
            subject = "intensity_ch" + std::to_string(channel);
            break;
            /* Count 1 */
        case 16:
            subject = "count_1_ch" + std::to_string(channel);
            break;
            /* Count 1 */
        case 17:
            subject = "count_2_ch" + std::to_string(channel);
            break;
            /* Count 1 */
        case 20:
            subject = "size_1_ch" + std::to_string(channel);
            break;
            /* Count 1 */
        case 21:
            subject = "size_2_ch" + std::to_string(channel);
            break;
            /* Count 1 */
        case 22:
            subject = "size_3_ch" + std::to_string(channel);
            break;
        default:
            std::cout << "Unknown midi message received!" << std::endl;
            return;
    }

    dispatch->SetSubject(subject, (double) message->at(2));
}