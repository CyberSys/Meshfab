#include "Mesh.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glew.h>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	while (edges.size() > 0)
	{
		delete edges[0];
		edges.erase(edges.begin());
	}
	while (faces.size() > 0)
	{
		delete faces[0];
		faces.erase(faces.begin());
	}
	while (vertices.size() > 0)
	{
		delete vertices[0];
		vertices.erase(vertices.begin());
	}
}


void Mesh::CreatCube()
{
	edges.clear();
	vertices.clear();
	faces.clear();
	glm::vec3 cube_vert_pos[8];

	//Store top cap verts (IDX 0 - 3)
	for (int i = 0; i < 4; i++) {
		glm::vec4 v = glm::rotate(glm::mat4(1.0f), glm::radians(i*90.0f), glm::vec3(0, 1, 0)) * glm::vec4(0.5f, 0.5f, 0.5f, 1);
		cube_vert_pos[i] = glm::vec3(v[0], v[1], v[2]);
	}
	//Store bottom cap verts (IDX 4 - 7)
	for (int i = 4; i < 8; i++) {
		glm::vec4 v = glm::rotate(glm::mat4(1.0f), glm::radians((i - 4)*90.0f), glm::vec3(0, 1, 0)) * glm::vec4(0.5f, -0.5f, 0.5f, 1);
		cube_vert_pos[i] = glm::vec3(v[0], v[1], v[2]);
	}
	for (unsigned int i = 0; i < 8; i++)
	{
		Vertex* vert = new Vertex();
		vert->SetPos(cube_vert_pos[i]);
		vert->SetVertexID(i);
		vertices.push_back(vert);
	}
	for (unsigned int i = 0; i < 6; i++)
	{
		Face* fp = new Face();
		fp->SetFaceID(i);
		faces.push_back(fp);
	}
	for (unsigned int i = 0; i < 24; i++)
	{
		Halfedge* hp = new Halfedge();
		hp->SetHalfEdgeID(i);
		edges.push_back(hp);
	}
	//set up half edges of the top cap
	edges[0]->SetFace(faces[0]);
	edges[0]->SetVertex(vertices[0]);
	edges[0]->SetNext(edges[1]);
	edges[0]->SetSym(edges[17]);
	edges[1]->SetFace(faces[0]);
	edges[1]->SetVertex(vertices[1]);
	edges[1]->SetNext(edges[2]);
	edges[1]->SetSym(edges[12]);
	edges[2]->SetFace(faces[0]);
	edges[2]->SetVertex(vertices[2]);
	edges[2]->SetNext(edges[3]);
	edges[2]->SetSym(edges[20]);
	edges[3]->SetFace(faces[0]);
	edges[3]->SetVertex(vertices[3]);
	edges[3]->SetNext(edges[0]);
	edges[3]->SetSym(edges[11]);
	//set up face of the top cap
	faces[0]->SetStartEdge(edges[0]);
	faces[0]->SetColor(glm::vec4(0, 0, 1, 1));
	faces[0]->SetNormal(glm::vec3(0, 1, 0));


	//set up half edges of the bottom cap
	edges[4]->SetFace(faces[1]);
	edges[4]->SetVertex(vertices[4]);
	edges[4]->SetNext(edges[7]);
	edges[4]->SetSym(edges[14]);
	edges[7]->SetFace(faces[1]);
	edges[7]->SetVertex(vertices[7]);
	edges[7]->SetNext(edges[6]);
	edges[7]->SetSym(edges[19]);
	edges[6]->SetFace(faces[1]);
	edges[6]->SetVertex(vertices[6]);
	edges[6]->SetNext(edges[5]);
	edges[6]->SetSym(edges[9]);
	edges[5]->SetFace(faces[1]);
	edges[5]->SetVertex(vertices[5]);
	edges[5]->SetNext(edges[4]);
	edges[5]->SetSym(edges[22]);
	//set up face of the bottom cap
	faces[1]->SetStartEdge(edges[4]);
	faces[1]->SetColor(glm::vec4(1, 1, 0, 1));
	faces[1]->SetNormal(glm::vec3(0, -1, 0));


	//set up half edges of the left cap
	edges[8]->SetFace(faces[2]);
	edges[8]->SetVertex(vertices[3]);
	edges[8]->SetNext(edges[11]);
	edges[8]->SetSym(edges[18]);
	edges[11]->SetFace(faces[2]);
	edges[11]->SetVertex(vertices[2]);
	edges[11]->SetNext(edges[10]);
	edges[11]->SetSym(edges[3]);
	edges[10]->SetFace(faces[2]);
	edges[10]->SetVertex(vertices[6]);
	edges[10]->SetNext(edges[9]);
	edges[10]->SetSym(edges[21]);
	edges[9]->SetFace(faces[2]);
	edges[9]->SetVertex(vertices[7]);
	edges[9]->SetNext(edges[8]);
	edges[9]->SetSym(edges[6]);
	//set up face of the left cap
	faces[2]->SetStartEdge(edges[8]);
	faces[2]->SetColor(glm::vec4(0, 1, 0, 1));
	faces[2]->SetNormal(glm::vec3(-1, 0, 0));


	//set up half edges of the right cap
	edges[12]->SetFace(faces[3]);
	edges[12]->SetVertex(vertices[0]);
	edges[12]->SetNext(edges[13]);
	edges[12]->SetSym(edges[1]);
	edges[13]->SetFace(faces[3]);
	edges[13]->SetVertex(vertices[4]);
	edges[13]->SetNext(edges[14]);
	edges[13]->SetSym(edges[16]);
	edges[14]->SetFace(faces[3]);
	edges[14]->SetVertex(vertices[5]);
	edges[14]->SetNext(edges[15]);
	edges[14]->SetSym(edges[4]);
	edges[15]->SetFace(faces[3]);
	edges[15]->SetVertex(vertices[1]);
	edges[15]->SetNext(edges[12]);
	edges[15]->SetSym(edges[23]);
	//set up face of the right cap
	faces[3]->SetStartEdge(edges[12]);
	faces[3]->SetColor(glm::vec4(0, 1, 1, 1));
	faces[3]->SetNormal(glm::vec3(1, 0, 0));



	//set up half edges of the front cap
	edges[16]->SetFace(faces[4]);
	edges[16]->SetVertex(vertices[0]);
	edges[16]->SetNext(edges[17]);
	edges[16]->SetSym(edges[13]);
	edges[17]->SetFace(faces[4]);
	edges[17]->SetVertex(vertices[3]);
	edges[17]->SetNext(edges[18]);
	edges[17]->SetSym(edges[0]);
	edges[18]->SetFace(faces[4]);
	edges[18]->SetVertex(vertices[7]);
	edges[18]->SetNext(edges[19]);
	edges[18]->SetSym(edges[8]);
	edges[19]->SetFace(faces[4]);
	edges[19]->SetVertex(vertices[4]);
	edges[19]->SetNext(edges[16]);
	edges[19]->SetSym(edges[7]);

	//set up face of the front cap
	faces[4]->SetStartEdge(edges[16]);
	faces[4]->SetColor(glm::vec4(1, 0, 0, 1));
	faces[4]->SetNormal(glm::vec3(0, 0, 1));


	//set up half edges of the back cap
	edges[20]->SetFace(faces[5]);
	edges[20]->SetVertex(vertices[1]);
	edges[20]->SetNext(edges[23]);
	edges[20]->SetSym(edges[2]);
	edges[23]->SetFace(faces[5]);
	edges[23]->SetVertex(vertices[5]);
	edges[23]->SetNext(edges[22]);
	edges[23]->SetSym(edges[15]);
	edges[22]->SetFace(faces[5]);
	edges[22]->SetVertex(vertices[6]);
	edges[22]->SetNext(edges[21]);
	edges[22]->SetSym(edges[5]);
	edges[21]->SetFace(faces[5]);
	edges[21]->SetVertex(vertices[2]);
	edges[21]->SetNext(edges[20]);
	edges[21]->SetSym(edges[10]);
	//set up face of the back cap
	faces[5]->SetStartEdge(edges[20]);
	faces[5]->SetColor(glm::vec4(1, 0, 1, 1));
	faces[5]->SetNormal(glm::vec3(0, 0, -1));


	//set up vertex

	vertices[0]->SetEdge(edges[0]);
	vertices[1]->SetEdge(edges[1]);
	vertices[2]->SetEdge(edges[2]);
	vertices[3]->SetEdge(edges[3]);
	vertices[4]->SetEdge(edges[4]);
	vertices[5]->SetEdge(edges[5]);
	vertices[6]->SetEdge(edges[6]);
	vertices[7]->SetEdge(edges[7]);
}

