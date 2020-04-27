#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

  RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
	  Intersection hit_intersection = this->world->scene->intersect(ray);
	  float clr = 0;
	  if (hit_intersection) {
		  clr = (dot(hit_intersection.normal(), -ray.d));
		  clr = clr < 0 ? 0 : clr;
	  }
	  return RGBColor(clr, clr, clr);
  }

}
