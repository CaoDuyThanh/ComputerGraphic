#ifndef FBXREADER_H
#define FBXREADER_H
#include <fstream>
#include <iostream>
#include <string>
#include "../../Model/Model.h"
#include "../../../../Exception/Exception.h"
#include "../../../../Utils/FBXSdk2015/include/fbxsdk.h"
#include "../../../../Utils/Log/log.h"

using namespace std;

/*
    This class will load the FBX file based on FBX SDK library.
*/
class FBXReader{
public:
    string FileName;

public:
    FBXReader();
    FBXReader(string fileName);
    Model* LoadModel();

private:
    void initializeSdkObjects(FbxManager*& fbxManager, FbxScene*& scene);
    bool loadScene(FbxManager* fbxManager, FbxDocument* scene, string fileName);
    void transferDataFromSceneToModel(FbxScene * scene, Model* &model);
    bool transferData(FbxNode* node, Node* modelNode);    
};

#endif