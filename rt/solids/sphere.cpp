#include <rt/solids/sphere.h>

namespace rt {

	Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material) {
		this->center = center;
		this->radius = radius;
	}

	BBox Sphere::getBounds() const {
		return BBox(center - Vector(radius, radius, radius), center + Vector(radius, radius, radius));
	}

	Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
		/*
		Ref:
		https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2012/lecture-notes/MIT6_837F12_Lec11.pdf
		https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

		P . P - r^2 = 0
		(r.o + t . d)(r.o + t . r.d) - r^2 = 0
		(r.o . r.o) + (2 . r.o . t . r.d) + (t . t . r.d . r.d) = r^2

		a t^2 + b t + c = 0
		a = 1 = r.d . r.d
		b = 2 . r.o . r.d
		c = r.o . r.o - r^2

		d = (b^2 - 4 . a . c ) ^ -1/2
		t = (b +- d)/2a
		*/

		if (radius == 0) { return Intersection::failure(); };

		float a = dot(ray.d, ray.d);
		float b = 2 * dot(ray.d, (ray.o - center));
		float c = dot(ray.o - center, ray.o - center) - (radius * radius);

		float d = (b * b) - (4 * a * c);
		if (d < 0) { return Intersection::failure(); };

		float t1 = (-b + sqrtf(d)) / (2 * a);
		float t2 = (-b - sqrtf(d)) / (2 * a);

		float t = min(t1, t2) > 0 ? min(t1, t2) : FLT_MAX;
		if (t > previousBestDistance) { return Intersection::failure(); };
		Vector local = (ray.o + ray.d * t) - center;
		Vector n = (ray.getPoint(t) - center).normalize();

		return Intersection(t, ray, this, n, ray.getPoint(t));
	}

	Solid::Sample Sphere::sample() const {
		NOT_IMPLEMENTED;
	}

	float Sphere::getArea() const {
		return 4 * pi * radius * radius;
	}

}
