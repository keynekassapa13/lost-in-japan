
#include <core/interpolate.h>
#include <core/point.h>
#include <core/float4.h>

namespace rt {

Point lerp(const Point& px0, const Point& px1, float xPoint) { return Point(lerp(Float4(px0), Float4(px1), xPoint)); }
Point lerpbar(const Point& px0, const Point& px1, const Point& px2, float xWeight, float yWeight) { return Point(lerpbar(Float4(px0), Float4(px1), Float4(px2), xWeight, yWeight)); }
Point lerp2d(const Point& px0y0, const Point& px1y0, const Point& px0y1, const Point& px1y1, float xPoint, float yPoint) {
    return Point(lerp2d(Float4(px0y0), Float4(px1y0),  Float4(px0y1), Float4(px1y1), xPoint, yPoint));
}
Point lerp3d(const Point& px0y0z0, const Point& px1y0z0, const Point& px0y1z0, const Point& px1y1z0,
    const Point& px0y0z1, const Point& px1y0z1, const Point& px0y1z1, const Point& px1y1z1,
    float xPoint, float yPoint, float zPoint) {
        return Point(lerp3d(Float4(px0y0z0), Float4(px1y0z0), Float4(px0y1z0), Float4(px1y1z0), 
            Float4(px0y0z1), Float4(px1y0z1), Float4(px0y1z1), Float4(px1y1z1), 
            xPoint, yPoint, zPoint));
}

}