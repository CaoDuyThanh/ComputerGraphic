#ifndef MESH_H
#define MESH_H
#include <Windows.h>
#include <iostream>
#include <vector>
#include "../../../GraphicUtils/Components/Vector/Vector.h"
#include "../../../Utils/glew/include/glew.h"
#include "../../../Utils/base/Object.h"
#include "../../../Utils/Log/log.h"
#include "Material.h"
#include "Texture.h"
#include "Triangle.h"
using namespace std;

class Mesh{
public:
    static const enum MeshType{
        VERTICLE = 1,
        NORMAL = 2,
        COORDINATE = 3,
        FACE = 4
    };

private:
    unsigned int currentAddedPosition;
    unsigned int currentAddedNormal;
    unsigned int currentAddedCoordinate;
    unsigned int currentAddedFace;

public:
    bool HasTexture;    
    unsigned int NumVerts;
    unsigned int NumNormals;
    unsigned int NumCoordinates;
    unsigned int NumFaces;

    unsigned int VBO;			      // Vertex Buffer Object
    unsigned int NBO;			      // Normal Buffer Object
    unsigned int CoorBO;			   // Coordinate Buffer Object
    unsigned int IBO;			      // Index Buffer Object
    unsigned int NBODisplay;  // Normal Buffer Object for Display Normal
    unsigned int INBODisplay; // Index Buffer Object for Normal Display

    vector<Material*> Materials;

    Vector3s* Vertices;
    Vector3s* Normals;
    Vector2s* UV;
    ITriangle* Faces;
public:    
    Mesh();

    void InitBuffer();
    void InitData();
    bool InitEmptyVertices(unsigned int numVerts);
    bool InitEmptyNormals(unsigned int numNormals);
    bool InitEmptyCoordinates(unsigned int numCoordinates);
    bool InitEmptyFaces(unsigned int numFaces);
    bool Push_back(MeshType Type, Object* object);
    void Draw();
    void DisplayNormal();

private:
    void beginDraw();
    void endDraw();
    void setMaterial();
    void releaseBuffer();
    void releaseData();
};
#endif