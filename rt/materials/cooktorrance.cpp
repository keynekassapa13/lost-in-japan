#include <rt/materials/cooktorrance.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>
#include <math.h>
#include <vector>

namespace rt {

CookTorranceMaterial::CookTorranceMaterial(
    Texture* tex, float kd, float fs, float r) {
        this->kd = kd;
        this->fs = fs;
        this->r = r;
        this->tex = tex;
    }

RGBColor CookTorranceMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    Vector n = normal.normalize();
    RGBColor clr = RGBColor::rep(0.0f);

    clr = clr + kd * (tex->getColor(texPoint) * dot(inDir.normalize(), normal) / pi);
    Vector h = (inDir + outDir).normalize();

    float NI = dot(normal, inDir);
    float NH = dot(normal, h);
    float NO = dot(normal, outDir);
    float OH = dot(outDir, h);

    // Shlick
    float F = fs + (1 - fs) * powf((1 - OH), 5);

    // Beckmann
    float D = (1.0f / (pi * r * r * powf(NH, 4))) * 
        exp((NH * NH - 1) / (NH * NH * r * r));

    // Geometric
    float G_2 = 2 * NH * NO / OH;
    float G_3 = 2 * NH * NI / OH;
    float G = std::min(1.0f, std::min(G_2, G_3));

    // Cook Torrance
    float spec = F * D * G / (pi * NI * NO);

    clr = clr + ((1 - kd) * tex->getColor(texPoint) * NI * spec);
    return clr;
}

RGBColor CookTorranceMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor(0, 0, 0);
}

Material::SampleReflectance CookTorranceMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return SampleReflectance();
}

Material::Sampling CookTorranceMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}

