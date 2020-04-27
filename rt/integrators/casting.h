#ifndef CG1RAYTRACER_INTEGRATORS_CASTING_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class RayCastingIntegrator : public Integrator {
public:
    RayCastingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif