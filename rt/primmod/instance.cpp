#include <rt/primmod/instance.h>

namespace rt {

    Instance::Instance(Primitive* content)
    {
        this->p = content;
        this->tr = Matrix::identity();
    }

    Primitive* Instance::content() {
        return p;
    }

    void Instance::reset() {
        tr = Matrix::identity();
    }

    void Instance::translate(const Vector& t) {
        tr[0][3] += t.x;
        tr[1][3] += t.y;
        tr[2][3] += t.z;
    }

    void Instance::rotate(const Vector& axis, float angle) {
        Vector a = axis.normalize();
        float s = sin(angle);
        float c = cos(angle);
        // Ref: Physically Based Rendering Book
        Matrix rotation = Matrix(
            Float4(
                a.x * a.x + (1 - a.x * a.x) * c,
                a.x * a.y * (1 - c) - a.z * s,
                a.x * a.z * (1 - c) + a.y * s,
                0
            ), Float4(
                a.x * a.y * (1 - c) + a.z * s,
                a.y * a.y + (1 - a.y * a.y) * c,
                a.y * a.z * (1 - c) - a.x * s,
                0
            ), Float4(
                a.x * a.z * (1 - c) - a.y * s,
                a.y * a.z * (1 - c) + a.x * s,
                a.z * a.z + (1 - a.z * a.z) * c,
                0
            ), Float4(0, 0, 0, 1)
        );
        tr = product(tr, rotation);
    }

    void Instance::scale(float f) {
        Matrix scale = Matrix(
            Float4(f, 0, 0, 0),
            Float4(0, f, 0, 0),
            Float4(0, 0, f, 0),
            Float4(0, 0, 0, 1)
        );
        tr = product(tr, scale);
    }

    void Instance::scale(const Vector& s) {
        Matrix scale = Matrix(
            Float4(s.x, 0, 0, 0),
            Float4(0, s.y, 0, 0),
            Float4(0, 0, s.z, 0),
            Float4(0, 0, 0, 1)
        );
        tr = product(tr, scale);
    }

    void Instance::setMaterial(Material* m) {
        p->setMaterial(m);
    }

    void Instance::setCoordMapper(CoordMapper* cm) {
        p->setCoordMapper(cm);
    }

    float Instance::getArea() const {
        return 0;
    }

    Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
        Ray tray = ray;
        Matrix trinv = tr.invert();
        tray.o = trinv * ray.o;
        tray.d = (trinv * ray.d).normalize();

        float trayd = (trinv * ray.getPoint(previousBestDistance) - tray.o).length();

        Intersection hit_intersection = p->intersect(tray, trayd);
        if (hit_intersection) {
            float d = ((tr * hit_intersection.hitPoint()) - ray.o).length();
            Vector n = (trinv.transpose() * hit_intersection.normal()).normalize();
            n = dot(n, ray.d.normalize()) > 0 ? -n : n;
            return Intersection(d, ray, hit_intersection.solid, n, tr * hit_intersection.hitPoint());
        }
        return Intersection::failure();
    }

    BBox Instance::getBounds() const {
        BBox pbox = p->getBounds();
        return BBox(tr * pbox.min, tr * pbox.max);
    }

}
