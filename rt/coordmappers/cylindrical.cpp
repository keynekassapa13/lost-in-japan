#include <rt/coordmappers/cylindrical.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
{
    this->o = origin;

    // The direction along which the y coordinate of the texture increases. 
    // The magnitude of the vector defines the scaling along the y direction.
    this->la = longitudinalAxis;

    // a direction intersecting a cylinder at some point
    // The magnitude of the vector defines the scaling along the x coordinate.
    this->pa = polarAxis;
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    
	Vector p = hit.local() - o;
    Vector la_n = la.normalize();
    Vector pa_n = pa.normalize();

    Vector z = cross(la_n, pa_n).normalize() * pa.length();

	float u = dot(p, pa) / pa.lensqr();
	float v = dot(p, z) / z.lensqr();

	float theta = acosf(dot(Vector(u, 0.0f, v).normalize(), pa_n));
	float h = dot(p, la) / (la.length() * pa.length());

	return Point(
        theta / (2 * pi * pa.length()), 
        h, 
        0.f);
}
}