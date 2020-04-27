#ifndef CG1RAYTRACER_MATERIALS_FLATMATERIAL_HEADER
#define CG1RAYTRACER_MATERIALS_FLATMATERIAL_HEADER

#include <rt/materials/material.h>

namespace rt {

class Texture;

class FlatMaterial : public Material {
public:
    FlatMaterial(Texture* texture);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
    Texture* texture;
};

}

#endif