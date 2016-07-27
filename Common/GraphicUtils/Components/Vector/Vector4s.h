#ifndef VECTOR4S_H
#define VECTOR4S_H
#include <math.h>

class Vector4s{
public:
    double X;
	   double Y;
	   double Z;
	   double T;

public:
    // Constructor
    Vector4s();
    Vector4s(double x, double y, double z, double t);
    float* ToFloatArray();

    // Operator
    bool operator == (const Vector4s& v);
    bool operator != (const Vector4s& v);
    Vector4s& operator += (const Vector4s& v);
    Vector4s& operator -= (const Vector4s& v);
    Vector4s& operator *= (const double value);
    Vector4s& operator /= (const double value);

    Vector4s operator + (const Vector4s& v2);
    Vector4s operator - (const Vector4s& v2);
    Vector4s operator * (const Vector4s& v2);
    Vector4s operator * (const double value);
    Vector4s operator / (const double value);
    Vector4s operator / (const Vector4s& v2);
    Vector4s operator - ();
};
#endif