//
// Created by ponderosa on 6/4/19.
//

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
                switch ((int)message->at(1))
                {
                    /* Count 1 */
                    case 16:
                        dispatch->SetSubject("count_1_ch1", (double) message->at(2));
                        break;
                    /* Count 1 */
                    case 17:
                        dispatch->SetSubject("count_2_ch1", (double) message->at(2));
                        break;
                    /* Count 1 */
                    case 20:
                        dispatch->SetSubject("size_1_ch1", (double) message->at(2));
                        break;
                    /* Count 1 */
                    case 21:
                        dispatch->SetSubject("size_2_ch1", (double) message->at(2));
                        break;
                    /* Count 1 */
                    case 22:
                        dispatch->SetSubject("size_3_ch1", (double) message->at(2));
                        break;
                }
                break;
            /* Channel 2 */
            case 177:
                break;
            default:
                std::cout << "Unknown midi message received!" << std::endl;
        }
    }
}