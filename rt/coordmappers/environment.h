#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER

#include <rt/coordmappers/coordmapper.h>

namespace rt {

class Intersection;
class Vector;

class EnvironmentMapper : public CoordMapper{
public:
    EnvironmentMapper();
    virtual Point getCoords(const Intersection& hit) const;

};

}

#endif