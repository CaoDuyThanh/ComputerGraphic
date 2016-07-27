#ifndef VECTOR3S_H
#define VECTOR3S_H
#include <math.h>
#include "../../../Utils/base/Object.h"

class Vector3s : public Object{
public:
    double X;
    double Y;
    double Z;

public:
    Vector3s();
    Vector3s(double x, double y, double z);

    double Length();
    void Normalize();
    double Dot(Vector3s &b);
    void Lerp(Vector3s &b, double amount);

    // Operator
    bool operator == (const Vector3s& v);
    bool operator != (const Vector3s& v);
    Vector3s& operator += (const Vector3s& v);
    Vector3s& operator -= (const Vector3s& v);
    Vector3s& operator *= (const double value);
    Vector3s& operator /= (const double value);

    Vector3s operator + (const Vector3s& v2);
    Vector3s operator - (const Vector3s& v2);
    Vector3s operator * (const Vector3s& v2);
    Vector3s operator * (const double value);
    Vector3s operator / (const double value);
    Vector3s operator / (const Vector3s& v2);
    Vector3s operator ^ (const Vector3s& v2);      // Cross function
    Vector3s operator - ();
};

#endif