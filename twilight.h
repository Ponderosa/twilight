//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_TWILIGHT_H
#define TWILIGHT_TWILIGHT_H

#include <list>
#include <string>

#define WIDTH 1920
#define HEIGHT 1080
#define SET_FULLSCREEN 0

const int NUMBER_OF_CHANNELS = 8;

const std::list<std::string> SUBJECT_MASTER =
        std::list<std::string>({"intensity", "mask", "bump", "mute"});

const std::list<std::string> SUBJECT_COLOR =
        std::list<std::string>({"module", "pattern", "repeat"});

const std::list<std::string> SUBJECT_SHAPE =
        std::list<std::string>({"count_1", "count_2", "size_1", "size_2", "size_3",
                                "origin_x", "origin_y"});

const std::list<std::string> SUBJECT_VELOCITY =
        std::list<std::string>({"velocity_1", "velocity_2"});

#endif //TWILIGHT_TWILIGHT_H
