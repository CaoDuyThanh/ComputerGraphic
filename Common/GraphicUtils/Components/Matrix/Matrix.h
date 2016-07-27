#ifndef MATRIX_H
#define MATRIX_H
#include "../Vector/Vector.h"
#include <math.h>
#include <iostream>

class Matrix4x4s{
public:
    double A1, A2, A3, A4;
    double B1, B2, B3, B4;
    double C1, C2, C3, C4;
    double D1, D2, D3, D4;

public:
    // Constructor
    Matrix4x4s();
    Matrix4x4s(double a1, double a2, double a3, double a4,
               double b1, double b2, double b3, double b4,
               double c1, double c2, double c3, double c4,
               double d1, double d2, double d3, double d4);

    Matrix4x4s &Transpose();
    double Determinant() const;
    Matrix4x4s &Inverse();

    // Operator region
    bool operator == (const Matrix4x4s &m) const;
    bool operator != (const Matrix4x4s &m) const;
    Matrix4x4s& operator *= (const Matrix4x4s &m);
    Matrix4x4s operator * (const Matrix4x4s &m);
    Vector4s operator * (const Vector4s &v);
    Vector3s operator * (const Vector3s &v);

    Matrix4x4s static Identity();
    Matrix4x4s static CreateRotatedMatrixX(const double rad);
    Matrix4x4s static CreateRotatedMatrixY(const double rad);
    Matrix4x4s static CreateRotatedMatrixZ(const double rad);
    Matrix4x4s static CreateRotatedMatrix(const double Angle, Vector3s Vec);
    Matrix4x4s static CreateTranslatedMatrix(const double dx, const double dy, const double dz);
    Matrix4x4s static CreateTranslatedMatrix(const Vector3s &Vecd);
    Matrix4x4s static CreateScaledMatrix(const double sx, const double sy, const double sz);
    Matrix4x4s static CreateScaledMatrix(const Vector3s &Vecs);
};
#endif