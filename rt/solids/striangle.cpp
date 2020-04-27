#include <rt/solids/striangle.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/solid.h>
#include <core/interpolate.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    this->texMapper = texMapper;
    this->material = material;

    this->v1 = vertices[0];
    this->v2 = vertices[1];
    this->v3 = vertices[2];

    this->n1 = normals[0];
    this->n2 = normals[1];
    this->n3 = normals[2];
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    this->texMapper = texMapper;
    this->material = material;
    
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    Vector e1 = (v2 - v1);
    Vector e2 = (v3 - v1);
    Vector s = ray.o - v1;

    float denom = dot(cross(ray.d, e2), e1);
    if (denom == 0) {return Intersection::failure();}

    float t = dot(cross(s, e1), e2) / denom;
    if (t < 0 || t > previousBestDistance) { return Intersection::failure(); };
    float b1 = dot(cross(ray.d, e2), s) / denom;
    float b2 = dot(cross(s, e1), ray.d) / denom;

    if (b1 < 0 || b2 < 0 || b1 + b2 >= 1) {return Intersection::failure(); };

    float b3 = 1 - b1 - b2;
    Vector n = n1 * b3 + n2 * b1 + n3 * b2;
    return Intersection(t, ray, this, n, Point(b1, b2, b3));
}

}