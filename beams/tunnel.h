//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_TUNNEL_H
#define TWILIGHT_TUNNEL_H

#include <list>
#include "beam.h"

class Tunnel: public Beam {
public:
    Tunnel(int, int);
    void OnFrame(uint32_t tick) override;
    void OnRender(BLContext *ctx) override;
private:
    double x_origin;
    double y_origin;
    int num_segment;
    int width;
    int height;
    int blanking;
    double originAngle;
    double radius;
    double thickness;
    uint32_t tick;

    std::list<BLArc> arcs;
};


#endif //TWILIGHT_TUNNEL_H
