//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_TUNNEL_H
#define TWILIGHT_TUNNEL_H

#include <list>
#include "beam.h"
#include "observer/dispatch.h"
#include "color.h"
#include "clock/clock_manager.h"

class Tunnel: public Beam {
public:
    Tunnel(int, int, int, Dispatch*, ClockManager*);
    void OnFrame(uint32_t tick) override;
    void OnRender(BLContext *ctx) override;
private:

    int width;
    int height;

    Color* color;

    Observer* num_segment;
    Observer* blanking;
    Observer* radius;
    Observer* thickness;
    Observer* ellipse;
    Observer* chiclet_march;
    Observer* context_rotate;
    Observer* chiclet_march_clock_master;
    Observer* context_rotate_clock_master;

    double scaled_thickness;
    double x_origin;
    double y_origin;
    double originAngle;
    double contextAngle;

    //uint32_t tick;
    ClockManager *clocks;

    std::vector<BLArc> arcs;
};


#endif //TWILIGHT_TUNNEL_H
