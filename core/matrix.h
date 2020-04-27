#ifndef CG1RAYTRACER_MATRIX_HEADER
#define CG1RAYTRACER_MATRIX_HEADER

#include <core/float4.h>

namespace rt {

class Matrix {
public:
    Matrix() {}
    Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4);

    Float4& operator[](int idx);
    Float4 operator[](int idx) const;

    Matrix operator+(const Matrix& b) const;
    Matrix operator-(const Matrix& b) const;
    
    Matrix transpose() const;
    Matrix invert() const;

    bool operator==(const Matrix& b) const;
    bool operator!=(const Matrix& b) const;


    Float4 operator*(const Float4& b) const;
    Vector operator*(const Vector& b) const;
    Point operator*(const Point& b) const;

    float det() const;

    static Matrix zero();
    static Matrix identity();

    static Matrix system(const Vector& e1, const Vector& e2, const Vector& e3);

    Float4 r[4];
};

Matrix product(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, float scalar);
Matrix operator*(float scalar, const Matrix& a);

}

#endif