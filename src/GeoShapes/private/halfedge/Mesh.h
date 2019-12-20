#pragma once
#include <vector>
#include "Face.h"
#include "Vertex.h"
#include "Halfedge.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Halfedge*>, std::vector<Face*>, std::vector<Vertex*>);
	~Mesh();

	void draw();

	void SetHalfEdge(Halfedge*);

	void SetFace(Face*);

	void SetVertex(Vertex*);

	Halfedge* GetEdgeByNum(unsigned int);

	Face* GetFaceByNum(unsigned int);

	Vertex* GetVertexByNum(unsigned int);

	int GetEgdeNum();

	int GetFaceNum();

	int GetVertexNum();

	void create();

	void CreatCube();

	void CreateFromOBJ(std::vector<glm::vec3> vert_pos, std::vector<glm::vec2> vert_vt,
		std::vector<glm::vec3> vert_nor, std::vector<std::vector<glm::vec3>> faceVector);

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

	void SetInfluenceFactor(Vertex*);
private:
	std::vector<Halfedge*> edges;
	std::vector<Face*> faces;
	std::vector<Vertex*> vertices;

	int count;     // The number of indices stored in bufIdx.
	unsigned int vao;
	unsigned int bufIdx; // A Vertex Buffer Object that we will use to store triangle indices (GLuints)
	unsigned int bufPos; // A Vertex Buffer Object that we will use to store mesh vertices (vec4s)
	unsigned int bufNor; // A Vertex Buffer Object that we will use to store mesh normals (vec4s)
	unsigned int bufCol; // Can be used to pass per-vertex color information to the shader, but is currently unused.
};