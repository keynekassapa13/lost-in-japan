#ifndef CG1RAYTRACER_WORLD_HEADER
#define CG1RAYTRACER_WORLD_HEADER

#include <rt/primitive.h>
#include <vector>
#include <rt/volume.h>

namespace rt {

class Light;

class World {
public:
    World(Volume* fog = nullptr) {this->fog = fog;}
    Primitive* scene;
	typedef std::vector<Light*> LightVector;
    LightVector light;
    Volume* fog;
};

}

#endif