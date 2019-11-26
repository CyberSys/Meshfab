#pragma once
#include <fbxsdk.h>                // FBX SDK
#include <glm/glm.hpp>
#include <vector>
#include <map>

// Get the geometry offset to a node. It is never inherited by the children.
FbxAMatrix GetGeometry(FbxNode* pNode)
{
  const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
  const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
  const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

  return FbxAMatrix(lT, lR, lS);
}

// FbxAMatrix → Matrix44
glm::mat4 getMatrix44(const FbxAMatrix& matrix)
{
	const double* p = (const double*)matrix;

	glm::mat4 m(p[0], p[1], p[2], p[3],
		p[4], p[5], p[6], p[7],
		p[8], p[9], p[10], p[11],
		p[12], p[13], p[14], p[15]);

	return m;
}

struct Skin
{
	bool has_skins;
	std::vector<std::vector<float>> weights;
	std::vector<FbxAMatrix> base_inv;
};

struct TriMesh
{
	std::vector<float>		mPositions;
	std::vector<float>		mColors;
	std::vector<float>		mNormals;
	std::vector<float>		mTangents;
	std::vector<float>		mBitangents; 
	std::vector<float>		mTexCoords;
	std::vector<uint32_t>	mIndices;
};

struct Mesh
{
  TriMesh tri_mesh;

  Skin skin;
  TriMesh deformed_mesh;
};

struct Material
{
	glm::vec3	mColorAmbient;
	glm::vec3	mColorDiffuse;
	glm::vec3	mColorEmission;
	glm::vec3	mColorSpecular;
	float		mShininess;
	unsigned int  texture;
};

class Importer
{
public:
	Importer();
	~Importer();

	void setAnimation(const int index);

	Mesh createMesh(FbxMesh* mesh);
	Skin createSkin(FbxMesh* mesh);
	Material createMaterial(FbxSurfaceMaterial* material);

	TriMesh getDeformedTriMesh(FbxMesh* mesh, const Mesh& src_mesh, FbxAMatrix& parent_matrix, FbxTime& time);
	const TriMesh& getTriMesh(FbxMesh* mesh, Mesh& src_mesh, FbxAMatrix& parent_matix, FbxTime& time);


	void draw(FbxNode* node, FbxTime& time);

private:
	FbxManager* manager;
	FbxScene* scene;
	FbxNode* root_node;

	double animation_time = 0.0;
	double animation_start;
	double animation_stop;

	std::map<std::string, Mesh> meshes;
	std::map<std::string, Material> materials;
};