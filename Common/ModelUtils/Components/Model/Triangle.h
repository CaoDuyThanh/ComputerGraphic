#ifndef TRIANGLE_H
#define TRIANGLE_H
using namespace std;
#include "../../../GraphicUtils/Components/Vector/Vector3s.h"
#include "../../../Utils/base/Object.h"

class ITriangle : public Object{
public:
    unsigned int Point1Id;
    unsigned int Point2Id;
    unsigned int Point3Id;

    unsigned int UV1Id;
    unsigned int UV2Id;
    unsigned int UV3Id;

public:
    ITriangle(){
        Point1Id = Point2Id = Point3Id = 0;
        UV1Id = UV2Id = UV3Id = 0;
    }
    ITriangle(unsigned int point1Id,
              unsigned int point2Id,
              unsigned int point3Id,
              unsigned int uv1Id,
              unsigned int uv2Id,
              unsigned int uv3Id):
    Point1Id(point1Id),
    Point2Id(point2Id),
    Point3Id(point3Id),
    UV1Id(uv1Id),
    UV2Id(uv2Id),
    UV3Id(uv3Id)
    {
        // Do nothing    
    }
};

class PTriangle3s{
public:
    Vector3s Point1;
    Vector3s Point2;
    Vector3s Point3;

public:
    PTriangle3s();
    PTriangle3s(Vector3s point1, 
                Vector3s point2, 
                Vector3s point3):
    Point1(point1), 
    Point2(point2), 
    Point3(point3)
    {
        // Do nothing
    }
};
#endif




