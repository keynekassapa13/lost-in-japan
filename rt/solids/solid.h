#ifndef CG1RAYTRACER_SOLIDS_SOLID_HEADER
#define CG1RAYTRACER_SOLIDS_SOLID_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/primitive.h>

namespace rt {

class Material;
class CoordMapper;

/*
A solid is a physical primitive that has material and can be textured
*/
class Solid : public Primitive {
public:
    struct Sample {
        Point point;
        Vector normal;
    };

    Material* material;
    CoordMapper* texMapper;
    explicit Solid(CoordMapper* texMapper = nullptr, Material* material = nullptr);
    virtual Sample sample() const = 0;
    virtual float getArea() const = 0;
    virtual void setMaterial(Material* m) { material = m; }
    virtual void setCoordMapper(CoordMapper* cm) { texMapper = cm; }
};

}


#endif