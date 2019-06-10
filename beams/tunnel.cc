//
// Created by ponderosa on 6/3/19.
//

#include <math.h>
#include "tunnel.h"
#include "observer/dispatch.h"

Tunnel::Tunnel(int width, int height, int channel, Dispatch* dispatch) {
    this->width = width;
    this->height = height;

    num_segment = new Observer(dispatch->GetSubject("count_1_ch" + std::to_string(channel)), 20.0);
    blanking = new Observer(dispatch->GetSubject("count_2_ch" + std::to_string(channel)), 1);
    radius = new Observer(dispatch->GetSubject("size_1_ch" + std::to_string(channel)), 60);
    thickness = new Observer(dispatch->GetSubject("size_2_ch" + std::to_string(channel)), 10);
    ellipse = new Observer(dispatch->GetSubject("size_3_ch" + std::to_string(channel)), 1);

    x_origin = 0.0;
    y_origin = 0.0;
    originAngle = 0.0;
}

void Tunnel::OnFrame(uint32_t tick) {
    // Local Declarations
    BLArc arc;
    int blank = blanking->GetValue()/2 - 32;

    // Handle ticks for smooth rendering
    uint32_t tick_diff = tick - this->tick;
    //originAngle += 0.01;
    originAngle += (float)tick_diff * 0.0001;
    this->tick = tick;


    // Drop all arcs from last frame
    arcs.clear();

    // Check if we are positively blanking or negatively blanking
    for(int i = 0; i < num_segment->GetValue(); ++i) {
        if ((blank == 0) || ((blank > 0) && (i % (blank + 1) == 0)) || ((blank < 0) && (i % blank))) {
            // Make an Arc
            arc.cx = double(width) / 2.0 + x_origin;
            arc.cy = double(height) / 2.0 + y_origin;
            arc.rx = radius->GetValue() * 10;
            arc.ry = radius->GetValue() * 10;
            arc.start = (originAngle + (360.0 / num_segment->GetValue() * double(i)) * (M_PI / 180.0));
            arc.sweep = 360.0 / num_segment->GetValue() * (M_PI / 180.0);
            arcs.push_back(arc);
        }
    }
}

void Tunnel::OnRender(BLContext *ctx) {
    BLRgba32 *color = new BLRgba32(0xFF1F7FFF);
    color->a = 0xFF;


    // Stroke
    ctx->setCompOp(BL_COMP_OP_SRC_OVER);
    ctx->setStrokeStyle(BLRgba32(0xFF1F7FFF));
    ctx->setStrokeWidth(thickness->GetValue() * 10);
    ctx->setStrokeStartCap(BL_STROKE_CAP_BUTT);
    ctx->setStrokeEndCap(BL_STROKE_CAP_BUTT);

    // Geometry
    std::list<BLArc>::iterator it;

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = arcs.begin(); it != arcs.end(); it++) {
        ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &(*it));
    }

}

