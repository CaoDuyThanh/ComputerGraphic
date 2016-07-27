#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include "Node.h"
#include "../../../Utils/Log/log.h"

class Model{
public:
    std::string FilePath;
    std::string NameModel;
    
    Node* RootNode;    
public:
    Model();
    ~Model();
    
    void InitRootNode();
    Node* GetNode(std::string NodeName);
    void Draw();
    void DisplayNormal();
    void InitBuffer();

private:
    void deleteRootNode();
    /*
    void createSizeMaterial();
    Texture* findTexture(std::string);
    void buildBuffer();

    void push_back(Mesh* mesh);
    void push_back(Texture* texture);

    void drawModel(Shader* shader, float rotx);*/
};
#endif