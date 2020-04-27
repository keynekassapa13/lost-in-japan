#include <rt/bbox.h>
#include <rt/primitive.h>
#include <algorithm>

namespace rt {

	BBox BBox::empty() {
		return BBox();
	}

	BBox BBox::full() {
		BBox box;
		box.min = Point(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		box.max = Point(FLT_MAX, FLT_MAX, FLT_MAX);
		box._flag = true;
		return box;
	}

	Point BBox::centroid() {
		return Point(
			(max.x + min.x) / 2,
			(max.y + min.y) / 2,
			(max.z + min.z) / 2
		);
	}

	void BBox::extend(const Point& point) {
		if (_flag) {
			min = rt::min(min, point);
			max = rt::max(max, point);
		} else {
			min = point; max = point;
			_flag = true;
		}
	}

	void BBox::extend(const BBox& bbox) {
		if (_flag) {
			min = rt::min(min, bbox.min);
			max = rt::max(max, bbox.max);
		} else {
			min = bbox.min;
			max = bbox.max;
			_flag = true;
		}
	}

	std::pair<float, float> BBox::intersect(const Ray& ray) const {
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

		if (t_min > t_max) { return std::make_pair(FLT_MAX, -FLT_MAX); };
		return std::make_pair(t_min, t_max);
	}

	bool BBox::isUnbound() {
		Point min_test = rt::min(min, max);
		Point max_test = rt::max(min, max);
		return (
			min_test.x == -FLT_MAX || min_test.y == -FLT_MAX || min_test.z == -FLT_MAX ||
			max_test.x == FLT_MAX || max_test.y == FLT_MAX || max_test.z == FLT_MAX);
	}

}
