//
// Created by ponderosa on 6/3/19.
//

#ifndef TWILIGHT_TUNNEL_H
#define TWILIGHT_TUNNEL_H

#include "beam.h"

class Tunnel: public Beam {

private:
    double x_origin;
    double y_origin;
    int num_segment;
    int width;
    int height;
    double originAngle;

public:
    Tunnel(int, int);
    //~Tunnel();

    void OnFrame() override;
    void OnRender(BLContext *ctx) override;
};


#endif //TWILIGHT_TUNNEL_H
