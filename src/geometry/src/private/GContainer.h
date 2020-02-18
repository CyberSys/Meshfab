#pragma once
#include <vector>
#include <map>
using namespace std;

/*
* treat geomtery as set of triangles
* each triangle is a face
*/
struct GFace
{
	int ID;
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class GContainer
{
public:
	GContainer();
	~GContainer();

	void Add_Face(GFace face);
	void Delete_Face(int face_id);

	int Faces_Count();
	vector<unsigned int> indcies();
private:
	int faces_count;
	map<int,GFace> Faces;
	vector<unsigned int> index_buffer;
};