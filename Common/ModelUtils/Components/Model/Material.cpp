#include "Material.h"


// Constructor
Material::Material():
MaterialName(""),
Ambient(Vector4s(0, 0, 0, 0)),
Diffuse(Vector4s(0, 0, 0, 0)),
Specular(Vector4s(0, 0, 0, 0)),
Emissive(Vector4s(0, 0, 0, 0)),
Opacity(0),
Shininess(0),
Reflectivity(0),
ShadingMode("Phong")
{
    // Do nothing
}
//-------------------------------------------------------------------------------------------------------------
Material::Material(string materialName,
                   Vector4s ambient,
                   Vector4s diffuse,
                   Vector4s specular,
                   Vector4s emissive,
                   double opacity,
                   double shininess,
                   double reflectivity,
                   string shadingMode) :
MaterialName(materialName),
Ambient(ambient),
Diffuse(diffuse),
Specular(specular),
Emissive(emissive),
Opacity(opacity),
Shininess(shininess),
Reflectivity(reflectivity),
ShadingMode(shadingMode)
{
    // Do nothing
}
//-------------------------------------------------------------------------------------------------------------
void Material::Active(){
    //glMaterialfv(GL_FRONT, GL_EMISSION, Emissive.ToFloatArray());
    //glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient.ToFloatArray());
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse.ToFloatArray());
    //glMaterialfv(GL_FRONT, GL_SPECULAR, Specular.ToFloatArray());
    //glMaterialf(GL_FRONT, GL_SHININESS, Shininess);

    if (Textures.size() > 0){
        Texture* texture = Textures[0];
        
        texture->Active();
    }else{
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}