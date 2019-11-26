#include "FbxEngine.h"


#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(mSdkManager->GetIOSettings()))
#endif


FbxEngine::FbxEngine()
{
	//The first thing to do is to create the FBX Manager 
	//which is the object allocator for almost all the classes in the SDK
	mSdkManager = FbxManager::Create();
	if (!mSdkManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", mSdkVersion = mSdkManager->GetVersion());

	//Create an IOSettings object.
	//This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(mSdkManager, IOSROOT);
	mSdkManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	mSdkManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. 
	//This object holds most objects imported/exported from/to files.
	mScene = FbxScene::Create(mSdkManager, "Scene");
	if (!mScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}
}

FbxEngine::~FbxEngine()
{
	//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
	if (mSdkManager) mSdkManager->Destroy();
	if (mStatus) FBXSDK_printf("Program Success!\n");
}

bool FbxEngine::Import(const char * filepath)
{
	int lFileMajor, lFileMinor, lFileRevision;
	int lSDKMajor, lSDKMinor, lSDKRevision;
	bool lStatus;
	char lPassword[1024];

	// Get the file version number generate by the FBX SDK.
	FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

	// Create an importer.
	FbxImporter* lImporter = FbxImporter::Create(mSdkManager, "importer");

	// Initialize the importer by providing a filename.
	const bool lImportStatus = lImporter->Initialize(filepath, -1, mSdkManager->GetIOSettings());
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

	if (!lImportStatus)
	{
		FbxString error = lImporter->GetStatus().GetErrorString();
		FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
		FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

		if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
		{
			FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
			FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", filepath, lFileMajor, lFileMinor, lFileRevision);
		}

		return false;
	}

	FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

	if (lImporter->IsFBX())
	{
		FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", filepath, lFileMajor, lFileMinor, lFileRevision);

		// From this point, it is possible to access animation stack information without
		// the expense of loading the entire file.

		FBXSDK_printf("Animation Stack Information\n");

		mAnimStackCount = lImporter->GetAnimStackCount();

		FBXSDK_printf("    Number of Animation Stacks: %d\n", mAnimStackCount);
		FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
		FBXSDK_printf("\n");

		for (int i = 0; i < mAnimStackCount; i++)
		{
			FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

			FBXSDK_printf("    Animation Stack %d\n", i);
			FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			mAnimationName_list.push_back(lTakeInfo->mName.Buffer());

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
	lStatus = lImporter->Import(mScene);

	if (lStatus == true)
	{
		// Check the scene integrity!
		FbxStatus status;
		FbxArray< FbxString*> details;
		FbxSceneCheckUtility sceneCheck(FbxCast<FbxScene>(mScene), &status, &details);
		lStatus = sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData);
		if (lStatus == false)
		{
			if (details.GetCount())
			{
				FBXSDK_printf("Scene integrity verification failed with the following errors:\n");
				for (int i = 0; i < details.GetCount(); i++)
					FBXSDK_printf("   %s\n", details[i]->Buffer());

				FbxArrayDelete<FbxString*>(details);
			}
		}
	}

	//check for password
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

		lStatus = lImporter->Import(mScene);

		if (lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
		{
			FBXSDK_printf("\nPassword is wrong, import aborted.\n");
		}
	}

	// Destroy the importer.
	lImporter->Destroy();


	// Convert the scene to triangles..
	FbxGeometryConverter clsConverter(mSdkManager);
	clsConverter.Triangulate(mScene, false);

	return lStatus;
}


//-------------------------------------------------------------

void FbxEngine::Process_Skelelton(FbxNode* pNode)
{
	FbxSkeleton* lSkeleton = (FbxSkeleton*) pNode->GetNodeAttribute();
}

void FbxEngine::Process_Mesh(FbxNode* pNode)
{
	FbxMesh* lMesh = (FbxMesh*) pNode->GetNodeAttribute ();

}

void FbxEngine::Process_Boundary(FbxNode* pNode)
{
}

void FbxEngine::Process_Node(FbxNode* pNode)
{
	//for each node get its content
	//for each node had attributes

	FbxNodeAttribute::EType lAttributeType;
	int i;
	NodeTransform ntransform;
	ntransform.name = pNode->GetName();

	if (pNode->GetNodeAttribute() == NULL)
	{
		FBXSDK_printf("NULL Node Attribute\n\n");
	}
	else
	{
		lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

		switch (lAttributeType)
		{
		default:
			break;

		case FbxNodeAttribute::eSkeleton:
			Process_Skelelton(pNode);
			break;

		case FbxNodeAttribute::eMesh:
			Process_Mesh(pNode);
			break;

		case FbxNodeAttribute::eBoundary:
			Process_Boundary(pNode);
			break;
		}
	}

	// process node transform
	FbxVector4 lTmpVector;

	//
	// Translation
	//
	lTmpVector = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	ntransform.position.x = (float)lTmpVector[0];
	ntransform.position.y = (float)lTmpVector[1];
	ntransform.position.z = (float)lTmpVector[2];

	//
	// Rotation
	//
	lTmpVector = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	ntransform.rotation.x = (float)lTmpVector[0];
	ntransform.rotation.y = (float)lTmpVector[1];
	ntransform.rotation.z = (float)lTmpVector[2];

	//
	// Scaling
	//
	lTmpVector = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
	ntransform.scale.x = (float)lTmpVector[0];
	ntransform.scale.y = (float)lTmpVector[1];
	ntransform.scale.z = (float)lTmpVector[2];

	mNodesTransform.push_back(ntransform);

	for (i = 0; i < pNode->GetChildCount(); i++)
	{
		Process_Node(pNode->GetChild(i));
	}
}
void FbxEngine::Process_Scene()
{
	if (mScene)
	{
		int i;
		FbxNode* lNode = mScene->GetRootNode();

		if (lNode)
		{
			for (i = 0; i < lNode->GetChildCount(); i++)
			{
				Process_Node(lNode->GetChild(i));
			}
		}
	}
}
