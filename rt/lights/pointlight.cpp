#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

    PointLight::PointLight(const Point& position, const RGBColor& intensity)
    {
        this->o = position;
        this->i = intensity;
    }

    LightHit PointLight::getLightHit(const Point& p) const {
        LightHit hit;

        // Vector of (light position - point)
        hit.distance = (o - p).length();
        hit.direction = (o - p).normalize();
        return hit;
    }

    RGBColor PointLight::getIntensity(const LightHit& irr) const {
        return (i / (irr.distance * irr.distance));
    }

}
