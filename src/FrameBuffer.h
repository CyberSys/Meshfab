#pragma once

class Frambuffer
{
public:
	Frambuffer();

	~Frambuffer();

	void Create(int width, int height);

	unsigned int ColorTexture_Get();

	unsigned int DepthTexture_Get();

	float AspectRatio();

	void Use();

	void Use_Prevframe();

private:
	unsigned int m_id;
	unsigned int colortexture;
	unsigned int depthtexture;
	int m_width;
	int m_height;

	//for reuse prev one
	int prev_frame;
};