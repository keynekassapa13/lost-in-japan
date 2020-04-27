#include <rt/materials/dummy.h>
#include <core/assert.h>
#include <math.h>
#include <cfloat>
#include <cmath>

namespace rt {

DummyMaterial::DummyMaterial() {
}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	float cosine = std::abs(dot(inDir.normalize(), normal));
	return RGBColor::rep(cosine);
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return Material::SampleReflectance(normal, RGBColor::rep(0.0f));
}

}