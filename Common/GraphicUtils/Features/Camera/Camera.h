#ifndef CAMERA_H
#define CAMERA_H

#include "../../Components/Matrix/Matrix.h"

class Camera{
protected:
    Vector3s Direction;
    Vector3s UpDir;
    Vector3s RightDir;

public:
    Vector3s Eye;
    Vector3s EyeRef;
    Vector3s Up;

    double Speed;
    double Fovy;
    double Ratio;
    double Near;
    double Far;

    Matrix4x4s View;
    Matrix4x4s Projection;

public:
    Camera();
    Camera(Vector3s &eye, Vector3s &eyeRef, Vector3s &up);
    void MoveMouse(double moveWidth, double moveHight);
    void UpdatePerspective();
    
protected:
    void calculateView();

public:
    // Static functions
    Matrix4x4s static CreateFrustumMatrix(const double Left, const double Right, const double Bottom, const double Top, const double Near, const double Far);
    Matrix4x4s static CreatePerspectiveMatrix(const double Fovy, const double AspectRatio, const double Near, const double Far);
    Matrix4x4s static CreateLookAtMatrix(Vector3s &r, Vector3s &up, Vector3s &n, Vector3s &eye);
};


#endif