void Mesh::create()      // by Xi Yang
{
	if (faces.size() < 1)   //assert no geometry situation
		return;

	std::vector<glm::vec3> vert_pos;
	std::vector<glm::vec3> vert_nor;
	std::vector<glm::vec4> vert_color;
	std::vector<unsigned int> indx;
	Halfedge *p;
	glm::vec3 pos1, pos2, pos3, norm;
	glm::vec4 cl;
	unsigned int ptNum = 0;
	unsigned int idNum = 0;

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		//std::cout<<"inside faces loop!!!!!!!"<<std::endl;
		p = faces[i]->GetStartEdge();
		pos1 = p->GetVertex()->GetPos();
		pos2 = p->GetNext()->GetVertex()->GetPos();
		pos3 = p->GetNext()->GetNext()->GetVertex()->GetPos();
		norm = glm::normalize(glm::cross(pos1 - pos2, pos2 - pos3));
		//norm=faces[i]->GetNormal();
		cl = faces[i]->GetColor();
		ptNum = 0;
		vert_pos.push_back(pos1);
		vert_nor.push_back(norm);
		vert_color.push_back(cl);

		while (p->GetNext() != faces[i]->GetStartEdge())   //generate vertex
		{
			//std::cout<<"inside GetStartEdge!!!!!!!"<<std::endl;
			p = p->GetNext();
			pos2 = p->GetVertex()->GetPos();
			vert_pos.push_back(pos2);
			vert_nor.push_back(norm);
			vert_color.push_back(cl);
			ptNum += 1;

		}
		for (unsigned int j = idNum; j + 1 < idNum + ptNum; j++)    //generate index
		{
			//std::cout<<"inside generate index!!!!!!!"<<std::endl;
			indx.push_back(idNum);
			indx.push_back(j + 1);
			indx.push_back(j + 2);
		}
		idNum = idNum + ptNum + 1;
	}

	int IDX_COUNT = indx.size();
	int VERT_COUNT = vert_pos.size();
	std::vector<unsigned int> obj_idx;
	std::vector<glm::vec4> obj_vert_pos;
	std::vector<glm::vec4> obj_vert_nor;
	std::vector<glm::vec4> obj_vert_col;
	std::vector<glm::ivec2> obj_vert_inf;
	std::vector<glm::vec2> obj_vert_wei;
	for (int k = 0; k < IDX_COUNT; k++)
	{
		obj_idx.push_back(indx[k]);
	}
	for (int k = 0; k < VERT_COUNT; k++)
	{
		obj_vert_pos.push_back(glm::vec4(vert_pos[k], 1));
		obj_vert_nor.push_back(glm::vec4(vert_nor[k], 1));
		obj_vert_col.push_back(vert_color[k]);

	}

	count = indx.size();

	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &bufIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IDX_COUNT * sizeof(GLuint), obj_idx.data(), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, bufPos);
	glBufferData(GL_ARRAY_BUFFER, VERT_COUNT * sizeof(glm::vec4), obj_vert_pos.data(), GL_DYNAMIC_DRAW);

	//generateNor();
	//context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
	//context->glBufferData(GL_ARRAY_BUFFER, VERT_COUNT * sizeof(glm::vec4), obj_vert_nor.data(), GL_STATIC_DRAW);
	//
	//generateCol();
	//context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
	//context->glBufferData(GL_ARRAY_BUFFER, VERT_COUNT * sizeof(glm::vec4), obj_vert_col.data(), GL_STATIC_DRAW);
}

