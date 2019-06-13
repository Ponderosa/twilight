//
// Created by ponderosa on 6/3/19.
//

#include <math.h>
#include "tunnel.h"
#include "observer/dispatch.h"
#include "observer/animator.h"

Tunnel::Tunnel(int width, int height, int channel, Dispatch* dispatch) {
    this->width = width;
    this->height = height;

    color = new Color(channel, dispatch);

    num_segment = new Animator(dispatch->GetParameter("count_1_ch" + std::to_string(channel)), 0, 127);
    blanking = new Animator(dispatch->GetParameter("count_2_ch" + std::to_string(channel)), 0, 127);
    radius = new Animator(dispatch->GetParameter("size_1_ch" + std::to_string(channel)), 0, 127);
    thickness = new Animator(dispatch->GetParameter("size_2_ch" + std::to_string(channel)), 0, 127);
    ellipse = new Animator(dispatch->GetParameter("size_3_ch" + std::to_string(channel)), 0, 127);
    chiclet_march = new Animator(dispatch->GetParameter("velocity_1_ch" + std::to_string(channel)), 0, 1);

    x_origin = 0.0;
    y_origin = 0.0;
    originAngle = 0.0;
}

void Tunnel::OnFrame(uint32_t tick) {
    // Local Declarations
    BLArc arc;
    int blank = blanking->GetScaled()/2 - 32;

    // Handle ticks for smooth rendering
    uint32_t tick_diff = tick - this->tick;
    originAngle += (double)tick_diff * 0.002 * chiclet_march->GetScaled();
    this->tick = tick;


    // Drop all arcs from last frame
    arcs.clear();

    // Check if we are positively blanking or negatively blanking
    for(int i = 0; i < num_segment->GetScaled(); ++i) {
        if ((blank == 0) || ((blank > 0) && (i % (blank + 1) == 0)) || ((blank < 0) && (i % blank))) {
            // Make an Arc
            arc.cx = double(width) / 2.0 + x_origin;
            arc.cy = double(height) / 2.0 + y_origin;
            arc.rx = radius->GetScaled() * 10;
            arc.ry = radius->GetScaled() * 10;
            arc.start = (originAngle + (360.0 / num_segment->GetScaled() * double(i)) * (M_PI / 180.0));
            arc.sweep = 360.0 / num_segment->GetScaled() * (M_PI / 180.0);
            arcs.push_back(arc);
        }
    }
}

void Tunnel::OnRender(BLContext *ctx) {
    // Stroke
    ctx->setCompOp(BL_COMP_OP_SRC_OVER);
    ctx->setStrokeWidth(thickness->GetScaled() * 10);
    ctx->setStrokeStartCap(BL_STROKE_CAP_BUTT);
    ctx->setStrokeEndCap(BL_STROKE_CAP_BUTT);

    // Geometry
    std::list<BLArc>::iterator it;

    // Color set
    color->SetCount(arcs.size());

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = arcs.begin(); it != arcs.end(); it++) {
        ctx->setStrokeStyle(color->GetNextColor());
        ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &(*it));
    }

}

