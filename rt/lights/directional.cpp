#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

    DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
    {
        this->d = direction;
        this->clr = color;
    }

    LightHit DirectionalLight::getLightHit(const Point& p) const {
        LightHit hit;
        
        // Infinite distance, Light source are parallel
        hit.distance = FLT_MAX;
        hit.direction = -d;
        hit.direction = hit.direction.normalize();
        return hit;
    }

    RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
        return clr;
    }

}
