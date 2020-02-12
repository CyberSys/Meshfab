#include "Model.h"

// GL-include
#include <glew.h>

// assimp library includes
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// tetxure loader include
#include <Texture.h>


/////////////////////// textures & materials
void get_mesh_texture(aiScene* scene, const aiMesh* mesh, const char* directory, vector<unsigned int>& textures)
{
	// extract all properties from the ASSIMP material structure
	const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	aiString Path;

	if (mesh->mTextureCoords[0])
	{
		// diffuse texture
		if(aiGetMaterialString(material,AI_MATKEY_TEXTURE_DIFFUSE(0),&Path) == AI_SUCCESS)
		{
			string fullpath(directory);
			fullpath += '\\';
			fullpath += Path.C_Str();
			auto id = Texture::Create2D(fullpath.c_str());
			textures.push_back(id);
		}
	}

}

//////////////////////////////////////////////////////

void aimat4_to_glmat4(aiMatrix4x4& prevmat, glm::mat4& newmat)
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			newmat[i][j] = prevmat[i][j];
		}
	}
}

//-------------------------------------------------------------------------------
// Calculate the boundaries of a given node and all of its children
// The boundaries are in Worldspace (AABB)
// piNode Input node
// p_avOut Receives the min/max boundaries. Must point to 2 vec3s
// piMatrix Transformation matrix of the graph at this position
//-------------------------------------------------------------------------------
int CalculateBounds(aiScene* scene, aiNode* piNode, glm::vec3* Out, const aiMatrix4x4& piMatrix) {

	aiMatrix4x4 mTemp = piNode->mTransformation;
	aiMatrix4x4 aiMe = mTemp * piMatrix;

	for (unsigned int i = 0; i < piNode->mNumMeshes; ++i)
	{
		for (unsigned int a = 0; a < scene->mMeshes[
			piNode->mMeshes[i]]->mNumVertices; ++a)
		{
			aiVector3D pc = scene->mMeshes[piNode->mMeshes[i]]->mVertices[a];

			glm::vec4 v(pc.x, pc.y, pc.z, 1);
			glm::mat4 trans(1);
			aimat4_to_glmat4(aiMe, trans);
			glm::vec3 res_vec = trans * v;


			Out[0].x = glm::min(Out[0].x, v.x);
			Out[0].y = glm::min(Out[0].y, v.y);
			Out[0].z = glm::min(Out[0].z, v.z);
			Out[1].x = glm::max(Out[1].x, v.x);
			Out[1].y = glm::max(Out[1].y, v.y);
			Out[1].z = glm::max(Out[1].z, v.z);
		}
	}
	for (unsigned int i = 0; i < piNode->mNumChildren; ++i)
	{
		CalculateBounds(scene, piNode->mChildren[i], Out, aiMe);
	}
	return 1;
}

//-------------------------------------------------------------------------------
// Scale the asset that it fits perfectly into the viewer window
// The function calculates the boundaries of the mesh and modifies the
// global world transformation matrix according to the aset AABB
//-------------------------------------------------------------------------------
inline static void ScaleModel(aiScene* scene, glm::vec3& max, glm::vec3& min,vector<float>& vertices)
{
	glm::vec3 minmax[2] = {glm::vec3(1e10f, 1e10f, 1e10f),glm::vec3(-1e10f, -1e10f, -1e10f)};
	aiMatrix4x4 m;
	CalculateBounds(scene,scene->mRootNode,minmax,m);

	min = minmax[0];
	max = minmax[1];

	glm::vec3 delta = max - min;
	glm::vec3 vhalf = min + (delta / 2.0f);
	float scale = 10.0f / glm::length(delta);

	//update vertices with new scale
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		glm::vec4 vert(vertices[i],vertices[i + 1],vertices[i + 2], 1.0f);

		glm::vec3 result = glm::translate(glm::mat4(1), -vhalf) * vert *glm::scale(glm::mat4(1), glm::vec3(scale));
		vertices[i]		= result.x;
		vertices[i + 1] = result.y;
		vertices[i + 2] = result.z;
	}

	//update max & min values
	max =  glm::translate(glm::mat4(1), -vhalf) * glm::vec4(max, 1) * glm::scale(glm::mat4(1), glm::vec3(scale));
	min =  glm::translate(glm::mat4(1), -vhalf) * glm::vec4(min, 1) * glm::scale(glm::mat4(1), glm::vec3(scale));
}

