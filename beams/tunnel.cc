//
// Created by ponderosa on 6/3/19.
//

#include <math.h>
#include "tunnel.h"

Tunnel::Tunnel(int width, int height) {
    x_origin = 0.0;
    y_origin = 0.0;
    num_segment = 20;
    originAngle = 0.0;
    this->width = width;
    this->height = height;
    radius = 600;
    thickness = 100;
    blanking = 1;
}

void Tunnel::OnFrame(uint32_t tick) {
    uint32_t tick_diff = tick - this->tick;
    //originAngle += 0.01;
    originAngle += (float)tick_diff * 0.0001;
    this->tick = tick;
    BLArc arc;

    // Drop all arcs from last frame
    arcs.clear();

    // Check if we are positively blanking or negatively blanking
    for(int i = 0; i < num_segment; ++i) {
        if ((blanking == 0) || ((blanking > 0) && (i % (blanking + 1) == 0)) || ((blanking < 0) && (i % blanking))) {
            // Make an Arc
            arc.cx = double(width) / 2.0 + x_origin;
            arc.cy = double(height) / 2.0 + y_origin;
            arc.rx = radius;
            arc.ry = radius;
            arc.start = (originAngle + (360.0 / num_segment * float(i)) * (M_PI / 180.0));
            arc.sweep = 360.0 /num_segment * (M_PI / 180.0);
            arcs.push_back(arc);
        }
    }
}

void Tunnel::OnRender(BLContext *ctx) {

    // Stroke
    ctx->setCompOp(BL_COMP_OP_SRC_OVER);
    ctx->setStrokeStyle(BLRgba32(0xFF1F7FFF));
    ctx->setStrokeWidth(thickness);
    ctx->setStrokeStartCap(BL_STROKE_CAP_BUTT);
    ctx->setStrokeEndCap(BL_STROKE_CAP_BUTT);

    // Geometry
    std::list<BLArc>::iterator it;

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = arcs.begin(); it != arcs.end(); it++) {
        ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &(*it));
    }

}

