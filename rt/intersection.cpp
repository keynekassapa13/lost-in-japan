#include <rt/intersection.h>

namespace rt {

	Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
	{
		this->ray = ray;
		this->solid = solid;
		this->distance = distance;
		this->normal_vector = normal.normalize();
		this->local_point = local;
	}

	Intersection::operator bool() {
		return (distance > 0 && distance < FLT_MAX);
	}

	Intersection Intersection::failure() {
		Intersection sample_ = Intersection();
		sample_.distance = 0;
		return sample_;
	}

	Point Intersection::hitPoint() const {
		return ray.o + (distance * ray.d);
	}

	Vector Intersection::normal() const {
		return normal_vector;
	}

	Point Intersection::local() const {
		return local_point;
	}

}
