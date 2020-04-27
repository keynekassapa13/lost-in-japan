#include <rt/solids/aabox.h>

namespace rt {

	AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
	: Solid(texMapper, material) {
		this->c1 = corner1;
		this->c2 = corner2;

		min = rt::min(corner1, corner2);
		max = rt::max(corner1, corner2);
	}

	BBox AABox::getBounds() const {
		return BBox(min, max);
	}

	Solid::Sample AABox::sample() const {
		NOT_IMPLEMENTED;
	}

	float AABox::getArea() const {
		// Each Side Plane 
		float xy = (max.x - min.x) * (max.y - min.y);
		float yz = (max.y - min.y) * (max.z - min.z);
		float xz = (max.x - min.x) * (max.z - min.z);

		return 2 * (xy + yz + xz);
	}

	Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
		/*
		Ref:
		Physically Based Rendering books.
		3.1.2 Ray Bounds Intersecting
		*/

		float ray_dir_x = 1 / ray.d.x;
		float ray_dir_y = 1 / ray.d.y;
		float ray_dir_z = 1 / ray.d.z;

		// For X
		float tx_1 = (min.x - ray.o.x) * ray_dir_x;
		float tx_2 = (max.x - ray.o.x) * ray_dir_x;

		// For Y
		float ty_3 = (min.y - ray.o.y) * ray_dir_y;
		float ty_4 = (max.y - ray.o.y) * ray_dir_y;

		// For Z
		float tz_5 = (min.z - ray.o.z) * ray_dir_z;
		float tz_6 = (max.z - ray.o.z) * ray_dir_z;

		float t_min = std::max(
			std::max(std::min(tx_1, tx_2), std::min(ty_3, ty_4)), 
			std::min(tz_5, tz_6));
		float t_max = std::min(
			std::min(std::max(tx_1, tx_2), std::max(ty_3, ty_4)), 
			std::max(tz_5, tz_6));

		if (t_max < 0 || t_min > t_max || t_max > FLT_MAX) { return Intersection::failure(); };
		if (t_min > previousBestDistance || t_min < 0) { return Intersection::failure(); };

		Vector n;
		n = t_min == tx_1 ? Vector(-1, 0, 0) : n;
		n = t_min == tx_2 ? Vector(1, 0, 0) : n;
		n = t_min == ty_3 ? Vector(0, -1, 0) : n;
		n = t_min == ty_4 ? Vector(0, 1, 0) : n;
		n = t_min == tz_5 ? Vector(0, 0, -1) : n;
		n = t_min == tz_6 ? Vector(0, 0, 1) : n;

		return Intersection(t_min, ray, this, n, ray.getPoint(t_min));
	}

}
