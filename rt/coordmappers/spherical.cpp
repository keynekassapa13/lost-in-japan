#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->o = origin;

    // zenith — the direction towards the north pole of the sphere.
    // The magnitude defines the scaling along the y texture direction. 
    this->zen = zenith;

    // a direction defining the prime meridian
    // The magnitude defines the scaling along the x texture direction
    this->azimuth = azimuthRef;

}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    
    // Similar to Cylinder
    Vector p = hit.local() - o;
    Vector zen_n = zen.normalize();
    Vector azimuth_n = azimuth.normalize();

    Vector z = cross(zen_n, azimuth_n).normalize() * azimuth.length();

    float theta = acosf(dot(p.normalize(), zen_n));

    float u = dot(p, azimuth) / azimuth.lensqr();
    float v = dot(p, z) / z.lensqr();

    float phi = acosf(dot(Vector(u, 0.0f, v).normalize(), azimuth_n));

    return Point(
        phi / (2 * pi * azimuth.length()),
        theta / (pi * azimuth.length()),
        0.0f
    );
}

}