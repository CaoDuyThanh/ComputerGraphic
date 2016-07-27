#include "Matrix.h"

// Constructor
Matrix4x4s::Matrix4x4s():
A1(1), A2(0), A3(0), A4(0),
B1(0), B2(1), B3(0), B4(0),
C1(0), C2(0), C3(1), C4(0),
D1(0), D2(0), D3(0), D4(1)
{
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s::Matrix4x4s(double a1, double a2, double a3, double a4,
                       double b1, double b2, double b3, double b4,
                       double c1, double c2, double c3, double c4,
                       double d1, double d2, double d3, double d4) :
    A1(a1), A2(a2), A3(a3), A4(a4),
    B1(b1), B2(b2), B3(b3), B4(b4),
    C1(c1), C2(c2), C3(c3), C4(c4),
    D1(d1), D2(d2), D3(d3), D4(d4)
{
    // Do nothing here
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s &Matrix4x4s::Transpose(){
    std::swap((double &)B1, (double &)A2);
    std::swap((double &)C1, (double &)A3);
    std::swap((double &)C2, (double &)B3);
    std::swap((double &)D1, (double &)A4);
    std::swap((double &)D2, (double &)B4);
    std::swap((double &)D3, (double &)C4);
    return *this;
}
//-----------------------------------------------------------------------------------------------------------------------------
double Matrix4x4s::Determinant() const {
    return   A1*B2*C3*D4 - A1*B2*C4*D3 + A1*B3*C4*D2 - A1*B3*C2*D4
           + A1*B4*C2*D3 - A1*B4*C3*D2 - A2*B3*C4*D1 + A2*B3*C1*D4
           - A2*B4*C1*D3 + A2*B4*C3*D1 - A2*B1*C3*D4 + A2*B1*C4*D3
           + A3*B4*C1*D2 - A3*B4*C2*D1 + A3*B1*C2*D4 - A3*B1*C4*D2
           + A3*B2*C4*D1 - A3*B2*C1*D4 - A4*B1*C2*D3 + A4*B1*C3*D2
           - A4*B2*C3*D1 + A4*B2*C1*D3 - A4*B3*C1*D2 + A4*B3*C2*D1;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s &Matrix4x4s::Inverse(){
    const double det = Determinant();

    const double invdet = (1.0) / det;

    Matrix4x4s res;
    res.A1 =  invdet  * (B2 * (C3 * D4 - C4 * D3) + B3 * (C4 * D2 - C2 * D4) + B4 * (C2 * D3 - C3 * D2));
    res.A2 = -invdet * (A2 * (C3 * D4 - C4 * D3) + A3 * (C4 * D2 - C2 * D4) + A4 * (C2 * D3 - C3 * D2));
    res.A3 =  invdet  * (A2 * (B3 * D4 - B4 * D3) + A3 * (B4 * D2 - B2 * D4) + A4 * (B2 * D3 - B3 * D2));
    res.A4 = -invdet * (A2 * (B3 * C4 - B4 * C3) + A3 * (B4 * C2 - B2 * C4) + A4 * (B2 * C3 - B3 * C2));
    res.B1 = -invdet * (B1 * (C3 * D4 - C4 * D3) + B3 * (C4 * D1 - C1 * D4) + B4 * (C1 * D3 - C3 * D1));
    res.B2 =  invdet  * (A1 * (C3 * D4 - C4 * D3) + A3 * (C4 * D1 - C1 * D4) + A4 * (C1 * D3 - C3 * D1));
    res.B3 = -invdet * (A1 * (B3 * D4 - B4 * D3) + A3 * (B4 * D1 - B1 * D4) + A4 * (B1 * D3 - B3 * D1));
    res.B4 =  invdet  * (A1 * (B3 * C4 - B4 * C3) + A3 * (B4 * C1 - B1 * C4) + A4 * (B1 * C3 - B3 * C1));
    res.C1 =  invdet  * (B1 * (C2 * D4 - C4 * D2) + B2 * (C4 * D1 - C1 * D4) + B4 * (C1 * D2 - C2 * D1));
    res.C2 = -invdet * (A1 * (C2 * D4 - C4 * D2) + A2 * (C4 * D1 - C1 * D4) + A4 * (C1 * D2 - C2 * D1));
    res.C3 =  invdet  * (A1 * (B2 * D4 - B4 * D2) + A2 * (B4 * D1 - B1 * D4) + A4 * (B1 * D2 - B2 * D1));
    res.C4 = -invdet * (A1 * (B2 * C4 - B4 * C2) + A2 * (B4 * C1 - B1 * C4) + A4 * (B1 * C2 - B2 * C1));
    res.D1 = -invdet * (B1 * (C2 * D3 - C3 * D2) + B2 * (C3 * D1 - C1 * D3) + B3 * (C1 * D2 - C2 * D1));
    res.D2 =  invdet  * (A1 * (C2 * D3 - C3 * D2) + A2 * (C3 * D1 - C1 * D3) + A3 * (C1 * D2 - C2 * D1));
    res.D3 = -invdet * (A1 * (B2 * D3 - B3 * D2) + A2 * (B3 * D1 - B1 * D3) + A3 * (B1 * D2 - B2 * D1));
    res.D4 =  invdet  * (A1 * (B2 * C3 - B3 * C2) + A2 * (B3 * C1 - B1 * C3) + A3 * (B1 * C2 - B2 * C1));
    *this = res;

    return *this;
}
//-----------------------------------------------------------------------------------------------------------------------------
bool Matrix4x4s::operator == (const Matrix4x4s &m) const
{
    return (A1 == m.A1 && A2 == m.A2 && A3 == m.A3 && A4 == m.A4 &&
            B1 == m.B1 && B2 == m.B2 && B3 == m.B3 && B4 == m.B4 &&
            C1 == m.C1 && C2 == m.C2 && C3 == m.C3 && C4 == m.C4 &&
            D1 == m.D1 && D2 == m.D2 && D3 == m.D3 && D4 == m.D4);
}
//-----------------------------------------------------------------------------------------------------------------------------
bool Matrix4x4s::operator != (const Matrix4x4s &m) const
{
	return !(*this == m);
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s &Matrix4x4s::operator *= (const Matrix4x4s &m)
{
    *this = Matrix4x4s(
        m.A1 * A1 + m.B1 * A2 + m.C1 * A3 + m.D1 * A4,
        m.A2 * A1 + m.B2 * A2 + m.C2 * A3 + m.D2 * A4,
        m.A3 * A1 + m.B3 * A2 + m.C3 * A3 + m.D3 * A4,
        m.A4 * A1 + m.B4 * A2 + m.C4 * A3 + m.D4 * A4,
        m.A1 * B1 + m.B1 * B2 + m.C1 * B3 + m.D1 * B4,
        m.A2 * B1 + m.B2 * B2 + m.C2 * B3 + m.D2 * B4,
        m.A3 * B1 + m.B3 * B2 + m.C3 * B3 + m.D3 * B4,
        m.A4 * B1 + m.B4 * B2 + m.C4 * B3 + m.D4 * B4,
        m.A1 * C1 + m.B1 * C2 + m.C1 * C3 + m.D1 * C4,
        m.A2 * C1 + m.B2 * C2 + m.C2 * C3 + m.D2 * C4,
        m.A3 * C1 + m.B3 * C2 + m.C3 * C3 + m.D3 * C4,
        m.A4 * C1 + m.B4 * C2 + m.C4 * C3 + m.D4 * C4,
        m.A1 * D1 + m.B1 * D2 + m.C1 * D3 + m.D1 * D4,
        m.A2 * D1 + m.B2 * D2 + m.C2 * D3 + m.D2 * D4,
        m.A3 * D1 + m.B3 * D2 + m.C3 * D3 + m.D3 * D4,
        m.A4 * D1 + m.B4 * D2 + m.C4 * D3 + m.D4 * D4);
    return *this;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::operator * (const Matrix4x4s &m)
{
    Matrix4x4s newMatrix = Matrix4x4s(
        m.A1 * A1 + m.B1 * A2 + m.C1 * A3 + m.D1 * A4,
        m.A2 * A1 + m.B2 * A2 + m.C2 * A3 + m.D2 * A4,
        m.A3 * A1 + m.B3 * A2 + m.C3 * A3 + m.D3 * A4,
        m.A4 * A1 + m.B4 * A2 + m.C4 * A3 + m.D4 * A4,
        m.A1 * B1 + m.B1 * B2 + m.C1 * B3 + m.D1 * B4,
        m.A2 * B1 + m.B2 * B2 + m.C2 * B3 + m.D2 * B4,
        m.A3 * B1 + m.B3 * B2 + m.C3 * B3 + m.D3 * B4,
        m.A4 * B1 + m.B4 * B2 + m.C4 * B3 + m.D4 * B4,
        m.A1 * C1 + m.B1 * C2 + m.C1 * C3 + m.D1 * C4,
        m.A2 * C1 + m.B2 * C2 + m.C2 * C3 + m.D2 * C4,
        m.A3 * C1 + m.B3 * C2 + m.C3 * C3 + m.D3 * C4,
        m.A4 * C1 + m.B4 * C2 + m.C4 * C3 + m.D4 * C4,
        m.A1 * D1 + m.B1 * D2 + m.C1 * D3 + m.D1 * D4,
        m.A2 * D1 + m.B2 * D2 + m.C2 * D3 + m.D2 * D4,
        m.A3 * D1 + m.B3 * D2 + m.C3 * D3 + m.D3 * D4,
        m.A4 * D1 + m.B4 * D2 + m.C4 * D3 + m.D4 * D4);
    return newMatrix;
}
//-----------------------------------------------------------------------------------------------------------------------------
Vector4s Matrix4x4s::operator * (const Vector4s &v)
{
    Vector4s newVector = Vector4s(
        v.X * A1 + v.Y * A2 + v.Z * A3 + v.T * A4,
        v.X * B1 + v.Y * B2 + v.Z * B3 + v.T * B4,
        v.X * C1 + v.Y * C2 + v.Z * C3 + v.T * C4,
        v.X * D1 + v.Y * D2 + v.Z * D3 + v.T * D4);
    return newVector;
}
//-----------------------------------------------------------------------------------------------------------------------------
Vector3s Matrix4x4s::operator * (const Vector3s &v)
{
    Vector4s v1 = Vector4s(v.X, v.Y, v.Z, 0.0);

    Vector4s newVector = Vector4s(
        v1.X * A1 + v1.Y * A2 + v1.Z * A3 + v1.T * A4,
        v1.X * B1 + v1.Y * B2 + v1.Z * B3 + v1.T * B4,
        v1.X * C1 + v1.Y * C2 + v1.Z * C3 + v1.T * C4,
        v1.X * D1 + v1.Y * D2 + v1.Z * D3 + v1.T * D4);
    return Vector3s(newVector.X, newVector.Y, newVector.Z);
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::Identity(){
    Matrix4x4s m;
    m.A1 = 1;
    m.B2 = 1;
    m.C3 = 1;
    m.D4 = 1;
    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateRotatedMatrixX(double radians){
    Matrix4x4s m;
    m.A1 = 1;		m.A2 = 0;			         m.A3 = 0;			          m.A4 = 0;
    m.B1 = 0;		m.B2 = cos(radians);	m.B3 = -sin(radians);	m.B4 = 0;
    m.C1 = 0;		m.C2 = sin(radians);	m.C3 =  cos(radians);	m.C4 = 0;
    m.D1 = 0;		m.D2 = 0;				        m.D3 = 0;			          m.D4 = 1;

    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateRotatedMatrixY(double radians){
    Matrix4x4s m;
    m.A1 = cos(radians);	 m.A2 = 0;		m.A3 = sin(radians);		m.A4 = 0;
    m.B1 = 0; 		 	        m.B2 = 1;		m.B3 = 0;	 			        m.B4 = 0;
    m.C1 = -sin(radians);	m.C2 = 0;		m.C3 = cos(radians);		m.C4 = 0;
    m.D1 = 0;		 		        m.D2 = 0;		m.D3 = 0;		 	        	m.D4 = 1;

    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateRotatedMatrixZ(double radians){
    Matrix4x4s m;
    m.A1 = cosf(radians);		m.A2 = -sinf(radians);		 m.A3 = 0;		m.A4 = 0;
    m.B1 = sinf(radians);		m.B2 =  cosf(radians);			m.B3 = 0;		m.B4 = 0;
    m.C1 = 0;				          m.C2 = 0;				            m.C3 = 1;		m.C4 = 0;
    m.D1 = 0;				          m.D2 = 0;				            m.D3 = 0;		m.D4 = 1;

    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateRotatedMatrix(double radians, Vector3s Vec){
    Vec.Normalize();
    double s = sin(radians);
    double c = cos(radians);

    Matrix4x4s m;
    m.A1 = Vec.X * Vec.X * (1 - c) + c;			      	m.A2 = Vec.X * Vec.Y * (1 - c) - Vec.Z * s;		m.A3 = Vec.X * Vec.Z * (1 - c) + Vec.Y * s;		m.A4 = 0;
    m.B1 = Vec.X * Vec.Y * (1 - c) + Vec.Z * s;		m.B2 = Vec.Y * Vec.Y * (1 - c) + c;				      m.B3 = Vec.Y * Vec.Z * (1 - c) - Vec.X * s;		m.B4 = 0;
    m.C1 = Vec.X * Vec.Z * (1 - c) - Vec.Y * s;		m.C2 = Vec.Y * Vec.Z * (1 - c) + Vec.X * s;		m.C3 = Vec.Z * Vec.Z * (1 - c) + c;				      m.C4 = 0;
    m.D1 = 0;										                          m.D2 = 0;										                          m.D3 = 0;										                          m.D4 = 1;

    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateTranslatedMatrix(const double dx, const double dy, const double dz){
    Matrix4x4s m = Matrix4x4s::Identity();
    m.A4 = dx;
    m.B4 = dy;
    m.C4 = dz;
    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateTranslatedMatrix(const Vector3s &Vecd){
    return CreateTranslatedMatrix(Vecd.X, Vecd.Y, Vecd.Z);
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateScaledMatrix(const double sx, const double sy, const double sz){
    Matrix4x4s m = Matrix4x4s::Identity();
    m.A1 = sx;
    m.B2 = sy;
    m.C3 = sz;
    return m;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Matrix4x4s::CreateScaledMatrix(const Vector3s &Vecs){
    return CreateScaledMatrix(Vecs.X, Vecs.Y, Vecs.Z);
}
//-----------------------------------------------------------------------------------------------------------------------------