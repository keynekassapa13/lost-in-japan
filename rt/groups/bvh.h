#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>

namespace rt {

class BVHNode {
public:
	BVHNode() {}

	BBox box;
	BVHNode* left = nullptr;
	BVHNode* right = nullptr;
	typedef std::vector<Primitive *> Primitives;
	Primitives p;
	float area;

	void add(Primitive* prim) {
		p.push_back(prim);
	}

	std::pair<float, BBox> getBounds() const {
		BBox b = BBox::empty();
		float a = 0;
		for (uint i = 0; i < p.size(); i++) {
			b.extend(p[i]->getBounds());
			a = a + p[i]->getArea();
		};
		return std::make_pair(a, b);
	}
};

class BVH : public Group {
public:
	BVHNode* root = new BVHNode();
    BVH();
	virtual ~BVH();
	// bool _sah = false;
	bool _sah = true;
	int _bin = 16;
	float bins[16], bins_n[16];
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual BBox getBounds() const;
	virtual float findMiddleSplit(int bool_axis, BVHNode* parent);
	virtual float findSAHSplit(int bool_axis, float len_axis, BVHNode* parent);
    virtual void rebuildIndex();
	virtual void buildRecursive(BVHNode* parent);
    virtual void add(Primitive* prim);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual float getArea() const;
};

}

#endif