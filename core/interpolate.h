#ifndef CG1RAYTRACER_INTERPOLATE_HEADER
#define CG1RAYTRACER_INTERPOLATE_HEADER

#include <core/assert.h>

namespace rt {

template <typename T>
inline T lerp(const T& px0, const T& px1, float xPoint);

template <typename T>
inline T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight);

template <typename T>
inline T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xPoint, float yPoint);

template <typename T>
inline T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint);

//Point class has no + operator. You need to cast it to/from Float4 to do lerp. We add these for convenience:
class Point;

Point lerp(const Point& px0, const Point& px1, float xPoint);
Point lerpbar(const Point& px0, const Point& px1, const Point& px2, float xWeight, float yWeight);
Point lerp2d(const Point& px0y0, const Point& px1y0, const Point& px0y1, const Point& px1y1, float xPoint, float yPoint); 
Point lerp3d(const Point& px0y0z0, const Point& px1y0z0, const Point& px0y1z0, const Point& px1y1z0,
    const Point& px0y0z1, const Point& px1y0z1, const Point& px0y1z1, const Point& px1y1z1,
    float xPoint, float yPoint, float zPoint);

}

#include "interpolate-impl.h"

#endif