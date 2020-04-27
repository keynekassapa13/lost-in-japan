#ifndef CG1RAYTRACER_SOLIDS_ENV_HEADER
#define CG1RAYTRACER_SOLIDS_ENV_HEADER

#include <rt/solids/solid.h>
#include <rt/intersection.h>

namespace rt {

class Env : public Solid {
public:
    Env() {}
    Env(CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;

private:
	Point center;
    float radius;
	Vector normal;
};

}

#endif