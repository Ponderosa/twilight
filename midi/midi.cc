//
// Created by ponderosa on 6/4/19.
//

#include "midi.h"
#include "RtMidi.h"

Midi::Midi() {
    CreateAPC();
}

void Midi::CreateAPC() {
    //RtMidiOut *midiout = 0;
    MidiOut[0] = 0;
    const unsigned char mode = 0x01;
    std::vector<unsigned char> message {0xF0,
                                        0x47,
                                        0x00,
                                        0x73,
                                        0x60,
                                        0x00,
                                        0x04,
                                        (0x40 + mode),
                                        0x08,
                                        0x04,
                                        0x01,
                                        0xF7};

    // RtMidiOut constructor
    try {
        MidiOut[0] = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    // Call function to select port.
    try {
        if ( ChooseMidiPort( MidiOut[0] ) == false ) exit( EXIT_FAILURE );;
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }


    MidiOut[0]->sendMessage( &message );

};

bool Midi::ChooseMidiPort( RtMidiOut *rtmidi )
{
    std::cout << "\nWould you like to open a virtual output port? [y/N] ";

    std::string keyHit;
    std::getline( std::cin, keyHit );
    if ( keyHit == "y" ) {
        rtmidi->openVirtualPort();
        return true;
    }

    std::string portName;
    unsigned int i = 0, nPorts = rtmidi->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No output ports available!" << std::endl;
        return false;
    }

    if ( nPorts == 1 ) {
        std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
    }
    else {
        for ( i=0; i<nPorts; i++ ) {
            portName = rtmidi->getPortName(i);
            std::cout << "  Output port #" << i << ": " << portName << '\n';
        }

        do {
            std::cout << "\nChoose a port number: ";
            std::cin >> i;
        } while ( i >= nPorts );
    }

    std::cout << "\n";
    rtmidi->openPort( i );

    return true;
}
