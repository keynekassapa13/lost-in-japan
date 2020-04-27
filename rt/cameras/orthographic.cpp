#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

	OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
	{
		this->center = center;
		this->forward = forward;
		this->up = up;

		/*
		X: forward (direction), Y: up, Z: right/left.
		*/
		this->sx = (cross(this->forward, this->up).normalize() * scaleX) / 2.0f;
		this->sy = (cross(this->sx, this->forward).normalize() * scaleY) / 2.0f;

	}

	Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
		return Ray(
			this->center + this->sx * x + this->sy * y,
			this->forward.normalize()
		);
	}

}
