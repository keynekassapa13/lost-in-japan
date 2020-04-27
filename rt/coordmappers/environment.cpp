#include <rt/coordmappers/environment.h>

namespace rt {

EnvironmentMapper::EnvironmentMapper() {
}

Point EnvironmentMapper::getCoords(const Intersection& hit) const {
    // Create a new coordinate mapper EnvironmentMapper that will ignore
    // the local/global hit coordinates and use the hit ray direction instead.
    return Point(hit.ray.d.x, hit.ray.d.y, hit.ray.d.z);
}

}