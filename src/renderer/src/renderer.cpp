#include "renderer.h"
#include "Scene.h"

#include <glew.h>

Camera Renderer::camera;

Renderer::Renderer(){}

Renderer::~Renderer(){}

void Renderer::init(int frame_width, int frame_height)
{
	materials.init();
	framerenderer.init();

	frame.Create(frame_width, frame_height);

	camera.initArc(frame_width, frame_height);
}

void Renderer::resize(int newwidth, int newheight)
{
	frame.resize(newwidth, newheight);
	camera.windowWidth = newwidth;
	camera.windowHeight = newheight;
}

void Renderer::flush(unsigned int finalframe)
{
	materials.framerender_material(finalframe);
	framerenderer.render();
}

/////////////////////////////////// gradiant background
//https://gist.github.com/mhalber/0a9b8a78182eb62659fc18d23fe5e94e
#define SHADER_HEADER "#version 330 core\n"
#define SHADER_STR(x) #x
void GradientBackground(float top_r, float top_g, float top_b, float top_a,
	float bot_r, float bot_g, float bot_b, float bot_a)
{
	glDisable(GL_DEPTH_TEST);

	static GLuint background_vao = 0;
	static GLuint background_shader = 0;

	if (background_vao == 0)
	{
		glGenVertexArrays(1, &background_vao);

		const char* vs_src = (const char*)SHADER_HEADER SHADER_STR
		(
			out vec2 v_uv;
		void main()
		{
			uint idx = uint(gl_VertexID);
			gl_Position = vec4(idx & 1U, idx >> 1U, 0.0, 0.5) * 4.0 - 1.0;
			v_uv = vec2(gl_Position.xy * 0.5 + 0.5);
		}
		);

		const char* fs_src = (const char*)SHADER_HEADER SHADER_STR
		(
			uniform vec4 top_color;
		uniform vec4 bot_color;
		in vec2 v_uv;
		out vec4 frag_color;

		void main()
		{
			frag_color = bot_color * (1 - v_uv.y) + top_color * v_uv.y;
		}
		);
		GLuint vs_id, fs_id;
		vs_id = glCreateShader(GL_VERTEX_SHADER);
		fs_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vs_id, 1, &vs_src, NULL);
		glShaderSource(fs_id, 1, &fs_src, NULL);
		glCompileShader(vs_id);
		glCompileShader(fs_id);
		background_shader = glCreateProgram();
		glAttachShader(background_shader, vs_id);
		glAttachShader(background_shader, fs_id);
		glLinkProgram(background_shader);
		glDetachShader(background_shader, fs_id);
		glDetachShader(background_shader, vs_id);
		glDeleteShader(fs_id);
		glDeleteShader(vs_id);
		glUseProgram(background_shader);
	}

	glUseProgram(background_shader);
	GLuint top_color_loc = glGetUniformLocation(background_shader, "top_color");
	GLuint bot_color_loc = glGetUniformLocation(background_shader, "bot_color");
	glUniform4f(top_color_loc, top_r, top_g, top_b, top_a);
	glUniform4f(bot_color_loc, bot_r, bot_g, bot_b, bot_a);

	glBindVertexArray(background_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}

/////////////////////////////////// render functions

inline static void selectmaterial(SceneObject* obj, Materials& materials)
{
	switch (obj->type_material)
	{
	case MaterialType::Default:
		materials.default_material(obj->TransformMatrix());
		break;
	case MaterialType::Colored:
		materials.colored_material(obj->TransformMatrix(), obj->color);
		break;
	case MaterialType::Phong:
		materials.phong_material(obj->TransformMatrix(),
								obj->ModelMatrix(),
								Renderer::camera.Front,
								glm::vec3(0.8,0.8,0.8));
		break;
	case MaterialType::Checkboard:
		materials.checkboard_material(obj->TransformMatrix());
		break;
	case MaterialType::Diffuse:
		break;
	default:
		break;
	}
}

inline static int
rendermode(DrawMode mode)
{
	switch (mode)
	{
	case KIND_TRIANGLE:
		return GL_TRIANGLES;
		break;
	case KIND_LINES:
		return GL_LINES;
		break;
	case KIND_LINE_LOOP:
		return GL_LINE_LOOP;
		break;
	default:
		return 0;
		break;
	}
}

void Renderer::Draw_sceneobjs(DrawMode mode)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GradientBackground(0.7f, 0.7f, 0.7f, 1.0f,
					   0.2f, 0.2f, 0.2f, 1.0f);

	//render all you want here
	for (auto obj : Scene::scene_objs)
	{
		//draw bounding box
		//Draw_boundingbox(Scene::viewer_bbox, obj->buffers.bmax, obj->buffers.bmin);

		//calculate vp camera matrix..
		obj->transformation.vp_matrix =
			camera.GetProjectionMatrix(frame.AspectRatio()) * camera.GetViewMatrix();

		//render 
		{
			obj->type_material = MaterialType::Phong;
			selectmaterial(obj, materials);

			glBindVertexArray(obj->buffers.vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->buffers.ibo);

			glDrawElements(rendermode(mode), obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);
		}
	}
}

void Renderer::Draw_object(SceneObject* obj, DrawMode mode)
{
	//calculate vp camera matrix..
	obj->transformation.vp_matrix =
		camera.GetProjectionMatrix(frame.AspectRatio()) * camera.GetViewMatrix();

	selectmaterial(obj, materials);

	glBindVertexArray(obj->buffers.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->buffers.ibo);

	glDrawElements(rendermode(mode), obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);
}

void Renderer::Draw_boundingbox(SceneObject * obj, glm::vec3 bmax, glm::vec3 bmin)
{
	//calculate vp camera matrix..
	obj->transformation.vp_matrix =
		camera.GetProjectionMatrix(frame.AspectRatio()) * camera.GetViewMatrix();

	//calculate model matrix
	glm::vec3 size = bmax - bmin;
	glm::vec3 center = (bmax + bmin) / 2.0f;
	obj->transformation.matrix = 
		glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);

	selectmaterial(obj, materials);

	glBindVertexArray(obj->buffers.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->buffers.ibo);

	glDrawElements(GL_LINE_LOOP, obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_LINE_LOOP, obj->buffers.num_indecies, GL_UNSIGNED_INT, (GLvoid*)(obj->buffers.num_indecies * sizeof(GLuint)));
	glDrawElements(GL_LINES, obj->buffers.num_indecies * 2, GL_UNSIGNED_INT, (GLvoid*)(obj->buffers.num_indecies * 2 * sizeof(GLuint)));
}
