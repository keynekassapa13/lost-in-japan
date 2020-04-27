#ifndef CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER
#define CG1RAYTRACER_MATERIALS_COOKTORRANCE_HEADER

#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <vector>

namespace rt {

class CookTorranceMaterial: public Material {
public:

	CookTorranceMaterial(Texture* texture, float kd, float ks, float r);
	virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
	virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
	virtual Sampling useSampling() const;

private:
	Texture* tex;

	float kd;
	float fs;
	float r;
};

}

#endif