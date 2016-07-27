#include "Model.h"

// - CONSTRUCTOR ---------------------------------------------------------------------------------------------------------------
Model::Model():
    FilePath(""),
    NameModel("")        
{
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::InitRootNode(){
    if (RootNode != NULL) delete(RootNode);
    RootNode = new Node();
}
// ------------------------------------------------------------------------------------------------------------------------------
Node* Model::GetNode(std::string nodeName){
    return RootNode->GetNode(nodeName);
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::Draw(){
    if (RootNode == NULL){
        throw new Exception("Can not draw an model before loading it !");
    }

    RootNode->Draw(true);
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::DisplayNormal(){
    if (RootNode == NULL){
        throw new Exception("Can not draw an model before loading it !");
    }

    RootNode->DisplayNormal();
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::InitBuffer(){
    RootNode->InitBuffer();
}
// ------------------------------------------------------------------------------------------------------------------------------
Model::~Model(){
    deleteRootNode();

    LOG_DEBUG << "Delete model successfully !" << " Model's name : " << NameModel;
}

// - PRIVATE FUNCTIONS ----------------------------------------------------------------------------------------------------------
void Model::deleteRootNode(){
    if (RootNode != NULL) delete RootNode;
    LOG_DEBUG << "Delete root node successfully !";
}












/*void Model::createSizeMaterial(){
    mMaterials = new Material[mNumMaterials];
}
// ------------------------------------------------------------------------------------------------------------------------------
Texture* Model::findTexture(std::string Path){
	// Find Texture from data has been loaded before
	for (int i = 0; i < mNumTextures; i++){
		if (mTextures[i]->getDiffusePath() == Path)
			return mTextures[i];
	}

	// Else load new Texture and add into mTextures
	Texture* newTexture = new Texture();
	newTexture->setDiffusePath(Path);
	newTexture->loadTexture();
	push_back(newTexture);

	return newTexture;
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::buildBuffer(){
	for (int i = 0; i < mNumMeshes; i++){
		mMeshes[i]->InitBuffer();
	}
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::push_back(Mesh* mesh){
	mNumMeshes++;
	Mesh** newmMeshes;
	newmMeshes = new Mesh*[mNumMeshes];
	newmMeshes[mNumMeshes - 1] = mesh;
	if (mMeshes != NULL){
		for (int i = 0; i < mNumMeshes - 1; i++)
			newmMeshes[i] = mMeshes[i];
	}

	delete mMeshes;
	mMeshes = newmMeshes;
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::push_back(Texture* texture){
	mNumTextures++;
	Texture** newmTextures;
	newmTextures = new Texture*[mNumTextures];
	newmTextures[mNumTextures - 1] = texture;
	if (mTextures != NULL){
		for (int i = 0; i < mNumTextures - 1; i++)
			newmTextures[i] = mTextures[i];
	}

	delete mTextures;
	mTextures = newmTextures;
}
// ------------------------------------------------------------------------------------------------------------------------------
void Recursive_Draw(Model* model, Node* mRootNode, Shader* shader, Matrix4x4s &world){
	Mesh** mesh = model->mMeshes;
	if (mRootNode != NULL){
		Matrix4x4s Trans = mRootNode->getTransformation();
		Matrix4x4s World = world * Trans;
		glUniformMatrix4fv(shader->mWorld, 1, GL_TRUE, (float*)&World);

		for (int i = 0; i < mRootNode->getNumMeshes(); i++){
			Mesh* part = mesh[mRootNode->mMeshes[i]];
			
			Texture* tex = model->mMaterials[part->getTextureIndex()].mDiffuseTexture;
			Vector4s DiffuseColor = model->mMaterials[part->getTextureIndex()].getDiffuseColor();
			if (tex){
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex->tex_2d);								
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glUniform1f(shader->mEnableTexture, 1.0f);
				glUniform4fv(shader->mDiffuseColor, 1, (float*)&DiffuseColor);
			}else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);	
				glUniform1f(shader->mEnableTexture, 0.0f);
				glUniform4fv(shader->mDiffuseColor, 1, (float*)&DiffuseColor);
			}

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, part->getVBO());			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3s), 0);

			glBindBuffer(GL_ARRAY_BUFFER, part->getNBO());			
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3s), 0);

			glBindBuffer(GL_ARRAY_BUFFER, part->getCoorBO());
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2s), 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, part->getIBO());			
			glDrawElements(GL_TRIANGLES, part->getNumFaces() * 3, GL_UNSIGNED_INT, 0);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
		glBindTexture(GL_TEXTURE_2D, 0);							

		for (int i = 0; i < mRootNode->getNumChildren(); i++){
			Node* child = mRootNode->mChildren[i];
			Recursive_Draw(model, child, shader, World);
		}
	}
}
// ------------------------------------------------------------------------------------------------------------------------------
void Model::drawModel(Shader* shader, float rotx){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	Matrix4x4s Trans = Matrix4x4s::Identity();
	btDefaultMotionState* myMotionState = (btDefaultMotionState*)mPhysicTrans->getMotionState();
	myMotionState->m_graphicsWorldTrans.getOpenGLMatrix((float*)&Trans);
	Trans.Transpose();
	Recursive_Draw(this, mRootNode, shader, Trans);
}
// ------------------------------------------------------------------------------------------------------------------------------
*/