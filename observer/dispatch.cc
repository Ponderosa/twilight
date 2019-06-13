//
// Created by ponderosa on 6/4/19.
//

// Create variables and allow beams to attach to them.
// Also create midi device

#include <vector>
#include <string>
#include "twilight.h"
#include "dispatch.h"


Dispatch::Dispatch() {
    CreateParameters(SUBJECT_MASTER, SUBJECT_MASTER_DEFAULT, NUMBER_OF_CHANNELS);
    CreateParameters(SUBJECT_COLOR, SUBJECT_COLOR_DEFAULT, NUMBER_OF_CHANNELS);
    CreateParameters(SUBJECT_SHAPE, SUBJECT_SHAPE_DEFAULT, NUMBER_OF_CHANNELS);
    CreateParameters(SUBJECT_VELOCITY, SUBJECT_VELOCITY_DEFAULT, NUMBER_OF_CHANNELS);
}

Parameter* Dispatch::GetParameter(std::string name) {
    return parameter_map.at(name);
}

void Dispatch::CreateParameters(std::vector<std::string> sub_list, std::vector<double> defaults, int num_channels) {
    // Create Subjects
    std::string subject_name;
    std::string subject_name_full;
    double def;
    Parameter *sub;

    //Create an iterator of std::list
    std::list<std::string>::const_iterator it;

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (int i = 0; i < sub_list.size(); ++i) {
        // Access the object through iterator
        subject_name = sub_list[i];
        def = defaults[i];

        // Check for num_channels <= 1
        if (num_channels <= 1) {
            sub = new Parameter(def/127.0);
            parameter_map[subject_name] = sub;
        } else {
            for (int j = 1; j <= num_channels; ++j) {
                subject_name_full = subject_name + "_ch" + std::to_string(j);
                sub = new Parameter(def/127.0);
                parameter_map[subject_name_full] = sub;
            }
        }
    }
}

