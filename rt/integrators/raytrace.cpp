#include <rt/integrators/raytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <core/float4.h>
#include <rt/textures/texture.h>
#include <rt/coordmappers/world.h>

namespace rt {

  RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    Intersection hit_intersection = this->world->scene->intersect(ray);
    RGBColor clr = RGBColor(0, 0, 0);

    if (hit_intersection) {

      Vector hn = hit_intersection.normal();
      Point hp = hit_intersection.hitPoint();
      Vector out_dir = ray.d.normalize();
      if (dot(hn, ray.d.normalize()) > 0) {hn = -hn;}

      // Texture
      auto tex = hit_intersection.solid->texMapper;
      if (tex == nullptr) {tex = new WorldMapper(Float4::rep(1));}
      Point tex_p = tex->getCoords(hit_intersection);

      clr = clr + hit_intersection.solid->material->getEmission(tex_p, hn, -out_dir);;

      for (auto light: this->world->light) {
        LightHit lh = light->getLightHit(hp);
        Intersection sh_intersect = this->world->scene->intersect(
          Ray(hp + epsilon * lh.direction, lh.direction),
          lh.distance);

        // If ray hit shadow
        if (dot(hn, lh.direction) < 0 || sh_intersect) {continue;}

        RGBColor reflected_clr = hit_intersection.solid->material->getReflectance(
        tex_p, hn, -out_dir, lh.direction);
        clr = clr + (reflected_clr * light->getIntensity(lh));
      }

    }
    return clr.clamp();
  }

}
