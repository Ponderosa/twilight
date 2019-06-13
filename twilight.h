//
// Created by ponderosa on 6/5/19.
//

#ifndef TWILIGHT_TWILIGHT_H
#define TWILIGHT_TWILIGHT_H

#include <list>
#include <string>
#include <vector>

//const int WIDTH = 1920;
//const int HEIGHT = 1080;
const int WIDTH = 2560;
const int HEIGHT = 1440;
const bool FPS_BEAM_ON = true;
const bool SET_FULLSCREEN = true;

const int NUMBER_OF_CHANNELS = 8;


const std::vector<std::string> SUBJECT_MASTER {"intensity", "mask", "bump", "mute"};
const std::vector<double> SUBJECT_MASTER_DEFAULT {0.0, 0.0, 0.0, 0.0};

const std::vector<std::string> SUBJECT_COLOR = {"pattern", "repeat", "saturation", "hue", "window"};
const std::vector<double> SUBJECT_COLOR_DEFAULT = {0.0, 0.0, 0.0, 0.0, 0.0};

const std::vector<std::string> SUBJECT_SHAPE
    {"count_1", "count_2", "size_1", "size_2", "size_3", "origin_x", "origin_y"};
const std::vector<double> SUBJECT_SHAPE_DEFAULT
    {126, 66, 45, 10, 0.0, 0.0, 0.0};

const std::vector<std::string> SUBJECT_VELOCITY {"velocity_1", "velocity_2"};
const std::vector<double> SUBJECT_VELOCITY_DEFAULT {64, 0.0};

#endif //TWILIGHT_TWILIGHT_H
