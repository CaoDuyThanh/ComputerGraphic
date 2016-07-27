#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../../../GraphicUtils/Components/Matrix/Matrix.h"
#include "../../../Utils/Log/log.h"
#include "../../../Exception/Exception.h"
using namespace std;

class Node{
public:
    string NodeName;						// Name of Node

    unsigned int NumMeshes;
    vector<Mesh*> Meshes;

    Node* Parent;

    unsigned int NumChildren;
    vector<Node*> Children;

    Matrix4x4s Transformation;
    Vector3s Translate;
    Vector3s Rotate;
    Vector3s Scale;
public:    
    Node();
    ~Node();

    bool InitEmptyMeshes(unsigned int numMeshes);
    bool InitEmptyMaterials(unsigned int numMaterials);
    bool InitEmptyTextures(unsigned int numTextures);
    bool InitEmptyChildren(unsigned int numChildren);
    Node* GetNode(std::string NodeName);    
    void InitBuffer();
    void Draw(bool);
    void DisplayNormal();

private:
    void deleteMeshes();
    void deleteMaterials();
    void deleteTextures();
    void deleteChildren();
};

#endif