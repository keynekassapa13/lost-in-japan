#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

    Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
        this->r[0] = r1;
        this->r[1] = r2;
        this->r[2] = r3;
        this->r[3] = r4;
    }

    Float4& Matrix::operator[](int idx) {
        return r[idx];
    }

    Float4 Matrix::operator[](int idx) const {
        return r[idx];
    }

    Matrix Matrix::operator+(const Matrix& b) const {
        return Matrix(
            r[0] + b[0],
            r[1] + b[1],
            r[2] + b[2],
            r[3] + b[3]
        );
    }

    Matrix Matrix::operator-(const Matrix& b) const {
        return Matrix(
            r[0] - b[0],
            r[1] - b[1],
            r[2] - b[2],
            r[3] - b[3]
        );
    }

    Matrix Matrix::transpose() const {
        return Matrix(
            Float4(r[0][0], r[1][0], r[2][0], r[3][0]),
            Float4(r[0][1], r[1][1], r[2][1], r[3][1]),
            Float4(r[0][2], r[1][2], r[2][2], r[3][2]),
            Float4(r[0][3], r[1][3], r[2][3], r[3][3])
        );
    }

    Matrix Matrix::invert() const {
        Matrix res = Matrix::zero();
        float d = this->det();
        if (d == 0) {return res;}

        res[0][0] = (r[1][1] * r[2][2] * r[3][3]) + (r[2][1] * r[1][3] * r[3][2]) + (r[1][2] * r[3][1] * r[2][3])
                - (r[1][1] * r[2][3] * r[3][2]) - (r[1][2] * r[2][1] * r[3][3]) - (r[1][3] * r[3][1] * r[2][2]);
        
        res[1][0] = -((r[1][0] * r[2][2] * r[3][3]) + (r[1][3] * r[2][0] * r[3][2]) + (r[1][2] * r[2][3] * r[3][0])
                - (r[1][0] * r[2][3] * r[3][2]) - (r[1][2] * r[2][0] * r[3][3]) - (r[1][3] * r[2][2] * r[3][0])); // min

        res[2][0] = (r[1][0] * r[2][1] * r[3][3]) + (r[1][1] * r[2][3] * r[3][0]) + (r[1][3] * r[2][0] * r[3][1])
                - (r[1][0] * r[2][3] * r[3][1]) - (r[1][1] * r[2][0] * r[3][3]) - (r[1][3] * r[2][1] * r[3][0]);

        res[3][0] = -((r[1][0] * r[2][1] * r[3][2]) + (r[1][1] * r[2][2] * r[3][0]) + (r[1][2] * r[2][0] * r[3][1])
                - (r[1][0] * r[2][2] * r[3][1]) - (r[1][1] * r[2][0] * r[3][2]) - (r[1][2] * r[2][1] * r[3][0])); // min

        res[0][1] = -((r[0][1] * r[2][2] * r[3][3]) + (r[0][2] * r[2][3] * r[3][1]) + (r[0][3] * r[2][1] * r[3][2]) 
                - (r[0][1] * r[2][3] * r[3][2]) - (r[0][2] * r[2][1] * r[3][3]) - (r[0][3] * r[2][2] * r[3][1])); // min

        res[1][1] = (r[0][0] * r[2][2] * r[3][3]) + (r[0][2] * r[2][3] * r[3][0]) + (r[0][3] * r[2][0] * r[3][2])
                - (r[0][0] * r[2][3] * r[3][2]) - (r[0][2] * r[2][0] * r[3][3]) - (r[0][3] * r[2][2] * r[3][0]);
                
        res[2][1] = -((r[0][0] * r[2][1] * r[3][3]) + (r[0][1] * r[2][3] * r[3][0]) + (r[0][3] * r[2][0] * r[3][1])
                 - (r[0][0] * r[2][3] * r[3][1]) - (r[0][1] * r[2][0] * r[3][3]) - (r[0][3] * r[2][1] * r[3][0])); // min

        res[3][1] = (r[0][0] * r[2][1] * r[3][2]) + (r[0][1] * r[3][0] * r[2][2]) + (r[0][2] * r[2][0] * r[3][1])
                - (r[0][0] * r[2][2] * r[3][1]) - (r[0][1] * r[2][0] * r[3][2]) - (r[0][2] * r[2][1] * r[3][0]);

        res[0][2] = (r[0][1] * r[1][2] * r[3][3]) + (r[0][2] * r[1][3] * r[3][1]) + (r[0][3] * r[1][1] * r[3][2])
                 - (r[0][1] * r[1][3] * r[3][2]) - (r[0][2] * r[1][1] * r[3][3]) - (r[0][3] * r[1][2] * r[3][1]);

        res[1][2] = -((r[0][0] * r[1][2] * r[3][3]) + (r[0][2] * r[1][3] * r[3][0]) + (r[0][3] * r[1][0] * r[3][2])
                - (r[0][0] * r[1][3] * r[3][2]) - (r[0][2] * r[1][0] * r[3][3]) - (r[0][3] * r[1][2] * r[3][0])); // min

        res[2][2] = (r[0][0] * r[1][1] * r[3][3]) + (r[0][1] * r[1][3] * r[3][0]) + (r[0][3] * r[1][0] * r[3][1])
                - (r[0][0] * r[1][3] * r[3][1]) - (r[0][1] * r[1][0] * r[3][3]) - (r[0][3] * r[1][1] * r[3][0]);

        res[3][2] = -((r[0][0] * r[1][1] * r[3][2]) + (r[0][1] * r[1][2] * r[3][0]) + (r[0][2] * r[1][0] * r[3][1])
                - (r[0][0] * r[1][2] * r[3][1]) - (r[0][1] * r[1][0] * r[3][2]) - (r[0][2] * r[1][1] * r[3][0])); // min

        res[0][3] = -((r[0][1] * r[1][2] * r[2][3]) + (r[0][2] * r[1][3] * r[2][1]) + (r[0][3] * r[1][1] * r[2][2])
                - (r[0][1] * r[1][3] * r[2][2]) - (r[0][2] * r[1][1] * r[2][3]) - (r[0][3] * r[1][2] * r[2][1])); // min

        res[1][3] = (r[0][0] * r[1][2] * r[2][3]) + (r[0][2] * r[1][3] * r[2][0]) + (r[0][3] * r[1][0] * r[2][2])
                - (r[0][0] * r[1][3] * r[2][2]) - (r[0][2] * r[1][0] * r[2][3]) - (r[0][3] * r[1][2] * r[2][0]);
                
        res[2][3] = -((r[0][0] * r[1][1] * r[2][3]) + (r[0][1] * r[1][3] * r[2][0]) + (r[0][3] * r[1][0] * r[2][1])
                - (r[0][0] * r[1][3] * r[2][1]) - (r[0][1] * r[1][0] * r[2][3]) - (r[0][3] * r[1][1] * r[2][0])); // min

        res[3][3] = (r[0][0] * r[1][1] * r[2][2]) + (r[0][1] * r[1][2] * r[2][0]) + (r[0][2] * r[1][0] * r[2][1])
                - (r[0][0] * r[1][2] * r[2][1]) - (r[0][1] * r[1][0] * r[2][2]) - (r[0][2] * r[1][1] * r[2][0]);

        return res * (1/d);
    }

    bool Matrix::operator==(const Matrix& b) const {
        return (r[0] == b.r[0] && r[1] == b.r[1] && r[2] == b.r[2] && r[3] == b.r[3]);
    }

    bool Matrix::operator!=(const Matrix& b) const {
        return !(r[0] == b.r[0] && r[1] == b.r[1] && r[2] == b.r[2] && r[3] == b.r[3]);
    }

    Matrix product(const Matrix& a, const Matrix& b) {
        Matrix res;
        Matrix bt = b.transpose();
        
        res[0][0] = dot(a[0], bt[0]);
        res[0][1] = dot(a[0], bt[1]);
        res[0][2] = dot(a[0], bt[2]);
        res[0][3] = dot(a[0], bt[3]);

        res[1][0] = dot(a[1], bt[0]);
        res[1][1] = dot(a[1], bt[1]);
        res[1][2] = dot(a[1], bt[2]);
        res[1][3] = dot(a[1], bt[3]);

        res[2][0] = dot(a[2], bt[0]);
        res[2][1] = dot(a[2], bt[1]);
        res[2][2] = dot(a[2], bt[2]);
        res[2][3] = dot(a[2], bt[3]);

        res[3][0] = dot(a[3], bt[0]);
        res[3][1] = dot(a[3], bt[1]);
        res[3][2] = dot(a[3], bt[2]);
        res[3][3] = dot(a[3], bt[3]);
        return res;
    }

    Matrix operator*(const Matrix& a, float scalar) {
        return Matrix(scalar * a[0], scalar * a[1], scalar * a[2], scalar * a[3]);
    }

    Matrix operator*(float scalar, const Matrix& a) {
        return a * scalar;
    }

    Float4 Matrix::operator*(const Float4& b) const {
        return Float4(dot(r[0], b), dot(r[1], b), dot(r[2], b), dot(r[3], b));
    }

    Vector Matrix::operator*(const Vector& b) const {
        return Vector(this->operator*(Float4(b)));
    }

    Point Matrix::operator*(const Point& b) const {
        return Point(this->operator*(Float4(b)));
    }

    float Matrix::det() const {
        float a00 = 0, a01 = 0, a02 = 0, a03 = 0;
        a00 = (r[1][1] * r[2][2] * r[3][3]) + (r[1][2] * r[2][3] * r[3][1]) + (r[1][3] * r[2][1] * r[3][2])
            - (r[1][1] * r[2][3] * r[3][2]) - (r[1][2] * r[2][1] * r[3][3]) - (r[1][3] * r[2][2] * r[3][1]);
        a01 = (r[1][0] * r[2][2] * r[3][3]) + (r[1][2] * r[2][3] * r[3][0]) + (r[1][3] * r[2][0] * r[3][2])
            - (r[1][0] * r[2][3] * r[3][2]) - (r[1][2] * r[2][0] * r[3][3]) - (r[1][3] * r[2][2] * r[3][0]);
        a02 = (r[1][0] * r[2][1] * r[3][3]) + (r[1][1] * r[2][3] * r[3][0]) + (r[1][3] * r[2][0] * r[3][1])
            - (r[1][0] * r[2][3] * r[3][1]) - (r[1][1] * r[2][0] * r[3][3]) - (r[1][3] * r[2][1] * r[3][0]);
        a03 = (r[1][0] * r[2][1] * r[3][2]) + (r[1][1] * r[2][2] * r[3][0]) + (r[1][2] * r[2][0] * r[3][1])
            - (r[1][0] * r[2][2] * r[3][1]) - (r[1][1] * r[2][0] * r[3][2]) - (r[1][2] * r[2][1] * r[3][0]);

        return ((r[0][0] * a00) - (r[0][1] * a01) + (r[0][2] * a02) - (r[0][3] * a03));

    }

    Matrix Matrix::zero() {
        Float4 zero_float = Float4(0, 0, 0, 0);
        return Matrix(zero_float, zero_float, zero_float, zero_float);
    }

    Matrix Matrix::identity() {
        return Matrix(
            Float4(1, 0, 0, 0),
            Float4(0, 1, 0, 0),
            Float4(0, 0, 1, 0),
            Float4(0, 0, 0, 1)
        );
    }

    Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
        return Matrix(
            Float4(e1.x, e2.x, e3.x, 0),
            Float4(e1.y, e2.y, e3.y, 0),
            Float4(e1.z, e2.z, e3.z, 0),
            Float4(0, 0, 0, 1)
        );
    }

}