void Mesh::CalculateSYM()
{
	int num = edges.size();

	for (int i = 0; i < num; i++)
	{
		if (edges[i]->GetSym() == nullptr)
		{
			Face* f = edges[i]->GetFace();
			Halfedge *str = f->GetStartEdge();
			while (str->GetNext() != edges[i])
			{
				str = str->GetNext();
			}
			unsigned int v2 = str->GetVertex()->GetVertexID();
			unsigned int v1 = edges[i]->GetVertex()->GetVertexID();

			for (int k = 0; k < num; k++)
			{
				unsigned int s1 = edges[k]->GetVertex()->GetVertexID();
				unsigned int s2 = edges[k]->GetNext()->GetVertex()->GetVertexID();
				if ((s1 == v1) && (s2 == v2))
				{
					edges[i]->SetSym(edges[k]->GetNext());
					edges[k]->GetNext()->SetSym(edges[i]);
				}
			}

		}
	}
}

void Mesh::AddVertex(Halfedge *h, glm::vec3 pos)
{
	Halfedge *h2 = h->GetSym();

	Vertex* v3 = new Vertex();
	v3->SetPos(pos);
	Halfedge* he1b = new Halfedge();
	Halfedge* he2b = new Halfedge();
	he1b->SetVertex(h->GetVertex());
	he2b->SetVertex(h2->GetVertex());
	he1b->SetFace(h->GetFace());
	he2b->SetFace(h2->GetFace());
	he1b->SetNext(h->GetNext());
	he2b->SetNext(h2->GetNext());
	h->SetNext(he1b);
	h2->SetNext(he2b);
	h->SetVertex(v3);
	h2->SetVertex(v3);
	h->SetSym(he2b);
	he2b->SetSym(h);
	h2->SetSym(he1b);
	he1b->SetSym(h2);
	v3->SetEdge(h);
	vertices.push_back(v3);
	edges.push_back(he1b);
	edges.push_back(he2b);
	v3->SetVertexID(vertices.size() - 1);
	he1b->SetHalfEdgeID(edges.size() - 2);
	he2b->SetHalfEdgeID(edges.size() - 1);

}

