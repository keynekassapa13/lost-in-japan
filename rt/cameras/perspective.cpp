#include <rt/cameras/perspective.h>
#include <cmath>

namespace rt {

	PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
	{
		this->center = center;
		this->forward = forward;
		this->up = up;

		/*
		Perspective Transformation
		X' = normalize(VUP x VPN), Y'= Z' x X'
		VUP = up, VPN = forward = Z'

		Turn to magnitude
		X' = X' * tan(theta/2)
		Y' = Y' * tan(theta/2)
		*/

		this->cam_x = cross(this->forward, this->up).normalize() 
			* tan(horizontalOpeningAngle / 2.0f);
		this->cam_y = cross(this->cam_x, this->forward).normalize() 
			* tan(verticalOpeningAngle / 2.0f);
	}

	Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
		Vector direction = this->forward.normalize() + this->cam_x * x + this->cam_y * y;
		return Ray(this->center, direction.normalize());
	}

}
