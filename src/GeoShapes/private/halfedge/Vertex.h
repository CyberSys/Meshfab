#pragma once
#include <glm.hpp>
#include "Halfedge.h"
#include <vector>

class Vertex
{
public:
	Vertex();
	Vertex(glm::vec3, Halfedge *, unsigned int);
	~Vertex();

	void SetPos(glm::vec3);

	void SetEdge(Halfedge*);

	void SetVertexID(unsigned int);
	
	glm::vec3 GetPos();

	Halfedge* GetEdge();

	unsigned int GetVertexID();

private:
	glm::vec3 pos;
	Halfedge* edge;
	unsigned int VertexID;
};