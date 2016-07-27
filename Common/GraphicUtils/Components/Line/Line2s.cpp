#include "Line2s.h"

// Constructor
Line2s::Line2s():
P1(Vector2s(0, 0)), P2(Vector2s(0, 0))
{
    // Do nothing here
}
// --------------------------------------------------------------------------------------------------
Line2s::Line2s(Vector2s p1, Vector2s p2):
P1(p1), P2(p2)
{
    // Do nothing here
}
// --------------------------------------------------------------------------------------------------
Vector2s Line2s::GetDirection(){
    Vector2s dir = Vector2s(P2.X - P1.X, P2.Y - P1.Y);
    dir.Normalize();
    return dir;
}
// --------------------------------------------------------------------------------------------------
Vector2s Line2s::GetNnormal(){
    Vector2s dir = GetDirection();
    Vector2s nor = Vector2s(dir.Y, -dir.X);
    return nor;
}