#ifndef CG1RAYTRACER_MATERIALS_PHONG_HEADER
#define CG1RAYTRACER_MATERIALS_PHONG_HEADER

#include <rt/materials/material.h>

namespace rt {

class Texture;

class PhongMaterial : public Material {
public:
    PhongMaterial(Texture* specular, float exponent);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;
    Texture* s;
    float e;
    
};

}

#endif