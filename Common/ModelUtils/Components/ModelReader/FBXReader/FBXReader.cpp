#include "FBXReader.h"

// CONSTRUCTOR  -----------------------------------------------------------------------------------------------------------------------------
FBXReader::FBXReader():
FileName("")
{
    // Do nothing
}

FBXReader::FBXReader(string fileName) :
FileName(fileName)
{
    // Do nothing
}

//-------------------------------------------------------------------------------------------------------------------------------------------
Model* FBXReader::LoadModel(){
    // Check blank file name
    if (FileName == ""){
        throw Exception("Filename could not be blank");
    }

    // Check file exists  
    std::ifstream file(FileName.c_str());
    if (!file.good()){
        throw Exception("File does not exist or access (please check if current file is used by another program !");
    }

    FbxManager* sdkManager = NULL;
    FbxScene* scene = NULL;
    bool loadSceneResult;
    initializeSdkObjects(sdkManager, scene);
    loadSceneResult = loadScene(sdkManager, scene, FileName);

    Model* fbxModel = NULL;
    if (loadSceneResult == false){
        throw Exception("An error occurred while loading the scene...");
    }
    else{
        transferDataFromSceneToModel(scene, fbxModel);
    }  
    
    LOG_DEBUG << "Load model successfully! " << "File's name: " << FileName;
    return fbxModel;
}

//- LOCAL FUNCTIONS - ABSTRACT --------------------------------------------------------------------------------------------------------------
void transferMesh(FbxMesh* fbxMesh, Mesh* mesh);
void transferVertices(FbxMesh* fbxMesh, Mesh* mesh);
void transferNormals(FbxMesh* fbxMesh, Mesh* mesh);
void transferPolygons(FbxMesh* fbxMesh, Mesh* mesh);
void transferMaterials(FbxGeometry* fbxMesh, Mesh* mesh);
void transferTextures(FbxGeometry* fbxMesh, Mesh* mesh);
void transferGeometricTransformation(FbxNode* fbxNode, Node* node);

