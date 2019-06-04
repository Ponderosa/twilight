//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_DISPATCH_H
#define TWILIGHT_DISPATCH_H


class Dispatch {
    Dispatch();
    void add_midi_device();
    void add_UI();
    void add_YAML();

    void attach_state();
    void get_state();
    void notify();
};


#endif //TWILIGHT_DISPATCH_H
