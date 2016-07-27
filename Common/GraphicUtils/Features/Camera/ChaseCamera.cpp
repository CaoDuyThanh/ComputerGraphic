#include "ChaseCamera.h";

const float ChaseCamera::SPRINGINESS = 0.02;

ChaseCamera::ChaseCamera(Vector3s &Eye, Vector3s &EyeRef, Vector3s &Up) :Camera(Eye, EyeRef, Up),
NewEye(Eye)
{
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::turnXAxis(float Width){
    Direction = Matrix4x4s::CreateRotatedMatrix(-Width, RightDir) * Direction;
    Direction.Normalize();
    NewEyeRef = Eye - Direction;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::turnYAxis(float Height){
    Direction = Matrix4x4s::CreateRotatedMatrixY(-Height) * Direction;
    Direction.Normalize();
    NewEyeRef = Eye - Direction;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::moveMouse(float MouseMoveWidth, float MouseMoveHeight){
    if (abs(MouseMoveWidth) > abs(MouseMoveHeight))
        turnXAxis(MouseMoveWidth);
    else
        turnYAxis(MouseMoveHeight);
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::update(){
    Eye.Lerp(NewEye, SPRINGINESS);
    EyeRef.Lerp(NewEyeRef, SPRINGINESS);
    //mEye = mNewEye;
    //mEyeRef = mNewEyeRef;
    calculateView();
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::setEye(Vector3s &Eye){
    NewEye = Eye;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::zoomIn(){
    NewEye = Eye - Direction * Speed;
    NewEyeRef = EyeRef - Direction * Speed;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::zoomOut(){
    NewEye = Eye + Direction * Speed;
    NewEyeRef = EyeRef + Direction * Speed;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::moveForward(){
    NewEye.X = Eye.X - Direction.X * Speed;
    NewEye.Z = Eye.Z - Direction.Z * Speed;

    NewEyeRef.X = EyeRef.X - Direction.X * Speed;
    NewEyeRef.Z = EyeRef.Z - Direction.Z * Speed;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::moveBack(){
    NewEye.X = Eye.X + Direction.X * Speed;
    NewEye.Z = Eye.Z + Direction.Z * Speed;

    NewEyeRef.X = EyeRef.X + Direction.X * Speed;
    NewEyeRef.Z = EyeRef.Z + Direction.Z * Speed;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::moveLeft(){
    NewEye.X = Eye.X - RightDir.X * Speed;
    NewEye.Z = Eye.Z - RightDir.Z * Speed;

    NewEyeRef.X = EyeRef.X - RightDir.X * Speed;
    NewEyeRef.Z = EyeRef.Z - RightDir.Z * Speed;
}

//-----------------------------------------------------------------------------------------------------------------------------
void ChaseCamera::moveRight(){
    NewEye.X = Eye.X + RightDir.X * Speed;
    NewEye.Z = Eye.Z + RightDir.Z * Speed;

    NewEyeRef.X = EyeRef.X + RightDir.X * Speed;
    NewEyeRef.Z = EyeRef.Z + RightDir.Z * Speed;
}
