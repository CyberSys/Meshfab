#pragma once
#include <list>

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
			int mods;
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

	//actions-inputs
	static void Input_MousePress(int button, int act, int mods, double xpos, double ypos);
	static void Input_CursorMove(double xpos, double ypos);
	static void Input_MouseWheel(double xoffset, double yoffset);


	static void Excute();
	static std::list<Action> list;
};
