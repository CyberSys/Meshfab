#pragma once

class Framerenderer
{
public:
	Framerenderer();

	~Framerenderer();

	void init();

	void render();

	unsigned int geometryID;
};