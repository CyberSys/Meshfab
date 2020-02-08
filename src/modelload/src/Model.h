#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using namespace std;

struct Part
{
	vector<float> vertices;
	vector<float> normals;
	vector<float> colors;
	vector<float> tangent;
	vector<float> bitangent;
	vector<float> uvs;
	vector<float> BoneIndices; //4-components per vertex
	vector<float> BoneWeights; //4-components per vertex
	vector<unsigned int> indices;

	// textures ids in gpu
	vector<unsigned int> textures;
	/*
	* [0] DIFFUSE TEXTURE
	* [1] SPECULAR TEXTURE
	* [2] OPACITY TEXTURE
	* [3] AMBIENT TEXTURE
	* [4] SHININES TEXTURE
	* [5] LIGHTMAP TEXTURE
	* [5] NORMAL/HEIGHT MAP
	*/


	glm::vec3 bounding_max;
	glm::vec3 bounding_min;
};

class Model
{
public:
	static vector<Part> Load(const char* filename);
};