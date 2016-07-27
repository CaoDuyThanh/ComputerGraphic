#ifndef CHASECAMERA_H
#define CHASECAMERA_H
#include "Camera.h"
#include <math.h>

class ChaseCamera : public Camera{
public:
    static const float SPRINGINESS;
public:
    Vector3s NewEye;
    Vector3s NewEyeRef;

public:
    ChaseCamera(Vector3s &Eye, Vector3s &EyeRef, Vector3s &Up);

    void update();
    void setEye(Vector3s &Eye);

    void turnYAxis(float Width);
    void turnXAxis(float Height);
    void moveMouse(float MouseMoveWidth, float MouseMoveHeight);
    void zoomIn();
    void zoomOut();
    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();
};

#endif

