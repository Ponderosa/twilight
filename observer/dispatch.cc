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
    CreateSubjects(SUBJECT_MASTER, NUMBER_OF_CHANNELS);
    CreateSubjects(SUBJECT_COLOR, NUMBER_OF_CHANNELS);
    CreateSubjects(SUBJECT_SHAPE, NUMBER_OF_CHANNELS);
    CreateSubjects(SUBJECT_VELOCITY, NUMBER_OF_CHANNELS);
}

Subject* Dispatch::GetSubject(std::string name) {
    return subject_map.at(name);
}

void Dispatch::SetSubject(std::string name, double value) {
    subject_map[name]->SetVal(value);
}


void Dispatch::CreateSubjects(std::list<std::string> sub_list, int num_channels) {
    // Create Subjects
    std::string subject_name;
    std::string subject_name_full;
    Subject *sub;

    //Create an iterator of std::list
    std::list<std::string>::const_iterator it;

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = sub_list.begin(); it != sub_list.end(); it++) {
        // Access the object through iterator
        subject_name = *it;

        // Check for num_channels <= 1
        if (num_channels <= 1) {
            sub = new Subject;
            sub->SetVal(0.0);
            subject_map[subject_name] = sub;
        } else {
            for (int i = 0; i < num_channels; ++i) {
                subject_name_full = subject_name + "_ch" + std::to_string(i);
                sub = new Subject;
                sub->SetVal(0.0);
                subject_map[subject_name_full] = sub;
            }
        }
    }
}