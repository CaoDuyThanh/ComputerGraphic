#ifndef TEXTURE_H
#define TEXTURE_H
#include <Windows.h>
#include <string>
#include <iostream>
#include <hash_map>
#include <cstdlib>
#include <gl\GL.h>
#include "../../../GraphicUtils/Components/Matrix/Matrix.h"
#include "../../../Utils/Log/log.h"
#include "Image.h"
using namespace std;

class Texture{
public:
    static hash_map<string, Image*> Images;

public:
    string TextureName;
    Image* Image;
    double ScaleU;
    double ScaleV;
    double TranslateU;
    double TranslateV;
    bool IsSwapUV;
    double RotateU;
    double RotateV;
    double RotateW;

    string AlphaSource;
    double CropLeft;
    double CropRight;
    double CropTop;
    double CropBottom;

    string MappingType;
    string BlendMode;
    double Alpha;

    string MaterialUsed;
    string TextureUsed;
public:
    Texture();
    void Active();

    string ToString();
};

#endif




