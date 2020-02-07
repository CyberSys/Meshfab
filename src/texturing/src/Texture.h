#pragma once

class Texture
{
public:
	static unsigned int Create2D(const char* filename);
	static unsigned int Create3D(int width, int height,int depth, void* data);
	static unsigned int CreateEmpty2D(int width, int height);
	static unsigned int CreateEmpty3D(int width, int height, int depth);
	static unsigned int FillData2D(void* data);
	static unsigned int FillData3D(void* data);
};