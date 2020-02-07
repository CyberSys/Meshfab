#include "Halfedge.h"
#include "Face.h"

Halfedge::Halfedge() : Halfedge(nullptr, nullptr, nullptr, nullptr, 0) {}

Halfedge::Halfedge(Face *f, Vertex *v, Halfedge *n, Halfedge *s, unsigned int i) :
	face(f), 
	vert(v), 
	next(n), 
	sym(s), 
	HalfEdgeID(i)
{
}

Halfedge::~Halfedge()
{
	face = nullptr;
	vert = nullptr;
	next = nullptr;
	sym = nullptr;
}

void Halfedge::SetFace(Face *f)
{
	face = f;
}

void Halfedge::SetVertex(Vertex *v)
{
	vert = v;
}

void Halfedge::SetNext(Halfedge *n)
{
	next = n;
}

void Halfedge::SetPrevious(Halfedge *hpre)
{
	face->SetPreEdge(hpre);
}

void Halfedge::SetSym(Halfedge *s)
{
	sym = s;
}

void Halfedge::SetHalfEdgeID(unsigned int i)
{
	HalfEdgeID = i;
}

Face * Halfedge::GetFace()
{
	return face;
}

Vertex * Halfedge::GetVertex()
{
	return vert;
}

Halfedge * Halfedge::GetNext()
{
	return next;
}

Halfedge * Halfedge::GetSym()
{
	return sym;
}

unsigned int Halfedge::GetHalfEdgeID()
{
	return HalfEdgeID;
}

Halfedge * Halfedge::GetPrevious()
{
	return face->GetPreEdge(this);
}
