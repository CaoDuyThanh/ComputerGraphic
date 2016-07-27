#ifndef MATERIAL_H
#define MATERIAL_H
#include <iostream>
#include <vector>
#include "Texture.h"
#include "../../../GraphicUtils/Components/Vector/Vector.h"
using namespace std;

class Material{
public:
    string MaterialName;
    Vector4s Ambient;
    Vector4s Diffuse;
    Vector4s Specular;
    Vector4s Emissive;
    double Opacity;
    double Shininess;
    double Reflectivity;
    string ShadingMode;
    vector<Texture*> Textures;

public:
    Material();
    Material(string materialName,
             Vector4s ambient,
             Vector4s diffuse,
             Vector4s specular,
             Vector4s emissive,
             double opacity,
             double shininess,
             double reflectivity,
             string shadingMode);
    void Active();
};

#endif