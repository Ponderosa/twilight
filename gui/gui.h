//
// Created by ponderosa on 6/17/19.
//

#ifndef TWILIGHT_GUI_H
#define TWILIGHT_GUI_H

#include "../observer/dispatch.h"

class Gui {
public:
    Gui(Dispatch *dispatch):dispatch(dispatch){};
    void operator()();
private:
    Dispatch *dispatch;
};


#endif //TWILIGHT_GUI_H
