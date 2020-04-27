#ifndef CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER
#define CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER

#include <rt/lights/light.h>
#include <core/color.h>

namespace rt {

class DirectionalLight : public Light {
public:
	DirectionalLight() {}
	DirectionalLight(const Vector& direction, const RGBColor& color);
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
private:
	Vector d;
	RGBColor clr;
};

}

#endif
