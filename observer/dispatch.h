//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_DISPATCH_H
#define TWILIGHT_DISPATCH_H

#include <list>
#include <string>
#include <map>
#include "subject.h"

class Dispatch {
public:
    Dispatch();
    void create_subjects();
    void add_midi_device();
    void add_UI();
    void add_YAML();
private:
    std::map<std::string, Subject> subject_map;
};


std::list<std::string> subject_master =
        std::list<std::string>({"intensity", "mask", "bump", "mute"});

std::list<std::string> subject_color =
        std::list<std::string>({"module", "pattern", "repeat"});

std::list<std::string> subject_shape =
        std::list<std::string>({"count_1", "count_2", "size_1", "size_2", "size_3",
                                "origin_x", "origin_y"});

std::list<std::string> subject_velocity =
        std::list<std::string>({"velocity_1", "velocity_2"});

#endif //TWILIGHT_DISPATCH_H
