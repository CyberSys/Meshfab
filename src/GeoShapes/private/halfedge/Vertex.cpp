#include "Vertex.h"

Vertex::Vertex() :Vertex(glm::vec3(1.0f), nullptr, 0) {}
Vertex::Vertex(glm::vec3 v, Halfedge* e, unsigned int id) :
	pos(v), edge(e), VertexID(id)
{
}

Vertex::~Vertex()
{
	edge = nullptr;
}

void Vertex::SetPos(glm::vec3 v)
{
	pos = v;
}

void Vertex::SetEdge(Halfedge *e)
{
	edge = e;
}

void Vertex::SetVertexID(unsigned int i)
{
	VertexID = i;
}

glm::vec3 Vertex::GetPos()
{
	return pos;
}

Halfedge* Vertex::GetEdge()
{
	return edge;
}

unsigned int Vertex::GetVertexID()
{
	return VertexID;
}