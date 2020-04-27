#ifndef CG1RAYTRACER_RAY_HEADER
#define CG1RAYTRACER_RAY_HEADER

#include <core/vector.h>
#include <core/point.h>

namespace rt {

class Ray {
public:
    Point o;
    Vector d;

    Ray() {}
    Ray(const Point& o, const Vector& d);
    Point getPoint(float distance) const;
};

}

#endif