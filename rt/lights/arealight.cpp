#include <rt/lights/arealight.h>
#include <rt/materials/material.h>
#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    LightHit hit;

    hit.direction = (source->sample().point - p).normalize();
    hit.distance = (source->sample().point - p).length();
    hit.normal = source->sample().normal;
    if (dot(hit.direction, hit.normal) < 0) {hit.normal = -hit.normal;}

    return hit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    RGBColor rad_clr = source->material->getEmission(
        Point::rep(0.0f),
        Vector::rep(0.0f),
        Vector::rep(0.0f)
    );

    return source->getArea() * rad_clr * fabs(dot(source->sample().normal, irr.direction)) / (irr.distance * irr.distance);
}

AreaLight::AreaLight(Solid* source)
{
    this->source = source;
}

}