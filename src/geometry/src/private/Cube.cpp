#include "Cube.h"
#include "halfedge/Mesh.h"

#include <glew.h>

Cube::Cube() {}

Cube::~Cube() {}

void add_new_vertex(Mesh& m)
{
	auto pos = m.edges[0]->GetVertex()->GetPos();
	pos.x -= 0.5;
	pos.y -= 0.5;
	m.AddVertex(m.edges[0], pos);
}

void subdivide(Mesh& m)
{
	std::vector<glm::vec3> cent = m.CalculateCentroid();
	std::vector<glm::vec3> eg = m.CalculateEdgeVertex(cent);
	m.SmoothVertex(cent, eg);
	m.Subdivision(cent, eg);

	cent.clear();
	eg.clear();
	cent = m.CalculateCentroid();
	eg = m.CalculateEdgeVertex(cent);
	//m.SmoothVertex(cent, eg);
	m.Subdivision(cent, eg);

	cent.clear();
	eg.clear();
	cent = m.CalculateCentroid();
	eg = m.CalculateEdgeVertex(cent);
	//m.SmoothVertex(cent, eg);
	m.Subdivision(cent, eg);
}

void Extrusion(Mesh& m)
{
	m.Extrude(m.faces[0], 2);
	m.Extrude(m.faces[2], 2);
	m.Extrude(m.faces[5], 2);
}

void Collapsing(Mesh& m)
{
	//collapse edge..
	//m.Collapse(m.edges[0]);

	//collapse face
	m.Collapse(m.faces[0]);
}


GeomtryInfo Cube::Generate()
{
	Mesh m;
	m.CreatCube();
	m.create();

	GeomtryInfo result;
	result.vao = m.vao;
	result.vbo = m.bufPos;
	result.nbo = m.bufNor;
	result.cbo = m.bufCol;
	result.ibo = m.bufIdx;
	result.num_indecies = m.count;

	return result;
}
