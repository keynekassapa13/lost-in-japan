#include <rt/lights/projective.h>

#include <core/vector.h>
#include <core/julia.h>
#include <rt/ray.h>

float a2computeWeight(float fx, float fy, const rt::Point& c, float div);
rt::RGBColor a2computeColor(const rt::Ray& r);

float a1computeWeight(float fx, float fy, const rt::Point& c, float div);
// rt::RGBColor a1computeColor(uint x, uint y, uint width, uint height);

namespace rt {

    ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity)
    {
        this->o = position;
        this->i = intensity;
    }

    LightHit ProjectiveLight::getLightHit(const Point& p) const {
        LightHit hit;

        // Vector of (light position - point)
        hit.distance = (o - p).length();
        hit.direction = (o - p).normalize();
        return hit;
    }

    RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {

        // RGBColor clr = i * a2computeColor(Ray(o, irr.direction));
        // return clr / (irr.distance * irr.distance);

        float   fx = irr.direction.normalize().x, 
                fy = irr.direction.normalize().y;

        RGBColor color = RGBColor::rep(0.0f);
        color = color + a1computeWeight(fx, fy, Point(-0.8f, 0.156f, 0.0f), 64.0f) * i;
        color = color + a1computeWeight(fx, fy, Point(-0.6f, 0.2f, 0.0f), 64.0f)   * 0.2f * i;
        color = color + a1computeWeight(fy, fx, Point(0.285f, 0.0f, 0.0f), 64.0f)  * i;
    
        return color.clamp() / (irr.distance * irr.distance);

        // return (a1computeColor(fx * 400, fy * 400, 400, 400)) * i / (irr.distance * irr.distance);
    }

}
