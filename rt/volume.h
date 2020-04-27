#ifndef CG1RAYTRACER_VOLUME_HEADER
#define CG1RAYTRACER_VOLUME_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <core/color.h>
#include <rt/bbox.h>
#include <rt/intersection.h>
#include <rt/textures/texture.h>

namespace rt {

class Volume {
public:
    virtual RGBColor getColor(const Point& p) = 0;
    virtual float getTrans(float dist) = 0;
};

// Assume that the fog is uniform, but is lit by actual light sources in the world. You will need to
// perform ray marching along the primary rays, but attenuation of shadow rays can still be done
// analytically.

// Assume that the fog is uniform, and lit by an ambient light source. You need to add the attenuation
// factor for your primary and shadow rays. The primary rays (and only those) should additionally
// account for the ambient light reflected by the fog.

class UniformFog : public Volume {
public:
  UniformFog(RGBColor clr, float density) {this->clr = clr; this->density = density;};
  RGBColor getColor(const Point& p) {return clr;};
  float    getTrans(float dist) {return std::exp(-dist * density);};

private:
  float    density;
  RGBColor clr;
};

// Assume the fog is heterogenous (e.g. defined by some 3D perlin noise texture). Perform the ray
// marching along the primary and shadow rays.

class HeteroFog : public Volume {
public:
  HeteroFog(Texture* texture, float density) {this->texture = texture; this->density = density;};

  RGBColor getColor(const Point& p) {return texture->getColor(p);};
  float getTrans(float dist) {return std::exp(-dist * density);};

private:
  Texture* texture;
  float density;
};

}

#endif