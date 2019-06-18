//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_TUNNEL_H
#define TWILIGHT_TUNNEL_H

#include <list>
#include "beam.h"
#include "observer/dispatch.h"
#include "color.h"

class Tunnel: public Beam {
public:
    Tunnel(int, int, int, Dispatch*);
    void OnFrame(uint32_t tick) override;
    void OnRender(BLContext *ctx) override;
private:
    int width;
    int height;

    Color* color;

    Observer* num_segment;
    Observer * blanking;
    Observer* radius;
    Observer* thickness;
    Observer* ellipse;
    Observer* chiclet_march;

    double x_origin;
    double y_origin;
    double originAngle;

    uint32_t tick;

    std::list<BLArc> arcs;
};


#endif //TWILIGHT_TUNNEL_H
