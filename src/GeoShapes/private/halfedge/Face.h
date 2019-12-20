#pragma once
#include <glm.hpp>
#include <vector>
#include "Halfedge.h"

class Face
{
public:
	Face();
	Face(Halfedge*, glm::vec4, unsigned int, glm::vec3);
	~Face();

	void SetStartEdge(Halfedge*);

	void SetColor(glm::vec4);

	void SetFaceID(unsigned int);

	void SetNormal(glm::vec3);

	void SetNormal();

	Halfedge* GetStartEdge();

	glm::vec4 GetColor();

	glm::vec3 GetNormal();

	unsigned int GetFaceID();

	Halfedge* GetPreEdge(Halfedge*);

	int GetEdgeNum();

	std::vector<Halfedge*> GetEdgeList();

private:
	Halfedge* start_edge;
	glm::vec4 color;
	unsigned int FaceID;
	glm::vec3 normal;
};