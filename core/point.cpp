#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

	Point::Point(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point::Point(const Float4& f4)
	{
		float w = f4.w;
		if (w == 0) {w = 1;}
		this->x = f4.x / w;
		this->y = f4.y / w;
		this->z = f4.z / w;
	}

	Vector Point::operator - (const Point& b) const {
		return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	bool Point::operator == (const Point& b) const {
		return this->x == b.x && this->y == b.y && this->z == b.z;
	}

	bool Point::operator != (const Point& b) const {
		return this->x != b.x || this->y != b.y || this->z != b.z;
	}

	Point operator * (float scalar, const Point& b) {
		return Point(b.x * scalar, b.y * scalar, b.z * scalar);
	}

	Point operator * (const Point& a, float scalar) {
		return scalar * a;
	}

	Point min(const Point& a, const Point& b) {
		float min_x = a.x < b.x ? a.x : b.x;
		float min_y = a.y < b.y ? a.y : b.y;
		float min_z = a.z < b.z ? a.z : b.z;
		return Point(min_x, min_y, min_z);
	}

	Point max(const Point& a, const Point& b) {
		float max_x = a.x > b.x ? a.x : b.x;
		float max_y = a.y > b.y ? a.y : b.y;
		float max_z = a.z > b.z ? a.z : b.z;
		return Point(max_x, max_y, max_z);
	}

}
