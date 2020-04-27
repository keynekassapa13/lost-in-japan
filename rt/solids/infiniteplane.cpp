#include <rt/solids/infiniteplane.h>

namespace rt {

	InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material)  {
		this->normal = normal;
		this->origin = origin;
	}

	BBox InfinitePlane::getBounds() const {
		return BBox::full();
	}

	Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
		/*
		Ref:
		https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2012/lecture-notes/MIT6_837F12_Lec11.pdf

		Ax + By + Cz + D = 0
		n . P + D = 0
		n . (r.o + t . r.d) + D = 0
		t = ( - D + n . r.o ) / n . r.d

		D = n . o -- distance from origin

		||o - r.o|| ||n|| cos
		||n|| ||r.d|| cos
		*/
		
		float t = dot(this->origin - ray.o, this->normal)
			/ dot(this->normal, ray.d);

		if (t < 0 || t > previousBestDistance) {
			return Intersection::failure();
		}
		return Intersection(t, ray, this, this->normal, ray.getPoint(t));
	}

	Solid::Sample InfinitePlane::sample() const {
		/* TODO */ NOT_IMPLEMENTED;
	}

	float InfinitePlane::getArea() const {
		return FLT_MAX;
	}

}