void Mesh::TriangulateQuad(Face *f)
{
	Halfedge *h = f->GetStartEdge();
	Halfedge *he_a = new Halfedge();
	Halfedge *he_b = new Halfedge();
	he_a->SetVertex(h->GetVertex());
	he_b->SetVertex(h->GetNext()->GetNext()->GetVertex());
	he_a->SetSym(he_b);
	he_b->SetSym(he_a);
	Face *f2 = new Face();
	f2->SetColor(glm::vec4((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), 1));
	f2->SetNormal(f->GetNormal());
	he_a->SetFace(f2);
	h->GetNext()->SetFace(f2);
	h->GetNext()->GetNext()->SetFace(f2);
	he_b->SetFace(f);
	f2->SetStartEdge(he_a);
	he_b->SetNext(h->GetNext()->GetNext()->GetNext());
	h->GetNext()->GetNext()->SetNext(he_a);
	he_a->SetNext(h->GetNext());
	h->SetNext(he_b);
	faces.push_back(f2);
	edges.push_back(he_a);
	edges.push_back(he_b);
	f2->SetFaceID(faces.size() - 1);
	he_a->SetHalfEdgeID(edges.size() - 2);
	he_b->SetHalfEdgeID(edges.size() - 1);
}

void Mesh::Triangulate(Face *f)
{
	Halfedge *h = f->GetStartEdge();
	while (h->GetNext()->GetNext()->GetNext() != h)
	{
		TriangulateQuad(f);
	}
}

std::vector<glm::vec3> Mesh::CalculateCentroid()
{
	std::vector<glm::vec3> cent;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		Halfedge* h = faces[i]->GetStartEdge();
		glm::vec3 pos = h->GetVertex()->GetPos();;
		int ptnum = 1;
		h = h->GetNext();
		while (h != faces[i]->GetStartEdge())
		{

			pos = pos + h->GetVertex()->GetPos();
			h = h->GetNext();
			ptnum++;
		}

		pos[0] = pos[0] / ptnum;
		pos[1] = pos[1] / ptnum;
		pos[2] = pos[2] / ptnum;

		for (int m = 0; m < 3; m++)
		{
			if (fabs(pos[m]) < 1e-006)
				pos[m] = 0.0f;
		}
		cent.push_back(pos);

	}
	return cent;

}

std::vector<glm::vec3> Mesh::CalculateEdgeVertex(std::vector<glm::vec3> cent)
{
	std::vector<glm::vec3> Edgev;
	unsigned int edgeNum = edges.size();

	for (unsigned int i = 0; i < edgeNum; i++)
	{

		Halfedge *h1 = edges[i];
		Halfedge *h2 = h1->GetSym();
		glm::vec3 pos = h1->GetVertex()->GetPos();
		pos = pos + h2->GetVertex()->GetPos();
		unsigned int f1 = h1->GetFace()->GetFaceID();
		unsigned int f2 = h2->GetFace()->GetFaceID();
		pos = pos + cent[f1] + cent[f2];
		pos[0] = pos[0] / 4;
		pos[1] = pos[1] / 4;
		pos[2] = pos[2] / 4;
		for (int m = 0; m < 3; m++)
		{
			if (fabs(pos[m]) < 1e-006)
				pos[m] = 0.0f;
		}
		Edgev.push_back(pos);
	}

	return Edgev;
}

