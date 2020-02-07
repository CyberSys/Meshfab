#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <glm.hpp>
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
	vector<unsigned int> textures;
	glm::vec3 bounding_max;
	glm::vec3 bounding_min;
};

class Model
{
public:
	static vector<Part> Load(const char* filename);
};