#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <string>
#include "../../../Utils/SOIL/SOIL.h"
#include "../../../Utils/Log/log.h"
using namespace std;

class Image{
public:
    string FileName;
    unsigned int BufferId;

public:
    Image();
    Image(string fileName);

    void LoadImage();
};

#endif