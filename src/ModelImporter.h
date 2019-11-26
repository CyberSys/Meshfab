#pragma once
#include "StaticModel.h"

#include <fbxsdk.h>
#include <glm.hpp>

class ModelImporter
{
public:
	ModelImporter();

	~ModelImporter();

	StaticModel Import_SM(const char * filepath);

private:
	FbxScene* mScene = NULL;
	FbxManager* mSdkManager = NULL;
	bool mStatus = false;
};