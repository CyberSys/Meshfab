#include "GContainer.h"

GContainer::GContainer() 
	: faces_count(0)
{

}

GContainer::~GContainer()
{

}

void GContainer::Add_Face(GFace face)
{
	Faces[faces_count] = face;

	index_buffer.push_back(face.a);
	index_buffer.push_back(face.b);
	index_buffer.push_back(face.c);

	face.ID = faces_count;
	++faces_count;
}

void GContainer::Delete_Face(int face_id)
{
	auto face = Faces[face_id];

	int indx = (face_id * 3);
	index_buffer.erase(index_buffer.begin() + indx, index_buffer.begin() + indx + 3);

	Faces.erase(face_id);
	--faces_count;
}

int GContainer::Faces_Count()
{
	return faces_count;
}

vector<unsigned int> GContainer::indcies()
{
	return index_buffer;
}

