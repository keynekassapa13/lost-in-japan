#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    Point hp = hit.hitPoint();
    return Point(
        s.x * hp.x,
        s.y * hp.y,
        s.z * hp.z
    );
}

WorldMapper::WorldMapper()
{  
    this->s = Float4::rep(1.0f);
}

WorldMapper::WorldMapper(const Float4& scale)
{
    this->s = scale;
}

}