void Mesh::SmoothVertex(std::vector<glm::vec3> cent, std::vector<glm::vec3> Edgev)
{
	std::vector<unsigned int> edgelist;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		edgelist.clear();
		for (unsigned int j = 0; j < edges.size(); j++)
		{
			if (vertices[i] == edges[j]->GetVertex())
			{
				edgelist.push_back(j);
			}
		}

		if (edgelist.size() > 0)
		{
			glm::vec3 esum(0.0f), fsum(0.0f);
			for (unsigned int k = 0; k < edgelist.size(); k++)
			{

				esum = Edgev[edgelist[k]] + esum;
				unsigned int f_id = edges[edgelist[k]]->GetFace()->GetFaceID();
				fsum = cent[f_id] + fsum;
			}
			glm::vec3 pos = vertices[i]->GetPos();
			int n = edgelist.size();
			pos[0] = (n - 2)*pos[0] / n;
			pos[1] = (n - 2)*pos[1] / n;
			pos[2] = (n - 2)*pos[2] / n;
			esum[0] = esum[0] / (float)pow(n, 2);
			esum[1] = esum[1] / (float)pow(n, 2);
			esum[2] = esum[2] / (float)pow(n, 2);
			fsum[0] = fsum[0] / (float)pow(n, 2);
			fsum[1] = fsum[1] / (float)pow(n, 2);
			fsum[2] = fsum[2] / (float)pow(n, 2);
			pos = pos + esum + fsum;
			for (int m = 0; m < 3; m++)
			{
				if (fabs(pos[m]) < 1e-006)
					pos[m] = 0.0f;
			}
			vertices[i]->SetPos(pos);
		}
	}


}

void Mesh::Subdivision(std::vector<glm::vec3> cent, std::vector<glm::vec3> Edgev)
{
	int edgesnum = Edgev.size();
	std::vector<int> AddFlag;

	for (int i = 0; i < edgesnum; i++)
	{
		AddFlag.push_back(1);
	}
	for (int i = 0; i < edgesnum; i++)
	{
		if (AddFlag[i] == 1)
		{
			AddFlag[edges[i]->GetSym()->GetHalfEdgeID()] = 0;
		}
	}
	for (int i = 0; i < edgesnum; i++)
	{
		if (AddFlag[i] != 0)
		{
			this->AddVertex(edges[i], Edgev[i]);
		}
	}

	int facenum = faces.size();
	std::vector<Face*> fullfaces = faces;
	faces.clear();
	for (int i = 0; i < facenum; i++)
	{
		std::vector<Halfedge*> b4Edge = fullfaces[i]->GetEdgeList();
		std::vector<Halfedge*> midEdge;
		for (unsigned int i = 0; i < b4Edge.size(); i++)
		{
			Vertex* vi = b4Edge[i]->GetVertex();
			for (unsigned int j = 0; j < Edgev.size(); j++)
			{
				if ((vi->GetPos() == Edgev[j]) && (AddFlag[j] != 0))
					midEdge.push_back(b4Edge[i]);
			}
		}
		Quadrangulate(cent[i], midEdge);

	}
	while (fullfaces.size() > 0)
	{
		delete fullfaces[0];
		fullfaces.erase(fullfaces.begin());
	}
}

