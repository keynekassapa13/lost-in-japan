#include <rt/materials/glass.h>
#include <core/random.h>
#include <core/scalar.h>

namespace rt {

GlassMaterial::GlassMaterial(float eta)
{
    this->eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    return RGBColor::rep(1.0f);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    Vector r_dir;
    float cos = dot(outDir, normal);
    Vector c_n = normal; float c_eta = eta;

    if (cos <= 0) {
        c_eta = 1.0f / eta;
        c_n = -normal;
        cos = -cos;
    }

    float r1 = random();
    if (r1 > 0.8) {
        r_dir = (-outDir + 2 * cos * c_n);
    } else {
        r_dir = -outDir / c_eta - (
                sqrtf(1.0f - (1.0f - cos * cos) / (c_eta * c_eta))
                - cos / c_eta
            ) * c_n;
    }
    
    return SampleReflectance(r_dir.normalize(), RGBColor::rep(1.0f));
}

Material::Sampling GlassMaterial::useSampling() const {
    return Material::SAMPLING_ALL;
}

}