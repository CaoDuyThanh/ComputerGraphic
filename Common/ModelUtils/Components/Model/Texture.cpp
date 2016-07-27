#include "Texture.h"

//- Static members --------------------------------------------------------------------------------------------
hash_map<string, Image*> Texture::Images;

//- Constructor -----------------------------------------------------------------------------------------------
Texture::Texture() :
TextureName(""),
ScaleU(0),
ScaleV(0),
TranslateU(0),
TranslateV(0),
IsSwapUV(true),
RotateU(0),
RotateV(0),
RotateW(0),
    AlphaSource(""),
    CropLeft(0),
    CropRight(0),
    CropTop(0),
    CropBottom(0),
MappingType(""),
BlendMode(""),
Alpha(0),
    MaterialUsed(""),
    TextureUsed("")
{
    // Do nothing
}
//-------------------------------------------------------------------------------------------------------------
void Texture::Active(){
    if (Image != NULL){
        glBindTexture(GL_TEXTURE_2D, Image->BufferId);
    }else{
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
//-------------------------------------------------------------------------------------------------------------
string Texture::ToString(){
    string fileName = "";
    if (Image != NULL){
        fileName = Image->FileName;
    }
    return 
           "Texture name: " + TextureName + "\n"
         + "File name: " + fileName + "\n"
         + "ScaleU: " + to_string(ScaleU) + "\n"
         + "ScaleV: " + to_string(ScaleV) + "\n"
         + "Translation U: " + to_string(TranslateU) + "\n"
         + "Tnanslation V: " + to_string(TranslateV) + "\n"
         + "IsSwapUV: " + to_string(IsSwapUV) + "\n"
         + "Rotate U: " + to_string(RotateU) + "\n"
         + "Rotate V: " + to_string(RotateV) + "\n"
         + "Rotate W: " + to_string(RotateW) + "\n"
         + "AlphaSource: " + AlphaSource + "\n"
         + "Crop left: " + to_string(CropLeft) + "\n"
         + "Crop right: " + to_string(CropRight) + "\n"
         + "Crop top: " + to_string(CropTop) + "\n"
         + "Crop bottom: " + to_string(CropBottom) + "\n"
         + "Mapping type: " + MappingType + "\n"
         + "Blend mode: " + BlendMode + "\n"
         + "Alpha: " + to_string(Alpha) + "\n"
         + "Material Used: " + MaterialUsed + "\n"
         + "Texture Used: " + TextureUsed;
}