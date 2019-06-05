//
// Created by ponderosa on 6/4/19.
//

// Create variables and allow beams to attach to them.
// Also create midi device

#include <vector>
#include <string>
#include "system.h"
#include "dispatch.h"

Dispatch::Dispatch() {
    // Create Subjects
    std::string subject_name;

    //Create an iterator of std::list
    std::list<std::string>::iterator it;

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = subject_master.begin(); it != subject_master.end(); it++) {
        // Access the object through iterator
        subject_name = *it;
        //for()
    }
}