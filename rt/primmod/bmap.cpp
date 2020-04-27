#include <rt/primmod/bmap.h>
#include <rt/solids/triangle.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/world.h>
#include <core/assert.h>
#include <core/interpolate.h>
#include <core/color.h>
#include <rt/textures/texture.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale)
{
    this->base = base;
    this->bm = bumpmap;
    this->bv1 = bv1;
    this->bv2 = bv2;
    this->bv3 = bv3;
    this->vs = vscale;
}

BBox BumpMapper::getBounds() const {
    return base->getBounds();
}

Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
    Intersection hit_intersection = base->intersect(ray, previousBestDistance);
    if (hit_intersection) {
        Point uv = hit_intersection.local();

        Vector e1 = bv2 - bv1;
        Vector e2 = bv3 - bv1;

        float det = e1.x * e2.y - e1.y * e2.x;
        
        Vector wx = Vector::rep(0.0f), wy = Vector::rep(0.0f);
        if (std::abs(det) > epsilon) {
            Vector be1 = base->v2 - base->v1;
            Vector be2 = base->v3 - base->v1;

            wx = - Vector(
                e2.y * be1.x - e1.y * be2.x,
                e2.y * be1.y - e1.y * be2.y,
                e2.y * be1.z - e1.y * be2.z 
            ) / det;

            wy = - Vector(
                -e2.x * be1.x + e1.x * be2.x,
                -e2.x * be1.y + e1.x * be2.y,
                -e2.x * be1.z + e1.x * be2.z 
            ) / det;
        }

        Point uvw = Point(
            bv1.x * uv.x + bv2.x * uv.y + bv3.x * uv.z,
            bv1.y * uv.x + bv2.y * uv.y + bv3.y * uv.z,
            bv1.z * uv.x + bv2.z * uv.y + bv3.z * uv.z
        );

        RGBColor dx = bm->getColorDX(uvw);
        RGBColor dy = bm->getColorDY(uvw);

        float DX = (dx.r + dx.g + dx.b) / 3.0f;
        float DY = (dy.r + dy.g + dy.b) / 3.0f;

        Vector n = hit_intersection.normal() + wx * DX + wy * DY;

        return Intersection(hit_intersection.distance, hit_intersection.ray, hit_intersection.solid, n, hit_intersection.local());
    } else {return Intersection::failure();}

}

void BumpMapper::setMaterial(Material* m) {
    base->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    base->setCoordMapper(cm);
}

float BumpMapper::getArea() const {
    return 0;
}

}