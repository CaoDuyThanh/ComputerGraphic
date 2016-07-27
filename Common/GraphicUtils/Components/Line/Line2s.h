#ifndef LINE2S_H
#define LINE2S_H

#include "../Vector/Vector2s.h"

class Line2s{
public:
    Vector2s P1;
    Vector2s P2;

public:
    // Constructor
    Line2s();
    Line2s(Vector2s p1, Vector2s p2);
    
    Vector2s GetDirection();
    Vector2s GetNnormal();
};

#endif