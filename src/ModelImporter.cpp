#include "ModelImporter.h"
#include <iostream>
#include <string>
#include <sstream>

ModelImporter::ModelImporter()
{
	//The first thing to do is to create the FBX Manager 
	//which is the object allocator for almost all the classes in the SDK
	mSdkManager = FbxManager::Create();
	if (!mSdkManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", mSdkManager->GetVersion());

	//Create an IOSettings object.
	//This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(mSdkManager, IOSROOT);
	mSdkManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	mSdkManager->LoadPluginsDirectory(lPath.Buffer());
}

ModelImporter::~ModelImporter()
{
	//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
	if (mSdkManager) mSdkManager->Destroy();
	if (mStatus) FBXSDK_printf("Program Success!\n");
}


//------------------------------------ static model loading
inline static Mesh
createMesh(FbxMesh* mesh)
{
	Mesh mesh_info;

	//vertices
	int indexCount = mesh->GetPolygonVertexCount();
	int* index = mesh->GetPolygonVertices();
	for (int i = 0; i < indexCount; ++i)
	{
		auto controlPoint = mesh->GetControlPointAt(index[i]);
		mesh_info.mVertices.push_back((float)controlPoint[0]);
		mesh_info.mVertices.push_back((float)controlPoint[1]);
		mesh_info.mVertices.push_back((float)controlPoint[2]);
	}

	//nomrals
	FbxArray<FbxVector4> normals;
	mesh->GetPolygonVertexNormals(normals);

	for (int i = 0; i < normals.Size(); ++i)
	{
		const FbxVector4& n = normals[i];
		mesh_info.mNormals.push_back((float)n[0]);
		mesh_info.mNormals.push_back((float)n[1]);
		mesh_info.mNormals.push_back((float)n[2]);
	}

	//UV
	FbxStringList uvsetName;
	mesh->GetUVSetNames(uvsetName);

	if (uvsetName.GetCount() > 0)
	{
		FbxArray<FbxVector2> uvsets;
		mesh->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

		for (int i = 0; i < uvsets.Size(); ++i)
		{
			const FbxVector2& uv = uvsets[i];
			mesh_info.mTexCoords.push_back((float)uv[0]);
			mesh_info.mTexCoords.push_back((float)uv[1]);
		}
	}

	auto local_rotation = mesh->GetNode()->LclRotation.Get();
	auto local_translation = mesh->GetNode()->LclTranslation.Get();
	auto local_scale = mesh->GetNode()->LclScaling.Get();

	return mesh_info;
}

inline static Material
createMaterial(FbxSurfaceMaterial* material)
{
	Material mat;

	glm::vec3  ambient(0.0f, 0.0f, 0.0f);
	glm::vec3  diffuse(1.0f, 1.0f, 1.0f);
	glm::vec3  emissive(0.0f, 0.0f, 0.0f);
	glm::vec3  specular(0.0f, 0.0f, 0.0f);
	float shininess = 80.0f;

	{
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
		if (prop.IsValid())
		{
			const auto& color = prop.Get<FbxDouble3>();
			ambient = glm::vec3(color[0], color[1], color[2]);
		}
	}
	{
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		if (prop.IsValid())
		{
			const auto& color = prop.Get<FbxDouble3>();
			diffuse = glm::vec3(color[0], color[1], color[2]);
		}
	}
	{
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
		if (prop.IsValid())
		{
			const auto& color = prop.Get<FbxDouble3>();
			emissive = glm::vec3(color[0], color[1], color[2]);
		}
	}
	{
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
		if (prop.IsValid())
		{
			const auto& color = prop.Get<FbxDouble3>();
			specular = glm::vec3(color[0], color[1], color[2]);
		}
	}
	{
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
		if (prop.IsValid())
		{
			shininess = (float)prop.Get<FbxDouble>();
		}
	}

	mat.ColorAmbient = ambient;
	mat.ColorDiffuse = diffuse;
	mat.ColorSpecular = specular;
	mat.Shininess = shininess;
	mat.ColorEmission = emissive;


	{ //load textures
	
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		if (prop.GetSrcObjectCount<FbxFileTexture>() > 0)
		{
			FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(0);
			if (texture)
			{
				const char* name = texture->GetFileName();
	
				//Surface surface = loadImage(loadAsset(name));
				//ip::flipVertical(&surface);
				//
				//mat.texture = surface;
				//mat.texture->setWrap(GL_REPEAT, GL_REPEAT);
	
				std::cout << "texture:" << name << std::endl;
			}
		}
	}

	return mat;

}

StaticModel ModelImporter::Import_SM(const char * filepath)
{
	StaticModel res;

	// Create an importer.
	FbxImporter* lImporter = FbxImporter::Create(mSdkManager, "importer");
	if(!lImporter->Initialize(filepath))
	{
	  std::cout << "FBX:can't open " << filepath << std::endl;
	}

	mScene = FbxScene::Create(mSdkManager, "");
	lImporter->Import(mScene);

	std::cout << "FBX:Imported." << std::endl;
	lImporter->Destroy();

	FbxGeometryConverter geometryConverter(mSdkManager);
	geometryConverter.Triangulate(mScene, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(mScene);

	geometryConverter.SplitMeshesPerMaterial(mScene, true);

	// Convert Axis System to what is used in this example, if needed
	FbxAxisSystem SceneAxisSystem = mScene->GetGlobalSettings().GetAxisSystem();
	FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
	if (SceneAxisSystem != OurAxisSystem)
	{
		OurAxisSystem.ConvertScene(mScene);
	}

	std::cout << "FBX:Converted." << std::endl;

	FbxNode* root_node = mScene->GetRootNode();

	{ //meshes loading..
		auto meshCount = mScene->GetSrcObjectCount<FbxMesh>();
		std::cout << "meshCount:" << meshCount << std::endl;

		for (int i = 0; i < meshCount; ++i)
		{
			FbxMesh* mesh = mScene->GetSrcObject<FbxMesh>(i);

			std::string mesh_name = mesh->GetNode()->GetName();

			if (res.meshes.count(mesh_name)) continue;

			Mesh mesh_info = createMesh(mesh);

			res.meshes.insert({ mesh_name, mesh_info });
		}
	}

	{ //material loading..
		auto materialCount = mScene->GetMaterialCount();
		std::cout << "material:" << materialCount << std::endl;

		for (int i = 0; i < materialCount; ++i)
		{
			FbxSurfaceMaterial* material = mScene->GetMaterial(i);
			std::string name = material->GetName();

			if (res.materials.count(name)) continue;

			Material mat = createMaterial(material);
			res.materials.insert({ name, mat });
		}
	}


	return res;
}
