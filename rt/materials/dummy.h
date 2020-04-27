#ifndef CG1RAYTRACER_MATERIALS_DUMMY_HEADER
#define CG1RAYTRACER_MATERIALS_DUMMY_HEADER

#include <rt/materials/material.h>

namespace rt {

class DummyMaterial : public Material {
public:
    DummyMaterial();
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const { return Material::SAMPLING_NOT_NEEDED; }
};

}

#endif