#pragma once

class Frambuffer
{
public:
	Frambuffer();

	~Frambuffer();

	void Create(int width, int height);

	void resize(int newwidth, int newheight);

	unsigned int ColorTexture_Get();

	unsigned int DepthTexture_Get();

	float AspectRatio();

	void begin();

	void end();

private:
	unsigned int m_id;
	unsigned int colortexture;
	unsigned int depthtexture;
	int m_width;
	int m_height;

	//for reuse prev one
	int prev_frame;
};