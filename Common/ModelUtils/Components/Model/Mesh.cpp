#include "Mesh.h"

Mesh::Mesh():
    NumVerts(0),
    NumNormals(0),
    NumCoordinates(0),
    NumFaces(0),

    VBO(0),
    NBO(0),
    CoorBO(0),
    IBO(0),
    NBODisplay(0),
    
    Vertices(NULL),
    Normals(NULL),
    UV(NULL),
    Faces(NULL)
{
    // Do nothing
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::InitBuffer(){
    // Release all resource before initialize new data
    releaseBuffer();

    Vector3s* vertices = new Vector3s[NumFaces * 3];
    Vector3s* normals = new Vector3s[NumFaces * 3];
    Vector2s* uv = new Vector2s[NumFaces * 3];
    unsigned int* indices = new unsigned int[NumFaces * 3];
    
    int count = 0;
    for (int faceId = 0; faceId < NumFaces; faceId++){
        ITriangle face = Faces[faceId];
        
        Vector3s P1 = Vertices[face.Point1Id];
        Vector3s P2 = Vertices[face.Point2Id];
        Vector3s P3 = Vertices[face.Point3Id];

        Vector3s N1 = Normals[face.Point1Id];
        Vector3s N2 = Normals[face.Point2Id];
        Vector3s N3 = Normals[face.Point3Id];

        Vector2s UV1 = UV[face.UV1Id];
        Vector2s UV2 = UV[face.UV2Id];
        Vector2s UV3 = UV[face.UV3Id];

        vertices[count * 3 + 0] = P1;
        vertices[count * 3 + 1] = P2;
        vertices[count * 3 + 2] = P3;

        normals[count * 3 + 0] = N1;
        normals[count * 3 + 1] = N2;
        normals[count * 3 + 2] = N3;

        uv[count * 3 + 0] = UV1;
        uv[count * 3 + 1] = UV2;
        uv[count * 3 + 2] = UV3;

        indices[count * 3 + 0] = count * 3 + 0;
        indices[count * 3 + 1] = count * 3 + 1;
        indices[count * 3 + 2] = count * 3 + 2;

        count++;
    }

    // Create Vertex Buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, NumFaces * 3 * sizeof(Vector3s), (double*)vertices, GL_STATIC_DRAW);

    // Create Normal Buffer
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, NumFaces * 3 * sizeof(Vector3s), (double*)normals, GL_STATIC_DRAW);

    // Create Coordinate Buffer
    glGenBuffers(1, &CoorBO);
    glBindBuffer(GL_ARRAY_BUFFER, CoorBO);
    glBufferData(GL_ARRAY_BUFFER, NumFaces * 3 * sizeof(Vector2s), (double*)uv, GL_STATIC_DRAW);
    
    // Create Normal Buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumFaces * 3 * sizeof(unsigned int), (unsigned int*)indices, GL_STATIC_DRAW);

    Vector3s* normalsDisplay = new Vector3s[NumVerts * 2];
    unsigned int* indicesNormalDisplay = new unsigned int[NumVerts * 2];
    for (int vertId = 0; vertId < NumVerts; vertId++){
        normalsDisplay[vertId * 2 + 0] = Vertices[vertId];
        normalsDisplay[vertId * 2 + 1] = Vertices[vertId] + Normals[vertId];
        indicesNormalDisplay[vertId * 2 + 0] = vertId * 2 + 0;
        indicesNormalDisplay[vertId * 2 + 1] = vertId * 2 + 1;
    }
    // Create Normal Buffer for Display Normal
    glGenBuffers(1, &NBODisplay);
    glBindBuffer(GL_ARRAY_BUFFER, NBODisplay);
    glBufferData(GL_ARRAY_BUFFER, NumVerts * 2 * sizeof(Vector3s), (double*)normalsDisplay, GL_STATIC_DRAW);

    // Create Indices Buffer for Display Normal
    glGenBuffers(1, &INBODisplay);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INBODisplay);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumVerts * 2 * sizeof(unsigned int), (unsigned int*)indicesNormalDisplay, GL_STATIC_DRAW);

    delete vertices;
    delete normals;
    delete uv;
    delete indices;
    delete normalsDisplay;
    delete indicesNormalDisplay;
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::InitData(){
    releaseData();

    NumNormals = NumCoordinates = NumVerts;
    //AddPosition = AddNormal = AddCoordinate = 0;
    Vertices = new Vector3s[NumVerts];
    Normals = new Vector3s[NumNormals];
    UV = new Vector2s[NumCoordinates];
    Faces = new ITriangle[NumFaces];
}
//-------------------------------------------------------------------------------------------------------------
bool Mesh::InitEmptyVertices(unsigned int numVerts){
    if (numVerts == 0){
        LOG_WARNING << "Can not initilize an array with 0 elements!";
        return false;
    }

    NumVerts = numVerts;
    Vertices = new Vector3s[NumVerts];

    return true;
}
//-------------------------------------------------------------------------------------------------------------
bool Mesh::InitEmptyNormals(unsigned int numNormals){
    if (numNormals == 0){
        LOG_WARNING << "Can not initilize an array with 0 elements!";
        return false;
    }

    NumNormals = numNormals;
    Normals = new Vector3s[numNormals];

    return true;
}
//-------------------------------------------------------------------------------------------------------------
bool Mesh::InitEmptyCoordinates(unsigned int numCoordinates){
    if (numCoordinates == 0){
        LOG_WARNING << "Can not initilize an array with 0 elements!";
        return false;
    }

    NumCoordinates = numCoordinates;
    UV = new Vector2s[NumCoordinates];

    return true;
}
//-------------------------------------------------------------------------------------------------------------
bool Mesh::InitEmptyFaces(unsigned int numFaces){
    if (numFaces == 0){
        LOG_WARNING << "Can not initilize an array with 0 elements!";
        return false;
    }

    NumFaces = numFaces;
    Faces = new ITriangle[NumFaces];

    return true;
}
//-------------------------------------------------------------------------------------------------------------
bool Mesh::Push_back(MeshType type, Object* object){
    switch (type){
    case MeshType::VERTICLE:
        Vertices[currentAddedPosition] = *(static_cast<Vector3s*>(object));
        currentAddedPosition++;
        if (currentAddedPosition >= NumVerts) return false;
    break;
    case MeshType::NORMAL:	
        Normals[currentAddedNormal] = *(static_cast<Vector3s*>(object));
        currentAddedNormal++;
        if (currentAddedNormal >= NumNormals) return false;
    break;
    case MeshType::COORDINATE:
        UV[currentAddedCoordinate] = *(static_cast<Vector2s*>(object)); 
        currentAddedCoordinate++;
        if (currentAddedCoordinate >= NumCoordinates) return false;
    break;
    case MeshType::FACE:
        Faces[currentAddedFace] = *(static_cast<ITriangle*>(object));
        currentAddedFace++;
        if (currentAddedFace >= NumFaces) return false;
    default:		break;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::Draw(){
    beginDraw();

    //setMaterial();
    glDrawElements(GL_TRIANGLES, NumFaces * 3, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(0));

    endDraw();
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::DisplayNormal(){
    // Set vertex position array.
    glBindBuffer(GL_ARRAY_BUFFER, NBODisplay);
    glVertexPointer(sizeof(Vector3s) / sizeof(double), GL_DOUBLE, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INBODisplay);
    glDrawElements(GL_LINES, NumVerts * 2, GL_UNSIGNED_INT, reinterpret_cast<const GLvoid *>(0));


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//- Private functions -----------------------------------------------------------------------------------------
void Mesh::beginDraw(){
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    glPushAttrib(GL_ENABLE_BIT);
    glPushAttrib(GL_CURRENT_BIT);
    glPushAttrib(GL_LIGHTING_BIT);
    glPushAttrib(GL_TEXTURE_BIT);

    // Set vertex position array.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexPointer(sizeof(Vector3s) / sizeof(double), GL_DOUBLE, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Set normal array.
    if (Normals)
    {
        glBindBuffer(GL_ARRAY_BUFFER, NBO);
        glNormalPointer(GL_DOUBLE, 0, 0);
        glEnableClientState(GL_NORMAL_ARRAY);
    }

    // Set UV array.
    if (UV)
    {
        glBindBuffer(GL_ARRAY_BUFFER, CoorBO);
        glTexCoordPointer(sizeof(Vector2s) / sizeof(double), GL_DOUBLE, 0, 0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    // Set index array.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::endDraw(){
    // Reset VBO binding.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Pop OpenGL attributes.
    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
    glPopAttrib();
    glPopClientAttrib();
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::setMaterial(){
    if (Materials.size() > 0){

        Material* material = Materials[0];

        material->Active();
    }
    else{
        // Set default material
        const GLfloat BLACK_COLOR[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat GREEN_COLOR[] = { 0.0f, 1.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, BLACK_COLOR);
        glMaterialfv(GL_FRONT, GL_AMBIENT, BLACK_COLOR);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN_COLOR);
        glMaterialfv(GL_FRONT, GL_SPECULAR, BLACK_COLOR);
        glMaterialf(GL_FRONT, GL_SHININESS, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::releaseBuffer(){
    if (VBO) glDeleteBuffers(1, &VBO);
    if (NBO) glDeleteBuffers(1, &NBO);
    if (CoorBO) glDeleteBuffers(1, &CoorBO);
    if (IBO) glDeleteBuffers(1, &IBO);

    VBO = NBO = CoorBO = IBO = 0;
}
//-------------------------------------------------------------------------------------------------------------
void Mesh::releaseData(){
    currentAddedPosition = currentAddedNormal = currentAddedCoordinate = currentAddedFace = 0;
    NumVerts = NumNormals = NumCoordinates = NumFaces = 0;

    if (Vertices) delete(Vertices);
    if (Normals) delete(Normals);
    if (UV) delete(UV);
    if (Faces) delete(Faces);

    Vertices = NULL;
    Normals = NULL;
    UV = NULL;
    Faces = NULL;
}