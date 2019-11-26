#pragma once
#include <vector>
#include <fbxsdk.h>
#include <glm.hpp>

using namespace std;

struct NodeTransform
{
	const char* name;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class FbxEngine
{
public:
	// Prepare the FBX SDK.
	FbxEngine();

	//delete alll alocated objects
	~FbxEngine();

	//import scene
	bool Import(const char* filepath);

	//process scene graph
	void Process_Scene();

private:
	void Process_Node(FbxNode* pNode);
	void Process_Boundary(FbxNode* pNode);
	void Process_Mesh(FbxNode* pNode);
	void Process_Skelelton(FbxNode* pNode);

	FbxScene* mScene = NULL;
	FbxManager* mSdkManager = NULL;
	const char* mSdkVersion = NULL;
	bool mStatus = false;
	int mAnimStackCount;
	vector<char*> mAnimationName_list;
	vector<NodeTransform> mNodesTransform;
};