#include <rt/lights/ambient.h>
#include <rt/materials/material.h>
#include <core/color.h>

namespace rt {

LightHit AmbientLight::getLightHit(const Point& p) const {
    LightHit hit;

    hit.distance = epsilon;
    hit.direction = (source->sample().point - p).normalize();
    hit.normal = source->sample().normal;
    if (dot(hit.direction, hit.normal) < 0) {hit.normal = -hit.normal;}
    
    return hit;
}

RGBColor AmbientLight::getIntensity(const LightHit& irr) const {
    RGBColor rad_clr = source->material->getEmission(
        Point::rep(0.0f),
        Vector::rep(0.0f),
        Vector::rep(0.0f)
    );
    return rad_clr;
}

}