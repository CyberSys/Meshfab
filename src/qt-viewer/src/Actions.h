#pragma once
#include <list>

//renderer module
#include "Scene.h"

enum Action_Kind
{
	KIND_ADD_CUBE,
	KIND_ADD_SPHERE,
	KIND_ADD_CYLINDER,
	KIND_ADD_CONE,
	KIND_ADD_MODEL,
	KIND_ADD_VOLUME,
	KIND_ADD_GRID,
	KIND_ADD_BBOX,

	//activate
	KIND_ACTIVE_WIREFRAME,

	//inputs
	KIND_INPUT_MOUSE,
	KIND_INPUT_CURSOR,
	KIND_INPUT_WHEEL
};

struct Action
{
	Action_Kind kind;

	union
	{
		struct
		{
			int button;
			int press;
			double press_posx;
			double press_posy;
		}mouse;

		struct
		{
			double xpos;
			double ypos;
		}cursor;

		struct
		{
			double xoffset;
			double yoffset;
		}wheel;

		char* filepath;
	};
};

class Actions
{
public:
	//actions-add
	static void Add_Cube();
	static void Add_Sphere();
	static void Add_Cylinder();
	static void Add_Cone();
	static void Add_Model(char* filepath);
	static void Add_Volume();
	static void Add_Grid();
	static void Add_BBox();

	//activate states
	static void Active_Wireframe();

	//actions-inputs
	static void Input_MousePress(int button, int act, double xpos, double ypos);
	static void Input_CursorMove(double xpos, double ypos);
	static void Input_MouseWheel(double xoffset, double yoffset);


	static void Excute();
	static std::list<Action> list;
};
