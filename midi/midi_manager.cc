//
// Created by ponderosa on 6/4/19.
//

#include "midi_manager.h"
#include "RtMidi.h"
#include "midi_apc_40.h"
#include "observer/dispatch.h"


MidiManager::MidiManager(Dispatch *dispatch) {
    if(!AutoSetup(dispatch)) {
        std::cout << "APC40 Setup Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool MidiManager::AutoSetup(Dispatch *dispatch) {
    RtMidiIn *midi_in = new RtMidiIn();
    RtMidiOut *midi_out = new RtMidiOut();
    MidiAPC40 *midi_device = new MidiAPC40();


    // Get number of output ports
    std::string portName;
    unsigned int i = 0, nPorts = midi_out->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No output ports available!" << std::endl;
        return false;
    }

    // Scan each port for the APC40
    for ( i=0; i<nPorts; i++ ) {
        portName = midi_out->getPortName(i);
        std::cout << "  Output port #" << i << ": " << portName << '\n';

        // Search for APC
        if (portName.find("APC40") != std::string::npos) {
            std::cout << "APC40 Out Found " << std::endl;
            midi_out->openPort(i);
            midi_device->SetMidiOut(midi_out);
            break;
        }
    }

    // Get number of input ports
    nPorts = midi_in->getPortCount();
    if(nPorts == 0) {
        std::cout << "No output ports available!" << std::endl;
        return false;
    }

    // Scan each port for the APC40
    for ( i=0; i<nPorts; i++ ) {
        portName = midi_in->getPortName(i);
        std::cout << "  Input port #" << i << ": " << portName << '\n';

        // Search for APC
        if (portName.find("APC40") != std::string::npos) {
            std::cout << "APC40 In Found " << std::endl;
            midi_in->openPort(i);

            struct MidiDispatch *md = new MidiDispatch();
            md->dispatch = dispatch;
            md->midi_device = midi_device;

            midi_in->setCallback(&MidiAPC40::HandleMidi, md);
            midi_device->SetMidiIn(midi_in);
            break;
        }
    }

    // Check if APC40 was properly setup
    if(midi_device->SetupComplete() == false) {
        // Destroy objects and return false
        delete(midi_device);
        delete(midi_in);
        delete(midi_out);
        return false;
    }

    // Change mode to something we can work with
    ((MidiAPC40*)midi_device)->UpdateMode(dispatch, 1);
    devices.insert(std::make_pair("APC40", midi_device));

    return true;
}

