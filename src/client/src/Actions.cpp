#include "Actions.h"
#include <assert.h>

//renderer module
#include "Scene.h"
#include "renderer.h"

//geomtry module
#include "Shape3D.h"

std::list<Action> Actions::list;

void Actions::Add_Cube()
{
	Action action;
	action.kind = KIND_ADD_CUBE;
	list.push_front(action);
}

void Actions::Add_Sphere()
{
	Action action;
	action.kind = KIND_ADD_SPHERE;
	list.push_front(action);
}

void Actions::Add_Cylinder()
{
	Action action;
	action.kind = KIND_ADD_CYLINDER;
	list.push_front(action);
}

void Actions::Add_Cone()
{
	Action action;
	action.kind = KIND_ADD_CONE;
	list.push_front(action);
}

void Actions::Add_Model()
{
	Action action;
	action.kind = KIND_ADD_MODEL;
	list.push_front(action);
}

void Actions::Add_Volume()
{
	Action action;
	action.kind = KIND_ADD_VOLUME;
	list.push_front(action);
}

void Actions::Add_Grid()
{
	Action action;
	action.kind = KIND_ADD_GRID;
	list.push_front(action);
}

void Actions::Add_BBox()
{
	Action action;
	action.kind = KIND_ADD_BBOX;
	list.push_front(action);
}

void Actions::Input_MousePress(int button, int act, int mods, double xpos, double ypos)
{
	Action action;
	action.kind = KIND_INPUT_MOUSE;
	action.mouse.press = act;
	action.mouse.button = button;
	action.mouse.mods = mods;
	action.mouse.press_posx = xpos;
	action.mouse.press_posy = ypos;
	list.push_front(action);
}

void Actions::Input_CursorMove(double xpos, double ypos)
{
	Action action;
	action.kind = KIND_INPUT_CURSOR;
	action.cursor.xpos = xpos;
	action.cursor.ypos = ypos;
	list.push_front(action);
}

void Actions::Input_MouseWheel(double xoffset, double yoffset)
{
	Action action;
	action.kind = KIND_INPUT_WHEEL;
	action.wheel.xoffset = xoffset;
	action.wheel.yoffset = yoffset;
	list.push_front(action);
}

//exute all commands comes from ui
void Actions::Excute()
{
	while (list.size() != 0)
	{
		auto action = list.back();

		switch (action.kind)
		{
		case KIND_ADD_CUBE:
			{
				//CG module
				GeomtryInfo new_cube = Shape3D::Create_Cube();

				//renderer module
				SceneObject *new_obj = new SceneObject(new_cube);
				Scene::Add(new_obj);
			}
			break;
		case KIND_ADD_SPHERE:
			break;
		case KIND_ADD_CONE:
			break;
		case KIND_ADD_CYLINDER:
			break;
		case KIND_ADD_VOLUME:
			break;
		case KIND_ADD_MODEL:
			{
				//{D:\\_GameEngines_Assets\\Models\\vigtation\\Tree 02\\Tree.obj}
				//D:\\Mixamo_Animations\\Jumping.fbx
				//CG module
				vector<GeomtryInfo> new_model = 
					Shape3D::Create_Model("D:\\Mixamo_Animations\\Jumping.fbx");

				//renderer module
				for (auto part : new_model)
				{
					//send model parts to renderer as seperate objs
					SceneObject *new_obj = new SceneObject(part);
					Scene::Add(new_obj);
				}
			}
			break;
		case KIND_ADD_GRID:
			{
				//CG module
				GeomtryInfo grid = Shape3D::Create_Grid();
				SceneObject *new_obj = new SceneObject(grid);
				Scene::viewer_grid = new_obj;
			}
			break;
		case KIND_ADD_BBOX:
		{
			//CG module
			GeomtryInfo bbox = Shape3D::Create_BBox();
			SceneObject *new_obj = new SceneObject(bbox);
			Scene::viewer_bbox = new_obj;
		}
		break;
		//inputs
		case KIND_INPUT_MOUSE:
			{
				if (action.mouse.button == 0 && action.mouse.press == 1)
				{
					Renderer::camera.mouseLeftDown = true;
					Renderer::camera.prevX = (float)action.mouse.press_posx;
					Renderer::camera.prevY = (float)action.mouse.press_posy;
					Renderer::camera.prevquat = Renderer::camera.quat;
				}
				else if (action.mouse.button == 0 && action.mouse.press == 0)
				{
					Renderer::camera.mouseLeftDown = false;
				}
			}
			break;
		case KIND_INPUT_CURSOR:
			{
				if (Renderer::camera.mouseLeftDown)
				{
					Renderer::camera.mouseX = (float)action.cursor.xpos;
					Renderer::camera.mouseY = (float)action.cursor.ypos;
					Renderer::camera.Arcball_rotate();
				}
			}
			break;
		case KIND_INPUT_WHEEL:
			{
				Renderer::camera.ProcessMouseScroll((float)action.wheel.yoffset);
			}
			break;
		default:
			assert("no action kind to excute!!");
			break;
		}

		list.pop_back();
	}
}
