#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) {
    this->e1 = e1;
    this->e2 = e2;
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    
    Vector hp = hit.hitPoint() - Point::rep(0.0f);
    float u = dot(hp, e1) / e1.lensqr();
    float v = dot(hp, e2) / e2.lensqr();

    return Point(u, v, 0.0f);
}

}