void Mesh::Quadrangulate(glm::vec3 ct, std::vector<Halfedge*> midEdge)
{
	Vertex *cen = new Vertex();
	cen->SetPos(ct);
	vertices.push_back(cen);
	cen->SetVertexID(vertices.size() - 1);
	std::vector<Halfedge*> midEdgeNext;
	std::vector<Halfedge*> tempEdge;
	std::vector<Face*> tempFace;
	unsigned int Num = midEdge.size();
	for (unsigned int i = 0; i < Num; i++)
	{
		midEdgeNext.push_back(midEdge[i]->GetNext());
	}
	for (unsigned int i = 0; i < Num; i++)
	{
		Halfedge *h3;
		Halfedge *h4 = midEdge[i];
		Halfedge *h5;
		if (i == 0)
		{
			h3 = midEdgeNext[Num - 1];
			h5 = midEdge[Num - 1];
		}
		else
		{
			h3 = midEdgeNext[i - 1];
			h5 = midEdge[i - 1];
		}
		Halfedge *h1 = new Halfedge();
		Halfedge *h2 = new Halfedge();
		Face *f1 = new Face();
		h1->SetVertex(cen);
		h2->SetVertex(h5->GetVertex());
		h1->SetFace(f1);
		h2->SetFace(f1);
		h3->SetFace(f1);
		h4->SetFace(f1);
		h4->SetNext(h1);
		h1->SetNext(h2);
		h2->SetNext(h3);
		tempEdge.push_back(h1);
		tempEdge.push_back(h2);
		f1->SetColor(glm::vec4((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), 1));
		f1->SetStartEdge(h1);
		tempFace.push_back(f1);
		cen->SetEdge(h1);
	}


	//    f->SetStartEdge(tempFace[0]->GetStartEdge());
	//    f->SetNormal();
	for (unsigned int i = 0; i < tempFace.size(); i++)
	{
		faces.push_back(tempFace[i]);
		tempFace[i]->SetFaceID(faces.size() - 1);
	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{

		if (tempEdge[i]->GetSym() == nullptr)
		{

			Halfedge* pre = tempEdge[i]->GetPrevious();
			unsigned int v2 = pre->GetVertex()->GetVertexID();

			unsigned int v1 = tempEdge[i]->GetVertex()->GetVertexID();

			for (unsigned int k = 0; k < tempEdge.size(); k++)
			{
				unsigned int s1 = tempEdge[k]->GetVertex()->GetVertexID();

				unsigned int s2 = tempEdge[k]->GetNext()->GetVertex()->GetVertexID();
				if ((s1 == v1) && (s2 == v2))
				{
					tempEdge[i]->SetSym(tempEdge[k]->GetNext());
					tempEdge[k]->GetNext()->SetSym(tempEdge[i]);
				}
			}

		}
	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{
		edges.push_back(tempEdge[i]);
		tempEdge[i]->SetHalfEdgeID(edges.size() - 1);
	}


}

void Mesh::Extrude(Face *f)
{
	f->SetNormal();
	std::vector<Halfedge*> b4Edge = f->GetEdgeList();
	std::vector<Halfedge*> tempEdge;
	std::vector<Vertex*> tempVertex;
	glm::vec3 dist = f->GetNormal();
	dist[0] = dist[0] * 0.1f;
	dist[1] = dist[1] * 0.1f;
	dist[2] = dist[2] * 0.1f;
	std::vector<Vertex*> b4Vertex;
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		Vertex *v = new Vertex();
		glm::vec3 pos = b4Edge[i]->GetVertex()->GetPos() + dist;
		v->SetPos(pos);
		tempVertex.push_back(v);
	}
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		b4Vertex.push_back(b4Edge[i]->GetVertex());
	}
	for (unsigned int i = 0; i < tempVertex.size(); i++)
	{
		tempVertex[i]->SetVertexID(vertices.size());
		vertices.push_back(tempVertex[i]);
	}
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{

		Halfedge* h1 = b4Edge[i];
		Halfedge* h1p;
		if (i == 0)
			h1p = b4Edge[b4Edge.size() - 1];
		else
			h1p = b4Edge[i - 1];
		Halfedge* h2 = h1->GetSym();
		Vertex *v1 = b4Vertex[i];
		Vertex *v2;
		if (i == 0)
			v2 = b4Vertex[b4Edge.size() - 1];
		else
			v2 = b4Vertex[i - 1];
		Vertex *v3 = tempVertex[i];
		Vertex *v4;
		if (i == 0)
			v4 = tempVertex[b4Edge.size() - 1];
		else
			v4 = tempVertex[i - 1];
		//        std::cout<<" v1  "<<v1->GetVertexID()<<std::endl;
		//        std::cout<<" v2  "<<v2->GetVertexID()<<std::endl;
		//        std::cout<<" v3  "<<v3->GetVertexID()<<std::endl;
		//        std::cout<<" v4  "<<v4->GetVertexID()<<std::endl;

		h1->SetVertex(v3);
		//if(i==b4Edge.size()-1)
		//    h1->SetVertex(v3);
		h1p->SetVertex(v4);
		v3->SetEdge(h1);
		v4->SetEdge(h1p);


		Halfedge* h1b = new Halfedge();
		Halfedge* h2b = new Halfedge();
		h1->SetSym(h1b);
		h2->SetSym(h2b);
		h1b->SetSym(h1);
		h2b->SetSym(h2);
		h1b->SetVertex(v4);
		h2b->SetVertex(v1);

		Face* nf = new Face();
		Halfedge* h3 = new Halfedge();
		Halfedge* h4 = new Halfedge();
		h1b->SetFace(nf);
		h2b->SetFace(nf);
		h3->SetFace(nf);
		h4->SetFace(nf);
		h3->SetVertex(v3);
		h4->SetVertex(v2);
		h1b->SetNext(h4);
		h4->SetNext(h2b);
		h2b->SetNext(h3);
		h3->SetNext(h1b);
		nf->SetStartEdge(h1b);
		//        std::cout<<" h1b 1 "<<h1b->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h4 4 "<<h4->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h2b  2 "<<h2b->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h3  3 "<<h3->GetVertex()->GetVertexID()<<std::endl;
		nf->SetColor(glm::vec4((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), 1));
		//nf->SetNormal();



		faces.push_back(nf);
		nf->SetFaceID(faces.size() - 1);
		//        h1b->SetHalfedgeID(edges.size());
		//        edges.push_back(h1b);
		//        h2b->SetHalfedgeID(edges.size());
		//        edges.push_back(h2b);
		tempEdge.push_back(h1b);
		tempEdge.push_back(h2b);
		tempEdge.push_back(h3);
		tempEdge.push_back(h4);


	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{

		if (tempEdge[i]->GetSym() == nullptr)
		{

			Halfedge* pre = tempEdge[i]->GetPrevious();
			unsigned int v2 = pre->GetVertex()->GetVertexID();

			unsigned int v1 = tempEdge[i]->GetVertex()->GetVertexID();

			for (unsigned int k = 0; k < tempEdge.size(); k++)
			{
				unsigned int s1 = tempEdge[k]->GetVertex()->GetVertexID();

				unsigned int s2 = tempEdge[k]->GetNext()->GetVertex()->GetVertexID();
				if ((s1 == v1) && (s2 == v2))
				{
					tempEdge[i]->SetSym(tempEdge[k]->GetNext());
					tempEdge[k]->GetNext()->SetSym(tempEdge[i]);
				}
			}

		}
	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{
		tempEdge[i]->SetHalfEdgeID(edges.size());
		edges.push_back(tempEdge[i]);
	}

}

void Mesh::Extrude(Face * f, float offset)
{
	f->SetNormal();
	std::vector<Halfedge*> b4Edge = f->GetEdgeList();
	std::vector<Halfedge*> tempEdge;
	std::vector<Vertex*> tempVertex;
	glm::vec3 dist = f->GetNormal();
	dist[0] = dist[0] * offset;
	dist[1] = dist[1] * offset;
	dist[2] = dist[2] * offset;
	std::vector<Vertex*> b4Vertex;
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		Vertex *v = new Vertex();
		glm::vec3 pos = b4Edge[i]->GetVertex()->GetPos() + dist;
		v->SetPos(pos);
		tempVertex.push_back(v);
	}
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{
		b4Vertex.push_back(b4Edge[i]->GetVertex());
	}
	for (unsigned int i = 0; i < tempVertex.size(); i++)
	{
		tempVertex[i]->SetVertexID(vertices.size());
		vertices.push_back(tempVertex[i]);
	}
	for (unsigned int i = 0; i < b4Edge.size(); i++)
	{

		Halfedge* h1 = b4Edge[i];
		Halfedge* h1p;
		if (i == 0)
			h1p = b4Edge[b4Edge.size() - 1];
		else
			h1p = b4Edge[i - 1];
		Halfedge* h2 = h1->GetSym();
		Vertex *v1 = b4Vertex[i];
		Vertex *v2;
		if (i == 0)
			v2 = b4Vertex[b4Edge.size() - 1];
		else
			v2 = b4Vertex[i - 1];
		Vertex *v3 = tempVertex[i];
		Vertex *v4;
		if (i == 0)
			v4 = tempVertex[b4Edge.size() - 1];
		else
			v4 = tempVertex[i - 1];
		//        std::cout<<" v1  "<<v1->GetVertexID()<<std::endl;
		//        std::cout<<" v2  "<<v2->GetVertexID()<<std::endl;
		//        std::cout<<" v3  "<<v3->GetVertexID()<<std::endl;
		//        std::cout<<" v4  "<<v4->GetVertexID()<<std::endl;

		h1->SetVertex(v3);
		//if(i==b4Edge.size()-1)
		//    h1->SetVertex(v3);
		h1p->SetVertex(v4);
		v3->SetEdge(h1);
		v4->SetEdge(h1p);


		Halfedge* h1b = new Halfedge();
		Halfedge* h2b = new Halfedge();
		h1->SetSym(h1b);
		h2->SetSym(h2b);
		h1b->SetSym(h1);
		h2b->SetSym(h2);
		h1b->SetVertex(v4);
		h2b->SetVertex(v1);

		Face* nf = new Face();
		Halfedge* h3 = new Halfedge();
		Halfedge* h4 = new Halfedge();
		h1b->SetFace(nf);
		h2b->SetFace(nf);
		h3->SetFace(nf);
		h4->SetFace(nf);
		h3->SetVertex(v3);
		h4->SetVertex(v2);
		h1b->SetNext(h4);
		h4->SetNext(h2b);
		h2b->SetNext(h3);
		h3->SetNext(h1b);
		nf->SetStartEdge(h1b);
		//        std::cout<<" h1b 1 "<<h1b->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h4 4 "<<h4->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h2b  2 "<<h2b->GetVertex()->GetVertexID()<<std::endl;
		//        std::cout<<" h3  3 "<<h3->GetVertex()->GetVertexID()<<std::endl;
		nf->SetColor(glm::vec4((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), 1));
		//nf->SetNormal();



		faces.push_back(nf);
		nf->SetFaceID(faces.size() - 1);
		//        h1b->SetHalfedgeID(edges.size());
		//        edges.push_back(h1b);
		//        h2b->SetHalfedgeID(edges.size());
		//        edges.push_back(h2b);
		tempEdge.push_back(h1b);
		tempEdge.push_back(h2b);
		tempEdge.push_back(h3);
		tempEdge.push_back(h4);


	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{

		if (tempEdge[i]->GetSym() == nullptr)
		{

			Halfedge* pre = tempEdge[i]->GetPrevious();
			unsigned int v2 = pre->GetVertex()->GetVertexID();

			unsigned int v1 = tempEdge[i]->GetVertex()->GetVertexID();

			for (unsigned int k = 0; k < tempEdge.size(); k++)
			{
				unsigned int s1 = tempEdge[k]->GetVertex()->GetVertexID();

				unsigned int s2 = tempEdge[k]->GetNext()->GetVertex()->GetVertexID();
				if ((s1 == v1) && (s2 == v2))
				{
					tempEdge[i]->SetSym(tempEdge[k]->GetNext());
					tempEdge[k]->GetNext()->SetSym(tempEdge[i]);
				}
			}

		}
	}
	for (unsigned int i = 0; i < tempEdge.size(); i++)
	{
		tempEdge[i]->SetHalfEdgeID(edges.size());
		edges.push_back(tempEdge[i]);
	}
}

////////////////////////////////////// collapse

//void Mesh::Collapse(Halfedge *h)
//{
//	Halfedge* he_next = h->GetNext();
//	Vertex* v_he = h->GetVertex();
//
//	int current_edge = h->GetHalfEdgeID();
//	int current_vert = h->GetVertex()->GetVertexID();
//	int next_vert = he_next->GetVertex()->GetVertexID();
//
//	for (auto e : edges)
//	{
//		if (e->GetVertex() == vertices[next_vert])
//			e->SetVertex(vertices[current_vert]);
//	}
//
//	vertices.erase(vertices.begin() + next_vert);
//	edges.erase(edges.begin() + current_edge);
//
//	//check for faces 
//	
//}

void Mesh::Collapse(Halfedge *h)
{
	//set half edges pointing on origin vertx 
	//point on new vertx
	Vertex* vert1 = h->GetVertex();
	Vertex* vert2 = h->GetNext()->GetVertex();

	Vertex* new_vert = vert2;
	glm::vec3 newpos = (vert1->GetPos() + vert2->GetPos()) / 2.0f;
	new_vert->SetPos(newpos);

	//each edge out from this vertx
	for (auto e : edges)
	{
		if (e->GetVertex() == vert1)
			e->SetVertex(new_vert);
	}

	//each edge point to this edge
	for (auto e : edges)
	{
		if (e->GetNext()->GetVertex() == vert1)
			e->GetNext()->SetVertex(new_vert);
	}


	int vert1_indx = vert1->GetVertexID();
	vertices.erase(vertices.begin() + vert1_indx);
	
	int he_indx = h->GetHalfEdgeID();
	edges.erase(edges.begin() + he_indx);

	int sym_indx = h->GetSym()->GetHalfEdgeID();
	edges.erase(edges.begin() + sym_indx);


	//update all edges id's
	for (size_t i =0 ; i < edges.size(); ++i)
	{
		edges[i]->SetHalfEdgeID(i);
	}

	//update all verts id's
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i]->SetVertexID(i);
	}
}

void Mesh::Collapse(Face* f)
{
	auto e_list = f->GetEdgeList();

	for (size_t i = 0; i < e_list.size(); ++i)
	{
		Collapse(e_list[i]);
	}

	//delete this face..
	int face_indx = f->GetFaceID();
	faces.erase(faces.begin() + face_indx);
	
	//update all faces id's
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		faces[i]->SetFaceID(i);
	}
}