struct node_transform
{
	glm::mat4 node_trans;
	vector<unsigned int> mesh_indx;
};

void get_meshNode(aiNode* current,aiScene* scene,vector<node_transform>& mats)
{
	for(size_t i = 0 ; i < current->mNumChildren; ++i)
		get_meshNode(current->mChildren[i],scene,mats);

	if(current->mMeshes != NULL)
	{
		//this meshes perform with same transformation node
		node_transform tr;
		aimat4_to_glmat4(current->mTransformation,tr.node_trans);

		for(size_t i = 0 ; i < current->mNumMeshes; ++i)
			tr.mesh_indx.push_back(current->mMeshes[i]);

		mats.push_back(tr);
	}
}

/////////////////////////////////// Assimp file loader ...
//we need to load all scene graph of the model to load it in mesh parts..
//recurse on all mesh parts..
vector<Part> Model::Load(const char * filename)
{
	// get dir folder
	string _path = string(filename);
	string dir_path = _path.substr(0, _path.find_last_of('\\'));

	// get current time
	clock_t begin = clock();

	aiPropertyStore* props = aiCreatePropertyStore();
	aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
	aiSetImportPropertyInteger(props, AI_CONFIG_GLOB_MEASURE_TIME, 1);

	unsigned int ppsteps = aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
		aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
		aiProcess_ValidateDataStructure | // perform a full validation of the loader's output
		aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
		aiProcess_RemoveRedundantMaterials | // remove redundant materials
		aiProcess_FindDegenerates | // remove degenerated polygons from the import
		aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
		aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
		aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
		aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
		aiProcess_OptimizeMeshes | // join small meshes, if possible;
		aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		0;

		aiScene* scene = (aiScene*)aiImportFileExWithProperties(filename,
		ppsteps | /* configurable pp steps */
		//aiProcess_GlobalScale | 
		aiProcess_GenSmoothNormals | // generate smooth normal vectors if not existing
		aiProcess_SplitLargeMeshes | // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate | // triangulate polygons with more than 3 edges
		aiProcess_ConvertToLeftHanded | // convert everything to D3D left handed space
		aiProcess_SortByPType | // make 'clean' meshes which consist of a single typ of primitives
		0,
		NULL,
		props);

	aiReleasePropertyStore(props);
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("load time = %f \n",(float)(elapsed_secs));

	// check whether the loading process has failed ...
	if (scene == NULL)
	{
		printf("faild to load this file !! \n");
		//return vector<Part>();
	}

	vector<Part> modelparts;
	
	// loop on all meshes..
	for (size_t i = 0; i < scene->mNumMeshes;++i)
	{
		Part modelpart;
		const aiMesh* mesh = scene->mMeshes[i];

		// Load Textures for each mesh..
		get_mesh_texture(scene, mesh, dir_path.c_str(), modelpart.textures);

		// fill the buffers
		for (size_t x = 0; x < mesh->mNumVertices; ++x)
		{
			// vertix positions
			modelpart.vertices.push_back(mesh->mVertices[x].x);
			modelpart.vertices.push_back(mesh->mVertices[x].y);
			modelpart.vertices.push_back(mesh->mVertices[x].z);

			// normals
			if (mesh->mNormals == NULL)
			{
				modelpart.normals.push_back(0.0f);
				modelpart.normals.push_back(0.0f);
				modelpart.normals.push_back(0.0f);
			}
			else
			{
				modelpart.normals.push_back(mesh->mNormals[x].x);
				modelpart.normals.push_back(mesh->mNormals[x].y);
				modelpart.normals.push_back(mesh->mNormals[x].z);
			}

			// tangents & bitangents
			if (mesh->mTangents == NULL)
			{
				modelpart.tangent.push_back(0.0f);
				modelpart.tangent.push_back(0.0f);
				modelpart.tangent.push_back(0.0f);

				modelpart.bitangent.push_back(0.0f);
				modelpart.bitangent.push_back(0.0f);
				modelpart.bitangent.push_back(0.0f);
			}
			else
			{
				modelpart.tangent.push_back(mesh->mTangents[x].x);
				modelpart.tangent.push_back(mesh->mTangents[x].y);
				modelpart.tangent.push_back(mesh->mTangents[x].z);

				modelpart.bitangent.push_back(mesh->mBitangents[x].x);
				modelpart.bitangent.push_back(mesh->mBitangents[x].y);
				modelpart.bitangent.push_back(mesh->mBitangents[x].z);
			}

			// vertex color
			if (mesh->HasVertexColors(0)) {
				modelpart.colors.push_back(max( min( mesh->mColors[0][x].r * 255.0f, 255.0f),0.0f) );
				modelpart.colors.push_back(max( min( mesh->mColors[0][x].r * 255.0f, 255.0f),0.0f) );
				modelpart.colors.push_back(max( min( mesh->mColors[0][x].r * 255.0f, 255.0f),0.0f) );
				modelpart.colors.push_back(max( min( mesh->mColors[0][x].r * 255.0f, 255.0f),0.0f) );
			}
			else
			{
				modelpart.colors.push_back(1.0f);
				modelpart.colors.push_back(1.0f);
				modelpart.colors.push_back(1.0f);
				modelpart.colors.push_back(1.0f);
			}

			// uvs coords
			if (mesh->HasTextureCoords(0)) {
				modelpart.uvs.push_back(mesh->mTextureCoords[0][x].x);
				modelpart.uvs.push_back(mesh->mTextureCoords[0][x].y);
			}
			else
			{
				modelpart.uvs.push_back(0.5f);
				modelpart.uvs.push_back(0.5f);
			}

			// bones & weights
			// TODO

			//bounding box
			modelpart.bounding_max = glm::vec3(mesh->mAABB.mMax.x,mesh->mAABB.mMax.y,mesh->mAABB.mMax.z);
			modelpart.bounding_min = glm::vec3(mesh->mAABB.mMin.x,mesh->mAABB.mMin.y,mesh->mAABB.mMin.z);
		}

		// fill index buffer
		for (unsigned int x = 0; x < mesh->mNumFaces; ++x)
		{
			for (unsigned int a = 0; a < 3 /*triangle*/; ++a)
			{
				modelpart.indices.push_back(mesh->mFaces[x].mIndices[a]);
			}
		}

		modelparts.push_back(modelpart);
	}

	vector<node_transform> trans;
	get_meshNode(scene->mRootNode,scene,trans);

	for (auto el : trans)
	{
		for (auto meshindx : el.mesh_indx)
		{
			//dont forget to scale model to fit on screen
			ScaleModel(scene, modelparts[meshindx].bounding_max,
				modelparts[meshindx].bounding_min,
				modelparts[meshindx].vertices);

			//for (size_t i = 0; i < modelparts[meshindx].vertices.size(); i += 3)
			//{
			//	glm::vec4 vert(modelparts[meshindx].vertices[i],
			//		modelparts[meshindx].vertices[i + 1],
			//		modelparts[meshindx].vertices[i + 2], 1.0f);
			//
			//	glm::vec3 result = vert * el.node_trans;
			//	modelparts[meshindx].vertices[i] = result.x;
			//	modelparts[meshindx].vertices[i + 1] = result.y;
			//	modelparts[meshindx].vertices[i + 2] = result.z;
			//}
		}
	}

	printf("Model Loading Finished .. \n");
	return modelparts;
}
