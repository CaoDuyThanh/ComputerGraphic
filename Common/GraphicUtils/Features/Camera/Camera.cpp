#include "Camera.h"

//- CONSTRUCTOR ---------------------------------------------------------------------------------------------------------------
Camera::Camera():
Eye(Vector3s(0, 0, 0)),
EyeRef(Vector3s(0, 0, 0)),
Up(Vector3s(0, 0, 0)),
    Speed(1.0),
    Fovy(10.0),
    Ratio(1.0),
    Near(0.01),
    Far(10000)
{
    calculateView();
}
//-----------------------------------------------------------------------------------------------------------------------------
Camera::Camera(Vector3s &eye, Vector3s &eyeRef, Vector3s &up):
Eye(eye),
EyeRef(eyeRef),
Up(up),
    Speed(1.0),
    Fovy(10.0),
    Ratio(1.0),
    Near(0.1),
    Far(10000)
{
    calculateView();
}
//-----------------------------------------------------------------------------------------------------------------------------
void Camera::MoveMouse(double moveWidth, double moveHeight){
    Vector3s mTempDirection = Matrix4x4s::CreateRotatedMatrixX(-moveHeight) * Matrix4x4s::CreateRotatedMatrixY(-moveWidth) * Direction;
    Vector3s newEyeRef = Eye - mTempDirection;
    EyeRef = newEyeRef;
    calculateView();
}
//-----------------------------------------------------------------------------------------------------------------------------
void Camera::UpdatePerspective(){
    Projection = Camera::CreatePerspectiveMatrix(Fovy, Ratio, Near, Far);
}

//- Protected function --------------------------------------------------------------------------------------------------------
void Camera::calculateView(){
    Direction = Eye - EyeRef;
    RightDir = Up ^ Direction;
    Up = Direction ^ RightDir;

    Direction.Normalize();
    Up.Normalize();
    RightDir.Normalize();

    View = Camera::CreateLookAtMatrix(RightDir, Up, Direction, Eye);
}

// Static function
Matrix4x4s Camera::CreateFrustumMatrix(double Left, double Right, double Bottom, double Top, double Near, double Far)
{
    double Temp1, Temp2, Temp3, Temp4;
    Temp1 = 2.0 * Near;
    Temp2 = Right - Left;
    Temp3 = Top - Bottom;
    Temp4 = Far - Near;

    Matrix4x4s Projection;
    Projection.A1 = Temp1 / Temp2;			Projection.A2 = 0.0;						Projection.A3 = (Right + Left) / Temp2;	Projection.A4 = 0.0;
    Projection.B1 = 0.0;					Projection.B2 = Temp1 / Temp3;				Projection.B3 = (Top + Bottom) / Temp3;	Projection.B4 = 0.0;
    Projection.C1 = 0;						Projection.C2 = 0.0;						Projection.C3 = (-Far - Near) / Temp4;	Projection.C4 = (-Temp1 * Far) / Temp4;
    Projection.D1 = 0.0;					Projection.D2 = 0.0;						Projection.D3 = -1;						Projection.D4 = 0.0;

    return Projection;
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Camera::CreatePerspectiveMatrix(double Fovy, double AspectRatio, double Near, double Far){
    double yMax, xMax;
    double temp, temp2, temp3, temp4;
    const double M_PI = 3.1415926535897932384626433832795028841971693993751058;
    yMax = Near * tanf(Fovy * M_PI / 360.0);
    xMax = yMax * AspectRatio;

    return CreateFrustumMatrix(-xMax, xMax, -yMax, yMax, Near, Far);
}
//-----------------------------------------------------------------------------------------------------------------------------
Matrix4x4s Camera::CreateLookAtMatrix(Vector3s &r, Vector3s &up, Vector3s &n, Vector3s &eye){
    Matrix4x4s View;
    View.A1 = r.X;		 View.A2 = r.Y;		View.A3 = r.Z;		  View.A4 = -r.Dot(eye);
    View.B1 = up.X;		View.B2 = up.Y;	View.B3 = up.Z;	 	View.B4 = -up.Dot(eye);
    View.C1 = n.X;		 View.C2 = n.Y;		View.C3 = n.Z;		  View.C4 = -n.Dot(eye);
    View.D1 = 0;		   View.D2 = 0;		  View.D3 = 0;    		View.D4 = 1;
    return View;
}
//-----------------------------------------------------------------------------------------------------------------------------
