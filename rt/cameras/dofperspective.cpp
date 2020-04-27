#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <core/random.h>
#include <math.h>
#include <core/scalar.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    this->center = center;
    this->forward = forward;
    this->up = up;

    this->right = cross(forward, up).normalize();
    this->up = cross(right, forward).normalize();

    this->cam_x = right * tan(horizontalOpeningAngle / 2.0f);
    this->cam_y = up * tan(verticalOpeningAngle / 2.0f);

    this->fd = focalDistance;
    this->ar = apertureRadius;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    Point fp = center + (forward + x * cam_x + y * cam_y).normalize() * fd;
	float random_ar = random(0.0f, ar);
	float angle = 2 * pi * random();
	x = random_ar * cos(angle);
	y = random_ar * sin(angle);

	Point o = center + x * right + y * up;
	Vector d = (fp - o).normalize();

	return Ray(o, d);
}

}