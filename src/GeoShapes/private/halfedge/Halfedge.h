#pragma once
#include <glm.hpp>

class Vertex;
class Face;
class Halfedge
{
public:
	Halfedge();

	Halfedge(Face*, Vertex*, Halfedge*, Halfedge*, unsigned int);

	~Halfedge();

	void SetFace(Face*);

	void SetVertex(Vertex*);

	void SetNext(Halfedge*);

	void SetSym(Halfedge*);

	void SetHalfEdgeID(unsigned int);

	Face* GetFace();

	Vertex* GetVertex();

	Halfedge* GetNext();

	Halfedge* GetSym();

	unsigned int GetHalfEdgeID();

	Halfedge* GetPrevious();

private:
	Face* face;
	Vertex* vert;
	Halfedge* next;
	Halfedge* sym;
	unsigned int HalfEdgeID;
};