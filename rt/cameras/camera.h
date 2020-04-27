#ifndef CG1RAYTRACER_CAMERAS_CAMERA_HEADER
#define CG1RAYTRACER_CAMERAS_CAMERA_HEADER

#include <core/assert.h>
#include <rt/ray.h>

namespace rt {

class Camera {
public:
    virtual Ray getPrimaryRay(float x, float y) const = 0;
};

}

#endif
