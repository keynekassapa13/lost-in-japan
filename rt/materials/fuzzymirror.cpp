#include <rt/materials/fuzzymirror.h>
#include <core/scalar.h>
#include <core/point.h>
#include <core/random.h>

namespace rt {

FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
    this->eta = eta;
    this->kappa = kappa;
    this->fa = fuzzyangle;
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
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

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.0f);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    float cos = dot(outDir, normal);
    Vector n = normal;
    if (cos < 0) {cos = -cos, n = -normal;}
    Vector dir = (-outDir + 2 * cos * n).normalize();
	
    Vector r_dir;
    int i = 0;
    
    // sample
    float r1 = random(), r2 = random();
    Vector dir_x = cross(dir, n).normalize();
    Vector dir_y = cross(dir, dir_x).normalize();

    float x = sqrtf(r1) * tanf(fa) * cosf(2 * pi * r2);
    float y = (2 * pi * r2) * sinf(sqrtf(r1) * tanf(fa));

    Point p = texPoint + dir + dir_x * x + dir_y * y;
    r_dir = (p - texPoint).normalize();

    return Material::SampleReflectance(r_dir, this->getReflectance(texPoint, n, outDir, r_dir));
}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
    return Material::Sampling::SAMPLING_ALL;
}

}
