#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>

struct Material
{
	glm::vec3	ColorAmbient;
	glm::vec3	ColorDiffuse;
	glm::vec3	ColorEmission;
	glm::vec3	ColorSpecular;

	float		Shininess;

	unsigned int diffuse_texture;
	unsigned int normal_texture;
	unsigned int specular_texture;
};

struct Mesh
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	//mandatory data..
	std::vector<float>		mVertices;
	std::vector<float>		mNormals;
	std::vector<float>		mTexCoords;

	//optional data..
	std::vector<float>		mColors;
	std::vector<float>		mTangents;
	std::vector<float>		mBitangents; 

	std::vector<uint32_t>	mIndices;
};

class StaticModel
{
public:
	StaticModel();

	~StaticModel();

	std::map<std::string, Mesh> meshes;
	std::map<std::string, Material> materials;
};