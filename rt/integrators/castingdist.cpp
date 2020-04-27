#include <rt/integrators/castingdist.h>
#include <rt/intersection.h>

namespace rt {

	RayCastingDistIntegrator::RayCastingDistIntegrator(
		World* world, const RGBColor& nearColor, 
		float nearDist, const RGBColor& farColor,
		float farDist)
		: Integrator(world)
	{
		this->near_clr = nearColor;
		this->near_dst = nearDist;
		this->far_clr = farColor;
		this->far_dst = farDist;
	}

	RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
		Intersection hit_intersection = world->scene->intersect(ray);
		RGBColor clr = RGBColor(0, 0, 0);
		if (hit_intersection) {

			float interpolate = (hit_intersection.distance - near_dst) 
				/ (far_dst - near_dst);

			interpolate = interpolate < 0 ? 0 : interpolate;
			interpolate = interpolate > 1 ? 1 : interpolate;
			float cos = dot(hit_intersection.normal(), -ray.d);
			cos = cos < 0 ? 0 : cos;
			clr = (
					(interpolate * far_clr) + ((1 - interpolate) * near_clr)
				) * cos;
		}
		return clr;
	}

}
