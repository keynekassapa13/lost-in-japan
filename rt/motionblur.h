#ifndef CG1RAYTRACER_GROUPS_MOTION_BLUR_HEADER
#define CG1RAYTRACER_GROUPS_MOTION_BLUR_HEADER

#include <core/random.h>
#include <core/matrix.h>
#include <core/interpolate.h>
#include <rt/groups/group.h>
#include <rt/primmod/instance.h>

namespace rt {

class MotionBlur : public Group {
public:
	Primitive* p;
	Matrix tr = Matrix::identity();

	MotionBlur() {}
	void translate(const Vector& t) {
        Matrix trans = Matrix::identity();
		trans[0][3] = t.x;
		trans[1][3] = t.y;
		trans[2][3] = t.z;
		tr = product(trans, tr);
    };

    virtual BBox getBounds() const {
        BBox pbox = p->getBounds();
		pbox.extend(tr * pbox.min);
		pbox.extend(tr * pbox.max);
		return pbox;
    };

    virtual Intersection intersect(const Ray& ray, float previousBestDistance) const {
        Instance p_inst = Instance(p);
		p_inst.tr = product(p_inst.tr, lerp(Matrix::identity(), tr, random()));
		return p_inst.intersect(ray, previousBestDistance);
    };

    virtual void rebuildIndex() {};
    virtual void add(Primitive* primitive) {p = primitive;};
    virtual void setMaterial(Material* m) {p->setMaterial(m);};
    virtual void setCoordMapper(CoordMapper* cm) {p->setCoordMapper(cm);};
    virtual float getArea() const {return p->getArea();};
};

}

#endif