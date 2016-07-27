#include "Node.h"

//- CONSTRUCTOR ---------------------------------------------------------------------------------------------
Node::Node() :
NodeName(""),
NumChildren(0),
NumMeshes(0),
Transformation(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1),
Children(NULL),
Meshes(NULL),
Parent(NULL),
Translate(Vector3s(0, 0, 0)),
Rotate(Vector3s(0, 0, 0)),
Scale(Vector3s(1, 1, 1))
{
}
//- DESTRUCTOR ------------------------------------------------------------------------------------------------
Node::~Node(){
    deleteMeshes();

    LOG_DEBUG << "Delete node successfully !" << " Node's name : " << NodeName;
}
//-------------------------------------------------------------------------------------------------------------
bool Node::InitEmptyMeshes(unsigned int numMeshes){
    if (numMeshes == 0){
        LOG_WARNING << "Initilize an empty meshes array with 0 element !";
        return false;
    }

    deleteMeshes();
    NumMeshes = numMeshes;
    Meshes.resize(NumMeshes);

    LOG_DEBUG << "Create an empty meshes! " << "NumMeshes: " << NumMeshes;
    return true;
}
// ------------------------------------------------------------------------------------------------------------------------------
bool Node::InitEmptyChildren(unsigned int numChildren){
    if (numChildren == 0){
        LOG_WARNING << "Initialize an empty children array with 0 elements";

        return false;
    }

    deleteChildren();
    NumChildren = numChildren;
    Children.resize(NumChildren);

    LOG_DEBUG << "Create an empty children! " << "NumChildren: " << NumChildren;
    return true;
}
// ------------------------------------------------------------------------------------------------------------------------------
Node* Node::GetNode(std::string nodeName){
    if (NodeName == nodeName)
        return this;
    for (int i = 0; i < NumChildren; i++){
        Node* getNode = Children[i]->GetNode(nodeName);
        if (getNode != NULL)
            return getNode;
    }
    return NULL;
}
//-------------------------------------------------------------------------------------------------------------
void Node::InitBuffer(){
    for (int meshId = 0; meshId < NumMeshes; meshId++){
        Meshes[meshId]->InitBuffer();
    }

    for (int childId = 0; childId < NumChildren; childId++){
        Children[childId]->InitBuffer();
    }
}
//-------------------------------------------------------------------------------------------------------------
void Node::Draw(bool isDraw){
    if (NodeName == "wheel_front_Lt")
        isDraw = true;
    if (isDraw)
    for (int meshId = 0; meshId < NumMeshes; meshId++){
        glPushMatrix();
        glScaled(30, 30, 30);
        glMultMatrixd((const double*)&(Transformation));

        Meshes[meshId]->Draw();
/*
        glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
        glPushAttrib(GL_ENABLE_BIT);
        glPushAttrib(GL_CURRENT_BIT);
        glPushAttrib(GL_LIGHTING_BIT);
        glPushAttrib(GL_TEXTURE_BIT);

        glColor3d(0, 0, 0);
        glBegin(GL_TRIANGLES);
        Mesh* mesh = Meshes[meshId];
        for (int faceId = 0; faceId < mesh->NumFaces; faceId++){
            ITriangle face = mesh->Faces[faceId];

            Vector3s P1 = mesh->Vertices[face.Point1Id];
            Vector3s P2 = mesh->Vertices[face.Point2Id];
            Vector3s P3 = mesh->Vertices[face.Point3Id];

            glVertex3d(P1.X, P1.Y, P1.Z);
            glVertex3d(P2.X, P2.Y, P2.Z);
            glVertex3d(P3.X, P3.Y, P3.Z);
        }
        glEnd();

        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_NORMALIZE);
*/
        glPopMatrix();
    }

    for (int childId = 0; childId < NumChildren; childId++){
        Children[childId]->Draw(isDraw);
    }
}
//-------------------------------------------------------------------------------------------------------------
void Node::DisplayNormal(){
    for (int meshId = 0; meshId < NumMeshes; meshId++){
        glPushMatrix();
        glScaled(30, 30, 30);
        glMultMatrixd((const double*)&(Transformation));

        Meshes[meshId]->DisplayNormal();

        glPopMatrix();
    }

    for (int childId = 0; childId < NumChildren; childId++){
        Children[childId]->DisplayNormal();
    }
}
//-------------------------------------------------------------------------------------------------------------

// - PRIVATE FUNCTIONS ----------------------------------------------------------------------------------------------------------
void Node::deleteMeshes(){
    for (int meshId = 0; meshId < NumMeshes; meshId++){
        if (Meshes[meshId] != NULL) delete Meshes[meshId];
    }
    Meshes.clear();
    NumMeshes = 0;

    LOG_DEBUG << "Delete meshes successfully";
}
// ------------------------------------------------------------------------------------------------------------------------------
void Node::deleteChildren(){
    for (int childId = 0; childId < NumChildren; childId++){
        if (Children[childId] != NULL){ delete Children[childId]; }
    }
    Children.clear();
    NumChildren = 0;

    LOG_DEBUG << "Delete children successfully";
}
/*void Node::setTransformation(aiMatrix4x4 Trans){
    mTransformation = Matrix4x4s(Trans.a1, Trans.a2, Trans.a3, Trans.a4,
        Trans.b1, Trans.b2, Trans.b3, Trans.b4,
        Trans.c1, Trans.c2, Trans.c3, Trans.c4,
        Trans.d1, Trans.d2, Trans.d3, Trans.d4);
}

*/

