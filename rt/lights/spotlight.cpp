#include <rt/lights/spotlight.h>
#include <cmath>

namespace rt {

    SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)
    {
        this->o = position;
        this->d = direction;
        this->angle = angle;
        this->pwr = power;
        this->i = intensity;
    }

    LightHit SpotLight::getLightHit(const Point & p) const
    {
        LightHit hit;

        // Vector of (light position - point)
        hit.distance = (o - p).length();
        hit.direction = (o - p).normalize();
        return hit;
    }

    RGBColor SpotLight::getIntensity(const LightHit& irr) const {
        float dir_angle = acosf(dot(irr.direction.normalize(), -d.normalize()));
        if (dir_angle < angle) {
            float att = 1 / (irr.distance * irr.distance);
            return i * powf(cos(dir_angle), pwr) * att;
        }
        return RGBColor(0, 0, 0);
    }

}
