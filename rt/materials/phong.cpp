#include <rt/materials/phong.h>
#include <math.h>
#include <core/scalar.h>
#include <rt/textures/texture.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    this->s = specular;
    this->e = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    
    float cos = dot(inDir, normal);
    Vector R = (2 * cos * normal - inDir).normalize();
    if (dot(R, normal) < 0 || dot(inDir, normal) < 0) return RGBColor(0, 0, 0);
    float RV = dot(outDir.normalize(), R.normalize());
    if (RV < 0) return RGBColor(0, 0, 0);
    RGBColor ps = s->getColor(texPoint) * powf(RV, e);
    // Normalized
    return ps * (e + 2) / (2 * pi) * cos;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(0.0f, 0.0f, 0.0f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	Vector R = (2 * dot(outDir, normal) * normal - outDir).normalize();
    return SampleReflectance(R, PhongMaterial::getReflectance(texPoint, normal, outDir, R)); 
}

Material::Sampling PhongMaterial::useSampling() const {
	return Material::Sampling::SAMPLING_NOT_NEEDED;
}

}