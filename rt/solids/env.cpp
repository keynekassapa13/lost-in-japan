#include <rt/solids/env.h>

namespace rt {

	Env::Env(CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material)  {
	}

	BBox Env::getBounds() const {
		return BBox::full();
	}

	Intersection Env::intersect(const Ray& ray, float previousBestDistance) const {
		// Introduce a new special Solid that always intersects with any ray at infinity
		// UV point will be ignored
		return Intersection(FLT_MAX, ray, this, ray.d, Point::rep(0.0f));
	}

	Solid::Sample Env::sample() const {
		/* TODO */ NOT_IMPLEMENTED;
	}

	float Env::getArea() const {
		return FLT_MAX;
	}

}
