#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material)
: Solid(texMapper, material) {
	this->center = center;
	this->normal = normal;
	this->radius = radius;
}

BBox Disc::getBounds() const {
	return BBox(center - Vector(radius, radius, radius), center + Vector(radius, radius, radius));
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
	/*
	Ref:
	Physically Based Rendering, 3.4 Disk
	https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023700000000000000

	N . ( P - Q ) = 0
	N . ( o + td - Q ) = 0
	t = N . ( Q - o) / N . d
	*/

	float n = dot(ray.d, normal);
	float t = dot((center - ray.o), normal) / n;

	if (t > 0 && t < previousBestDistance && (ray.getPoint(t) - center).length() <= radius) {
		return Intersection(t, ray, this, normal.normalize(), ray.getPoint(t));
	}
	
	return Intersection::failure();
}

Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
	return pi * radius * radius;
}

}
