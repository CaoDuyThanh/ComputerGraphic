#include "Image.h"

// - Constructor --------------------------------------------------------------------------------------
Image::Image():
FileName(""),
BufferId(0)
{
    // Do nothing
}
Image::Image(string fileName) :
FileName(fileName),
BufferId(0)
{
    // Do nothing
}

// ----------------------------------------------------------------------------------------------------
void Image::LoadImage(){
    LOG_DEBUG << "Load image..." << "\n"
        << "      File's name : " << FileName;

    BufferId = SOIL_load_OGL_texture(
        FileName.data(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    if (BufferId == 0){
        LOG_WARNING << "Error while loading image: " << SOIL_last_result();
    }

    LOG_DEBUG << "Load image completed ! ";
}