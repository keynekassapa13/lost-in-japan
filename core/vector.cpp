#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

	Vector::Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector::Vector(const Float4& f4)
	{
		float w = f4.w;
		if (w == 0) {w = 1;}
		this->x = f4.x / w;
		this->y = f4.y / w;
		this->z = f4.z / w;
	}

	Vector Vector::operator + (const Vector& b) const {
		return Vector(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	Vector Vector::operator - (const Vector& b) const {
		return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	Vector Vector::operator - () const {
		return Vector(-this->x, -this->y, -this->z);
	}

	Vector Vector::normalize() const {
		float l = this->length();
		return Vector(this->x / l, this->y / l, this->z / l);
	}

	Vector operator * (float scalar, const Vector& b) {
		return Vector(b.x * scalar, b.y * scalar, b.z * scalar);
	}

	Vector operator * (const Vector& a, float scalar) {
		return scalar * a;
	}

	Vector operator / (const Vector& a, float scalar) {
		return (1 / scalar) * a;
	}

	Vector cross(const Vector& a, const Vector& b) {
		float i = (a.y * b.z) - (a.z * b.y);
		float j = (a.z * b.x) - (a.x * b.z);
		float k = (a.x * b.y) - (a.y * b.x);
		return Vector(i, j, k);
	}

	float dot(const Vector& a, const Vector& b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	float Vector::lensqr() const {
		/* return the square of the length of the vector */
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
	}

	float Vector::length() const {
		/* return the length of Euclidean Space */
		return sqrtf(this->lensqr());
	}


	bool Vector::operator == (const Vector& b) const {
		return this->x == b.x && this->y == b.y && this->z == b.z;
	}

	bool Vector::operator != (const Vector& b) const {
		return this->x != b.x || this->y != b.y || this->z != b.z;
	}

	Vector min(const Vector& a, const Vector& b) {
		float min_x = a.x < b.x ? a.x : b.x;
		float min_y = a.y < b.y ? a.y : b.y;
		float min_z = a.z < b.z ? a.z : b.z;
		return Vector(min_x, min_y, min_z);
	}

	Vector max(const Vector& a, const Vector& b) {
		float max_x = a.x > b.x ? a.x : b.x;
		float max_y = a.y > b.y ? a.y : b.y;
		float max_z = a.z > b.z ? a.z : b.z;
		return Vector(max_x, max_y, max_z);
	}

	Point operator + (const Point& a, const Vector& b) {
	   return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Point operator + (const Vector& a, const Point& b) {
		return b + a;
	}

	Point operator - (const Point& a, const Vector& b) {
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Point operator * (const Float4& scale, const Point& p) {
		/* TODO */ NOT_IMPLEMENTED;
	}

}
