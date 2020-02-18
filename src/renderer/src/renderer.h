#pragma once
#include "camera.h"
#include "Framerenderer.h"
#include "SceneObject.h"
#include "FrameBuffer.h"
#include "Materials/Materials.h"

#include <vector>
using namespace std;

class Renderer
{
public:
	Renderer();

	~Renderer();

	void init(int frame_width, int frame_height);

	void Draw_sceneobjs(DrawMode mode);
	void Draw_object(SceneObject* obj, DrawMode mode);
	void Draw_boundingbox(SceneObject* obj, glm::vec3 bmax, glm::vec3 bmin);

	void resize(int newwidth, int newheight);

	void flush(unsigned int finalframe);

	static Camera camera;
	Frambuffer frame;
	Materials materials;
	Framerenderer framerenderer;
};