#include <rt/groups/simplegroup.h>

namespace rt {

	BBox SimpleGroup::getBounds() const {
		return b;
	}

	Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
	
		Intersection hit_intersection;
		Intersection nearest = Intersection::failure();
		for (auto& p : primitives) {
			hit_intersection = p->intersect(ray, previousBestDistance);
			if (hit_intersection.distance > FLT_MAX || hit_intersection.distance < 0) { return nearest; };
			if (hit_intersection > 0 && (hit_intersection.distance < previousBestDistance)) {
				nearest = hit_intersection;
				previousBestDistance = hit_intersection.distance;
			}
		}
		return nearest;
	}

	void SimpleGroup::rebuildIndex() {
		//do nothing
	}

	void SimpleGroup::add(Primitive* p) {
		primitives.push_back(p);
		b.extend(p->getBounds());
	}

	void SimpleGroup::setMaterial(Material* m) {
		for (auto& p : primitives) {
			p->setMaterial(m);
		}
	}

	void SimpleGroup::setCoordMapper(CoordMapper* cm) {
		for (auto& p : primitives) {
			p->setCoordMapper(cm);
		}
	}

	float SimpleGroup::getArea() const {
		return 0;
	}

}
