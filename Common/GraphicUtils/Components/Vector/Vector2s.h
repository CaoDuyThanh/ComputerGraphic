#ifndef VECTOR2S_H
#define VECTOR2S_H
#include <math.h>
#include "../../../Utils/base/Object.h"

class Vector2s : public Object{
public:
    double X;
    double Y;

public:
    // Constructor
    Vector2s();
    Vector2s(double x, double y);
	
    double Length();
    void Normalize();
    double Dot(Vector2s &b);	

	   // Operator
	   bool operator == (const Vector2s& v);
	   bool operator != (const Vector2s& v);
	   Vector2s& operator += (const Vector2s& v);
	   Vector2s& operator -= (const Vector2s& v);
	   Vector2s& operator *= (const double value);
	   Vector2s& operator /= (const double value);

	   Vector2s operator + (const Vector2s& v2);
	   Vector2s operator - (const Vector2s& v2);
	   Vector2s operator * (const Vector2s& v2);
	   Vector2s operator * (const double value);
	   Vector2s operator / (const double value);
	   Vector2s operator / (const Vector2s& v2);
	   Vector2s operator - ();
};

#endif