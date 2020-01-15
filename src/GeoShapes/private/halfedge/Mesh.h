#pragma once
#include <vector>
#include "Face.h"
#include "Vertex.h"
#include "Halfedge.h"

class Mesh
{
public:
	Mesh();

	~Mesh();

	void create();

	void CreatCube();

	void CalculateSYM();

	void AddVertex(Halfedge *h, glm::vec3 pos);

	void TriangulateQuad(Face *f);

	void Triangulate(Face *f);

	std::vector<glm::vec3> CalculateCentroid();

	std::vector<glm::vec3> CalculateEdgeVertex(std::vector<glm::vec3>);

	void SmoothVertex(std::vector<glm::vec3>, std::vector<glm::vec3>);

	void Quadrangulate(glm::vec3 ct, std::vector<Halfedge*> midEdge);

	void Subdivision(std::vector<glm::vec3>, std::vector<glm::vec3>);

	void Extrude(Face *f);
	void Extrude(Face *f,float offset);

	void Collapse(Halfedge *h);

	void Collapse(Face *f);

	int count;			 // The number of indices stored in bufIdx.
	unsigned int vao;
	unsigned int bufIdx; // A Vertex Buffer Object that we will use to store triangle indices (GLuints)
	unsigned int bufPos; // A Vertex Buffer Object that we will use to store mesh vertices (vec4s)
	unsigned int bufNor; // A Vertex Buffer Object that we will use to store mesh normals (vec4s)
	unsigned int bufCol; // Can be used to pass per-vertex color information to the shader, but is currently unused.

	std::vector<Face*> faces;
	std::vector<Halfedge*> edges;
	std::vector<Vertex*> vertices;
};