// PRIVATE FUNCTION--------------------------------------------------------------------------------------------------------------------------
void FBXReader::initializeSdkObjects(FbxManager*& fbxManager, FbxScene*& scene)
{
    //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    fbxManager = FbxManager::Create();
    if (!fbxManager)
    {
        FBXSDK_printf("Error: Unable to create FBX Manager!\n");
        exit(1);
    }
    else FBXSDK_printf("Autodesk FBX SDK version %s\n", fbxManager->GetVersion());

    //Create an IOSettings object. This object holds all import/export settings.
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);

    //Load plugins from the executable directory (optional)
    FbxString lPath = FbxGetApplicationDirectory();
    fbxManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    scene = FbxScene::Create(fbxManager, "My Scene");
    if (!scene)
    {
        FBXSDK_printf("Error: Unable to create FBX scene!\n");
        exit(1);
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
#ifdef IOS_REF
    #undef  IOS_REF
    #define IOS_REF (*(fbxManager->GetIOSettings()))
#endif
bool FBXReader::loadScene(FbxManager* fbxManager, FbxDocument* scene, string fileName)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor, lSDKMinor, lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;
    char lPassword[1024];

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(fbxManager, "");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(fileName.c_str(), -1, fbxManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if (!lImportStatus)
    {
        FbxString error = lImporter->GetStatus().GetErrorString();
        FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

        if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
        {
            FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
            FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", fileName, lFileMajor, lFileMinor, lFileRevision);
        }

        return false;
    }

    FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

    if (lImporter->IsFBX())
    {
        FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", fileName, lFileMajor, lFileMinor, lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        FBXSDK_printf("Animation Stack Information\n");

        lAnimStackCount = lImporter->GetAnimStackCount();

        FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
        FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
        FBXSDK_printf("\n");

        for (i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            FBXSDK_printf("    Animation Stack %d\n", i);
            FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
            FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported 
            // under a different name.
            FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported. 
            FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
            FBXSDK_printf("\n");
        }

        // Set the import states. By default, the import states are always set to 
        // true. The code below shows how to change these states.
        IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
        IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
        IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
        IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
        IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
        IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
        IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    lStatus = lImporter->Import(scene);

    if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
    {
        FBXSDK_printf("Please enter password: ");

        lPassword[0] = '\0';

        FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
            scanf("%s", lPassword);
        FBXSDK_CRT_SECURE_NO_WARNING_END

            FbxString lString(lPassword);

        IOS_REF.SetStringProp(IMP_FBX_PASSWORD, lString);
        IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

        lStatus = lImporter->Import(scene);

        if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
        {
            FBXSDK_printf("\nPassword is wrong, import aborted.\n");
        }
    }

    // Destroy the importer.
    lImporter->Destroy();

    return lStatus;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void FBXReader::transferDataFromSceneToModel(FbxScene* scene, Model* &model){
    model = new Model();
    LOG_DEBUG << "Start transferring data from scene to model...";

    FbxNode* rootNode = scene->GetRootNode();
    model->InitRootNode();
    Node* rootModelNode = model->RootNode;
    for (int i = 0; i < rootNode->GetChildCount(); i++)
    {
        Node* newNode = new Node();
        if (transferData(rootNode->GetChild(i), newNode)){
            rootModelNode->Children.push_back(newNode);
            rootModelNode->NumChildren = rootModelNode->Children.size();
        }
    }

    LOG_DEBUG << "Finish traferring data from scene to model !";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
bool FBXReader::transferData(FbxNode* node, Node* modelNode){
    if (node == NULL){
        throw new Exception("node is NULL!");
    }

    if (modelNode == NULL){        
        throw new Exception("modelNode is NULL!");
    }    

    modelNode->NodeName = node->GetName();

    FbxNodeAttribute::EType nodeAttributeType = node->GetNodeAttribute()->GetAttributeType();
    FbxMesh* fbxMesh = (FbxMesh*)node->GetNodeAttribute();
    Mesh* newMesh = NULL;
    switch (nodeAttributeType){
    case FbxNodeAttribute::eMarker:
        // Do nothing
        break;
    case FbxNodeAttribute::eSkeleton:
        // Do nothing
        break;
    case FbxNodeAttribute::eMesh:            
            newMesh = new Mesh();
            transferMesh(fbxMesh, newMesh);
            modelNode->Meshes.push_back(newMesh);
            modelNode->NumMeshes = modelNode->Meshes.size();
        break;
    case FbxNodeAttribute::eNurbs:
        // Do nothing
        break;
    case FbxNodeAttribute::ePatch:
        // Do nothing
        break;
    case FbxNodeAttribute::eCamera:
        // Do nothing
        break;
    case FbxNodeAttribute::eLight:
        // Do nothing
        break;
    case FbxNodeAttribute::eLODGroup:
        // Do nothing
        break;
    default: LOG_WARNING << "Can not identify the type of this mesh !";
        break;
    }

    // Read geometric transformation
    transferGeometricTransformation(node, modelNode);

    LOG_DEBUG << "Transfer data successfully! " << "Node's name: " << modelNode->NodeName;

    for (int i = 0; i < node->GetChildCount(); i++)
    {
        Node* newNode = new Node();
        if (transferData(node->GetChild(i), newNode)){
            modelNode->Children.push_back(newNode);
            modelNode->NumChildren = modelNode->Children.size();
        }
    }

    if (modelNode->NumChildren == 0 && modelNode->NumMeshes == 0){
        return false;
    }

    return true;
}

//- LOCAL FUNCTIONS - IMPLEMENTATION --------------------------------------------------------------------------------------------------------
void transferMesh(FbxMesh* fbxMesh, Mesh* mesh){
    transferVertices(fbxMesh, mesh);
    transferNormals(fbxMesh, mesh);
    transferPolygons(fbxMesh, mesh);
    transferMaterials(fbxMesh, mesh);
    transferTextures(fbxMesh, mesh);

    LOG_DEBUG << "Transfer mesh successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferVertices(FbxMesh* fbxMesh, Mesh* mesh){
    int numVertices = fbxMesh->GetControlPointsCount();
    FbxVector4* vertices = fbxMesh->GetControlPoints();

    mesh->InitEmptyVertices(numVertices);
    for (int i = 0; i < numVertices; i++){
        FbxVector4 vertex = vertices[i];
        mesh->Push_back(Mesh::MeshType::VERTICLE, &Vector3s((double)vertex[0], (double)vertex[1], (double)vertex[2]));
    }

    LOG_DEBUG << "Transfer vertices successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferNormals(FbxMesh* fbxMesh, Mesh* mesh){
    int numVertices = fbxMesh->GetControlPointsCount();
    FbxGeometryElementNormal* normals = fbxMesh->GetElementNormal(0);

    mesh->InitEmptyNormals(numVertices);
    for (int i = 0; i < numVertices; i++){
        FbxVector4 normal = normals->GetDirectArray().GetAt(i);
        mesh->Push_back(Mesh::MeshType::NORMAL, &Vector3s((double)normal[0], (double)normal[1], (double)normal[2]));
    }

    LOG_DEBUG << "Transfer normals successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferPolygons(FbxMesh* fbxMesh, Mesh* mesh){
    // Transfer all UV array in fbxMesh to mesh
    int uvSize = fbxMesh->GetElementUV(0)->GetDirectArray().GetCount();
    mesh->InitEmptyCoordinates(uvSize);
    for (int uvId = 0; uvId < uvSize; uvId++){
        FbxVector2 uv = fbxMesh->GetElementUV(0)->GetDirectArray().GetAt(uvId);
            mesh->Push_back(Mesh::MeshType::COORDINATE, &Vector2s((double)uv[0], (double)uv[1]));
    }

    int polygonSize = fbxMesh->GetPolygonCount();
    mesh->InitEmptyFaces(polygonSize);
    for (int polyId = 0; polyId < polygonSize; polyId++){
        vector<int> triangle;   triangle.clear();

        int polyNumPoints = fbxMesh->GetPolygonSize(polyId);
        for (int pointId = 0; pointId < polyNumPoints; pointId++){
            // Add Vertex index of current point (in polygon)
            int vertexId = fbxMesh->GetPolygonVertex(polyId, pointId);
            triangle.push_back(vertexId);

            // Add UV index of current point (in polygon)
            int uvId = fbxMesh->GetTextureUVIndex(polyId, pointId);            
            triangle.push_back(uvId);
        }

        mesh->Push_back(Mesh::MeshType::FACE, &ITriangle(triangle[0], triangle[2], triangle[4],
                                                         triangle[1], triangle[3], triangle[5]));
    }

    LOG_DEBUG << "Transfer polygons (triangle mode) successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferMaterials(FbxGeometry* fbxMesh, Mesh* mesh){
    int numMaterials = 0;
    if (fbxMesh == NULL){
        throw new Exception("fbxMesh can not be NULL !");
    }

    FbxNode* fbxNode = NULL;
    fbxNode = fbxMesh->GetNode();
    if (fbxNode){
        numMaterials = fbxNode->GetMaterialCount();
    }

    LOG_DEBUG << "   Number of materials: " << numMaterials;

    if (numMaterials > 0)
    {
        FbxPropertyT<FbxDouble3> lKFbxDouble3;
        FbxPropertyT<FbxDouble> lKFbxDouble1;
        FbxColor theColor;

        for (int matId = 0; matId < numMaterials; matId++){
            Material* material = new Material();

            FbxSurfaceMaterial* fbxMaterial = fbxNode->GetMaterial(matId);

            // Get the implementation to see f it's a hardware shader
            const FbxImplementation* fbxImplementation = GetImplementation(fbxMaterial, FBXSDK_IMPLEMENTATION_HLSL);
            string fbxImplementationType = "HLSL";
            if (fbxImplementation != NULL){
                fbxImplementation = GetImplementation(fbxMaterial, FBXSDK_IMPLEMENTATION_CGFX);
                fbxImplementationType = "CFGX";
            }

            if (fbxImplementation)
            {
                // Handle hardware shader
                // TODO: transfer material using hardware shader
            }
            else if (fbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
            {
                // Handle phong shader

                // Transfer Ambient color
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Ambient;
                material->Ambient = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Transfer Diffuse color
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Diffuse;
                material->Diffuse = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Transfer Specular color
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Specular;
                material->Specular = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Transfer Emissive color
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Emissive;
                material->Emissive = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Transfer Transperency factor
                lKFbxDouble1 = ((FbxSurfacePhong*)fbxMaterial)->TransparencyFactor;
                material->Opacity = 1.0 - lKFbxDouble1.Get();

                // Transfer Shininess
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->Shininess;
                material->Shininess = lKFbxDouble1.Get();
                
                // Transfer Reflectivity
                lKFbxDouble3 = ((FbxSurfacePhong*)fbxMaterial)->ReflectionFactor;
                material->Reflectivity = lKFbxDouble1.Get();
            }
            else if (fbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
            {
                // Handle Lambert shader
                lKFbxDouble3 = ((FbxSurfaceLambert *)fbxMaterial)->Ambient;
                material->Ambient = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Display the Diffuse Color
                lKFbxDouble3 = ((FbxSurfaceLambert *)fbxMaterial)->Diffuse;
                material->Diffuse = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Display the Emissive
                lKFbxDouble3 = ((FbxSurfaceLambert *)fbxMaterial)->Emissive;
                material->Emissive = Vector4s(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2], 1);

                // Display the Opacity
                lKFbxDouble1 = ((FbxSurfaceLambert *)fbxMaterial)->TransparencyFactor;
                material->Opacity = 1.0 - lKFbxDouble1.Get();
            }
            else
            {
                LOG_WARNING << "Unknown type of Material !";
            }

            FbxPropertyT<FbxString> fbxString;
            fbxString = fbxMaterial->ShadingModel;
            material->ShadingMode = fbxString.Get();

            mesh->Materials.push_back(material);
        }
    }

    LOG_DEBUG << "Transfer materials successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
Image* loadImage(string fileName, hash_map<string, Image*> *images){
    Image* image = NULL;

    image = (*images)[fileName];
    if (image == NULL){
        image = new Image(fileName);
        image->LoadImageW();
        (*images)[fileName] = image;
    }

    return image;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferTextureInfo(FbxTexture* texture, int blendMode, Texture* modelTexture){
    FbxFileTexture* fileTexture = FbxCast<FbxFileTexture>(texture);
    FbxProceduralTexture* proceduralTexture = FbxCast<FbxProceduralTexture>(texture);

    modelTexture->TextureName = texture->GetName();
    if (fileTexture){
        Image* image = loadImage(fileTexture->GetFileName(), &Texture::Images);
        modelTexture->Image = image;
    }
    else if (proceduralTexture){
        LOG_WARNING << "Procedural texture ! "
                    << "Texture name: " << modelTexture->TextureName;
    }

    modelTexture->ScaleU = texture->GetScaleU();
    modelTexture->ScaleV = texture->GetScaleV();
    modelTexture->TranslateU = texture->GetTranslationU();
    modelTexture->TranslateV = texture->GetTranslationV();
    modelTexture->IsSwapUV = texture->GetSwapUV();
    modelTexture->RotateU = texture->GetRotationU();
    modelTexture->RotateV = texture->GetRotationV();
    modelTexture->RotateW = texture->GetRotationW();

    const char* lAlphaSources[] = { "None", "RGB Intensity", "Black" };
    modelTexture->AlphaSource = lAlphaSources[texture->GetAlphaSource()];
    modelTexture->CropLeft = texture->GetCroppingLeft();
    modelTexture->CropRight = texture->GetCroppingRight();
    modelTexture->CropTop = texture->GetCroppingTop();
    modelTexture->CropBottom = texture->GetCroppingBottom();

    const char* lMappingTypes[] = { "Null", "Planar", "Spherical", "Cylindrical",
                                    "Box", "Face", "UV", "Environment" };
    modelTexture->MappingType = lMappingTypes[texture->GetMappingType()];

    const char* lBlendModes[] = { "Translucent", "Add", "Modulate", "Modulate2" };
    if (blendMode >= 0){
        modelTexture->BlendMode = lBlendModes[blendMode];
    }
    modelTexture->Alpha = texture->GetDefaultAlpha();

    if (fileTexture){
        const char* lMaterialUses[] = { "Model Material", "Default Material" };
        modelTexture->MaterialUsed = lMaterialUses[fileTexture->GetMaterialUse()];
    }

    const char* pTextureUses[] = { "Standard", "Shadow Map", "Light Map",
                                   "Spherical Reflexion Map", "Sphere Reflexion Map", "Bump Normal Map" };
    modelTexture->TextureUsed = pTextureUses[texture->GetTextureUse()];

    LOG_INFO << "Texture information: \n" << modelTexture->ToString();

    LOG_DEBUG << "Read texture successfully!";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferTextureByProperty(FbxProperty fbxProperty, int matId, Material* modelMaterial){
    if (fbxProperty.IsValid()){
        int textureCount = fbxProperty.GetSrcObjectCount<FbxTexture>();

        for (int texId = 0; texId < textureCount; texId++){
            FbxLayeredTexture* layeredTexture = fbxProperty.GetSrcObject<FbxLayeredTexture>(texId);
            if (layeredTexture){
                int numTexture = layeredTexture->GetSrcObjectCount<FbxTexture>();
                for (int k = 0; k < numTexture; k++){
                    FbxTexture* texture = layeredTexture->GetSrcObject<FbxTexture>(k);
                    if (texture){
                        LOG_DEBUG << "   Textures connected to material " << matId;

                        Texture* modelTexture = new Texture();
                        FbxLayeredTexture::EBlendMode blendMode;
                        layeredTexture->GetTextureBlendMode(k, blendMode);
                        transferTextureInfo(texture, (int)blendMode, modelTexture);
                        modelMaterial->Textures.push_back(modelTexture);
                    }
                }
            }
            else
            {
                // There is no layered texture
                FbxTexture* texture = fbxProperty.GetSrcObject<FbxTexture>(texId);
                if (texture){
                    LOG_DEBUG << "   Textures connected to material " << matId;

                    Texture* modelTexture = new Texture();
                    transferTextureInfo(texture, -1, modelTexture);
                    modelMaterial->Textures.push_back(modelTexture);
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferTextures(FbxGeometry* fbxMesh, Mesh* mesh)
{
    FbxNode* fbxNode = fbxMesh->GetNode();
    FbxProperty fbxProperty;
    int numMaterials = fbxNode->GetSrcObjectCount<FbxSurfaceMaterial>();
    for (int matId = 0; matId < numMaterials; matId++){
        FbxSurfaceMaterial* fbxMaterial = fbxNode->GetSrcObject<FbxSurfaceMaterial>(matId);
        Material* modelMaterial = mesh->Materials[matId];

        if (fbxMaterial){
            // Go through all the possible textures
            for (int layerId = 0; layerId < FbxLayerElement::sTypeTextureCount; layerId++){
                fbxProperty = fbxMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[layerId]);
                transferTextureByProperty(fbxProperty, matId, modelMaterial);
            }
        }
    }


    LOG_DEBUG << "Transfer materials successfully! ";
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void transferGeometricTransformation(FbxNode* fbxNode, Node* node){
    FbxVector4 vector4;

    vector4 = fbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    node->Translate = Vector3s((double)vector4[0], (double)vector4[1], (double)vector4[2]);

    vector4 = fbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
    node->Rotate = Vector3s((double)vector4[0], (double)vector4[1], (double)vector4[2]);

    vector4 = fbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
    node->Scale = Vector3s((double)vector4[0], (double)vector4[1], (double)vector4[2]);

    FbxAMatrix globalTransform = fbxNode->EvaluateGlobalTransform(0);
    const double* flatArray = (const double*)globalTransform;
    node->Transformation = Matrix4x4s(flatArray[0],  flatArray[1],  flatArray[2],  flatArray[3],
                                      flatArray[4],  flatArray[5],  flatArray[6],  flatArray[7],
                                      flatArray[8],  flatArray[9],  flatArray[10], flatArray[11],
                                      flatArray[12], flatArray[13], flatArray[14], flatArray[15]);
}