//
// Created by ponderosa on 6/3/19.
//

#include <math.h>
#include "tunnel.h"

Tunnel::Tunnel(int width, int height) {
    x_origin = 0.0;
    y_origin = 0.0;
    num_segment = 3;
    originAngle = 0.0;
    this->width = width;
    this->height = height;
}

void Tunnel::OnFrame() {

}

void Tunnel::OnRender(BLContext *ctx) {
    originAngle += 0.01;

    // Compose Arcs
    BLArc arc(width / 2, height / 2, 200, 200, originAngle + 0, 60.0  * (M_PI/180.0));
    BLArc arc2(width / 2, height / 2, 200, 200, originAngle + 120.0  * (M_PI/180.0), 60.0  * (M_PI/180.0));
    BLArc arc3(width / 2, height / 2, 200, 200, originAngle + 240.0  * (M_PI/180.0), 60.0  * (M_PI/180.0));

    // Stroke
    ctx->setCompOp(BL_COMP_OP_SRC_OVER);
    ctx->setStrokeStyle(BLRgba32(0xFF1F7FFF));
    ctx->setStrokeWidth(100);
    ctx->setStrokeStartCap(BL_STROKE_CAP_BUTT);
    ctx->setStrokeEndCap(BL_STROKE_CAP_BUTT);

    // Geometry
    ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &arc);
    ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &arc2);
    ctx->strokeGeometry(BL_GEOMETRY_TYPE_ARC, &arc3);

}

