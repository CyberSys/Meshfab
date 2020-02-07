#include "Face.h"
#include "Vertex.h"

Face::Face() :Face(nullptr, glm::vec4(1.0f), 0, glm::vec3(0.0f)) {}

Face::Face(Halfedge *h, glm::vec4 c, unsigned int i, glm::vec3 n) :
	start_edge(h), color(c), FaceID(i), normal(n)
{

}
Face::~Face()
{
	start_edge = nullptr;
}

void Face::SetStartEdge(Halfedge * h)
{
	start_edge = h;
}

void Face::SetColor(glm::vec4 c)
{
	color = c;
}

void Face::SetFaceID(unsigned int i)
{
	FaceID = i;
}

void Face::SetNormal(glm::vec3 n)
{
	normal = n;
}

void Face::SetNormal()
{
	if (start_edge != nullptr)
	{
		glm::vec3 pos1 = start_edge->GetVertex()->GetPos();
		glm::vec3 pos2 = start_edge->GetNext()->GetVertex()->GetPos();
		glm::vec3 pos3 = start_edge->GetNext()->GetNext()->GetVertex()->GetPos();
		normal = glm::normalize(glm::cross(pos1 - pos2, pos2 - pos3));
	}
}

Halfedge* Face::GetStartEdge()
{
	return start_edge;
}

glm::vec4 Face::GetColor()
{
	return color;
}

unsigned int Face::GetFaceID()
{
	return FaceID;
}

glm::vec3 Face::GetNormal()
{
	return normal;
}

int Face::GetEdgeNum()
{
	int i = 1;
	Halfedge* h0 = start_edge->GetNext();
	while (h0 != start_edge)
	{
		i++;
		h0 = h0->GetNext();
	}
	return i;
}

std::vector<Halfedge*> Face::GetEdgeList()
{
	std::vector<Halfedge*> b4Edge;
	Halfedge* h0 = start_edge;
	b4Edge.push_back(h0);
	h0 = h0->GetNext();
	while (h0 != start_edge)
	{

		b4Edge.push_back(h0);
		h0 = h0->GetNext();
	}
	return b4Edge;
}

Halfedge* Face::GetPreEdge(Halfedge *h)
{
	std::vector<Halfedge*> b4Edge = GetEdgeList();
	int hth = -1;
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		if (b4Edge[i]->GetNext() == h)
			hth = i;
	}
	if (hth != -1)
		return b4Edge[hth];
	else
		return nullptr;
}

void Face::SetPreEdge(Halfedge *h)
{
	std::vector<Halfedge*> b4Edge = GetEdgeList();
	int hth = -1;
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		if (b4Edge[i]->GetNext() == h)
			hth = i;
	}
	if (hth != -1)
		b4Edge[hth] = h;
}
