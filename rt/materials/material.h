#ifndef CG1RAYTRACER_MATERIALS_MATERIAL_HEADER
#define CG1RAYTRACER_MATERIALS_MATERIAL_HEADER

#include <core/vector.h>
#include <core/color.h>

namespace rt {

class Material {
public:
	/*
	  inDir - the direction the light is incoming from
	  outDir - the direction the light is leaving the surface to the viewer
	  inDir and outDir point -away- from the hit point
	*/
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const = 0;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const = 0;


    struct SampleReflectance {
        Vector direction;
        RGBColor reflectance;
        SampleReflectance(const Vector& direction, const RGBColor& weight) : direction(direction), reflectance(weight) {}
        SampleReflectance() : direction(0,0,1), reflectance(0.0f,0.0f,0.0f) {}
    };

    enum Sampling {
        SAMPLING_NOT_NEEDED,
        SAMPLING_SECONDARY,
        SAMPLING_ALL
    };
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const = 0;
    virtual Sampling useSampling() const = 0;
    virtual ~Material() {}
};

}

#endif