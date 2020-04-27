#include <rt/solids/triangle.h>
#include <core/random.h>

namespace rt {

	Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material) {
		this->v1 = vertices[0];
		this->v2 = vertices[1];
		this->v3 = vertices[2];
	}

	Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	BBox Triangle::getBounds() const {
		Point min_point = rt::min(rt::min(v1, v2), v3);
		Point max_point = rt::max(rt::max(v1, v2), v3);
		return BBox(min_point, max_point);
	}

	Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
		/*
		Ref:
		https://cg.informatik.uni-freiburg.de/course_notes/graphics_01_raycasting.pdf
		*/
		
		Vector vec1 = Vector(v1.x, v1.y, v1.z);
		Vector vec2 = Vector(v2.x, v2.y, v2.z);
		Vector vec3 = Vector(v3.x, v3.y, v3.z);

		Vector e1 = v2 - v1;
		Vector e2 = v3 - v1;
		Vector n = cross(e1, e2).normalize();
		Vector s = ray.o - v1;
		float denom = dot(cross(ray.d, e2), e1);
		if (denom == 0) {return Intersection::failure();}

		float t = dot(cross(s, e1), e2) / denom;
		if (t < 0 || t > previousBestDistance) { return Intersection::failure(); };
		float b1 = dot(cross(ray.d, e2), s) / denom;
		float b2 = dot(cross(s, e1), ray.d) / denom;

		if (b1 < 0 || b2 < 0 || b1 + b2 >= 1) {return Intersection::failure(); };

		Vector p = (1 - b1 - b2) * vec1 + b1 * vec2 + b2 * vec3;
		return Intersection(t, ray, this, n, Point((1-b1-b2), b1, b2));
	}

	Solid::Sample Triangle::sample() const {
		float r1 = random();
		float r2 = random();

		return {Point(
			r1 * v1.x + r2 * v2.x * (1 - r1 - r2) * v3.x,
			r1 * v1.y + r2 * v2.y * (1 - r1 - r2) * v3.y,
			r1 * v1.z + r2 * v2.z * (1 - r1 - r2) * v3.z
		), cross(v2 - v1, v3 - v1).normalize()};
	}

	float Triangle::getArea() const {
		Vector e1 = v2 - v1;
		Vector e2 = v3 - v1;
		return cross(e1, e2).length() / 2;
	}

}