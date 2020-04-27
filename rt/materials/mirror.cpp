#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt {

MirrorMaterial::MirrorMaterial(float eta, float kappa)
{
    // Fresnel
    this->eta = eta;
    this->kappa = kappa;
}

RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    float cos_NI = dot(normal.normalize(), inDir.normalize());
    float ek2 = eta * eta + kappa * kappa;

    float F_parallel =
        (ek2 * cos_NI * cos_NI - 2 * eta * cos_NI + 1 )
        / (ek2 * cos_NI * cos_NI + 2 * eta * cos_NI + 1 );
    float F_perpendicular =
        (ek2 - 2 * eta * cos_NI + cos_NI * cos_NI) 
        / (ek2 + 2 * eta * cos_NI + cos_NI * cos_NI);

    float Fr = 0.5f * (F_parallel + F_perpendicular);
    return RGBColor::rep(Fr);
}

RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    float cos = dot(outDir.normalize(), normal.normalize());
    Vector dir = (-outDir + 2 * cos * normal).normalize();
    return SampleReflectance(dir, getReflectance(texPoint, normal, -outDir, dir));
}

Material::Sampling MirrorMaterial::useSampling() const {
    return Material::Sampling::SAMPLING_ALL;
}

}
