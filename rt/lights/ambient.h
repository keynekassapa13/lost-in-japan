#ifndef CG1RAYTRACER_LIGHTS_AMBIENTLIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_AMBIENTLIGHT_HEADER

#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <core/color.h>

namespace rt {

class Solid;

class AmbientLight : public Light {
public:
    AmbientLight() {}
    AmbientLight(Solid* source) {this->source = source;};
    virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
    Solid* source;

};

}

#endif
