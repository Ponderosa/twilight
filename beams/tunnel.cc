//
// Created by ponderosa on 6/3/19.
//

#include <math.h>
#include "twilight.h"
#include "tunnel.h"
#include "observer/dispatch.h"
#include "observer/observer.h"

Tunnel::Tunnel(int width, int height, int channel, Dispatch* dispatch, ClockManager *clocks) {
    this->width = width;
    this->height = height;

    color = new Color(channel, dispatch);

    num_segment = new Observer(dispatch->GetSubject("count_1_ch" + std::to_string(channel)), 0, 127);
    blanking = new Observer(dispatch->GetSubject("count_2_ch" + std::to_string(channel)), 0, 127);
    radius = new Observer(dispatch->GetSubject("size_1_ch" + std::to_string(channel)), 0, 1270);
    thickness = new Observer(dispatch->GetSubject("size_2_ch" + std::to_string(channel)), 0, 1270);
    ellipse = new Observer(dispatch->GetSubject("size_3_ch" + std::to_string(channel)), -500, 500);
    chiclet_march = new Observer(dispatch->GetSubject("velocity_1_ch" + std::to_string(channel)), -1, 1);
    context_rotate = new Observer(dispatch->GetSubject("velocity_2_ch" + std::to_string(channel)), -1, 1);
    chiclet_march_clock_master = new Observer(dispatch->GetSubject("velocity_1_clock_master_ch" + std::to_string(channel)), 0, NUMBER_OF_CLOCKS);
    context_rotate_clock_master = new Observer(dispatch->GetSubject("velocity_2_clock_master_ch" + std::to_string(channel)), 0, NUMBER_OF_CLOCKS);

    x_origin = 0.0;
    y_origin = 0.0;
    originAngle = 0.0;
    //tick = 0;

    this->clocks = clocks;
}

void Tunnel::OnFrame(uint32_t tick) {
    // Local Declarations
    BLArc arc;
    int blank = blanking->GetScaled()/2 - 32;

    // Handle ticks for smooth rendering
    if(abs(chiclet_march->GetScaled()) > 0.02) {
        uint32_t tick_diff = clocks->GetTickDiff(chiclet_march_clock_master->GetScaled());
        originAngle += (double) tick_diff * 0.002 * chiclet_march->GetScaled();
    }

    // Handle ticks for smooth rendering
    if(abs(context_rotate->GetScaled()) > 0.02) {
        uint32_t tick_diff = clocks->GetTickDiff(context_rotate_clock_master->GetScaled());
        contextAngle += (double) tick_diff * 0.002 * context_rotate->GetScaled();
    }

    // Drop all arcs from last frame
    arcs.clear();

    // Save thickness for rendering
    scaled_thickness = thickness->GetScaled();

    // Check if we are positively blanking or negatively blanking
    for(int i = 0; i < num_segment->GetScaled(); ++i) {
        if ((blank == 0) || ((blank > 0) && (i % (blank + 1) == 0)) || ((blank < 0) && (i % blank))) {
            // Make an Arc
            arc.start = (originAngle + (360.0 / num_segment->GetScaled() * double(i)) * (M_PI / 180.0));
            arc.sweep = 360.0 / num_segment->GetScaled() * (M_PI / 180.0);

            arc.rx = radius->GetScaled() + thickness->GetScaled() / 2;
            arc.ry = radius->GetScaled() + thickness->GetScaled() / 2;

            double center_angle = arc.start + arc.sweep/2;
            arc.cx = double(width) / 2.0 + x_origin + ellipse->GetScaled() * cos(center_angle);
            arc.cy = double(height) / 2.0 + y_origin;

            arcs.push_back(arc);
        }
    }
}

void Tunnel::OnRender(BLContext *ctx) {
    // Stroke
    ctx->setCompOp(BL_COMP_OP_SRC_OVER);
    ctx->setStrokeWidth(scaled_thickness);
    ctx->setStrokeStartCap(BL_STROKE_CAP_BUTT);
    ctx->setStrokeEndCap(BL_STROKE_CAP_BUTT);

    // Geometry
    std::list<BLArc>::iterator it;

    // Color set
    color->SetCount(arcs.size());

    ctx->rotate(contextAngle, double(width) / 2.0 + x_origin, double(height) / 2.0 + y_origin);

    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (it = arcs.begin(); it != arcs.end(); it++) {
        ctx->setStrokeStyle(color->GetNextColor());
        ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &(*it));
    }
}

