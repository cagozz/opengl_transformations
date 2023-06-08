#ifndef MESH_H
#define MESH_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <vector>
#include "vector.h"
#include "matrix.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vertex
{
	Vec3f position;
	Vec3f normal;
};

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<Vec3> indices;
	Mat4f model;
	
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	float speed;

private:

	void VAO();
	void VBO();
	void EBO();

public:

	Mesh() : model(1), vao(0), vbo(0), ebo(0), speed(0.01) {}
	~Mesh();

	void create();
	void draw();

	void update();
	void input(GLFWwindow* window, Vec3f &a, Vec3f &b);

	void rotateArbitaryAxis(Vec3f p1, Vec3f p2, float alpha);

	Mat4f getModelMat() { return model; }


	void move(float x, float y, float z) {
		Mat4f mv(1);
		mv[3]  = x;
		mv[7]  = y;
		mv[11] = z;

		model = mv*model;
	}

	void rotate_x(float alpha)
	{
		Mat4f rotate_x(1);
		rotate_x[5] = cos(alpha);
		rotate_x[6] = -sin(alpha);
		rotate_x[9] = sin(alpha);
		rotate_x[10] = cos(alpha);

		model = rotate_x * model;
	}

	void rotate_y(float alpha)
	{
		Mat4f rotate_y(1);
		rotate_y[0] = cos(alpha);
		rotate_y[2] = sin(alpha);
		rotate_y[8] = -sin(alpha);
		rotate_y[10] = cos(alpha);

		model = rotate_y * model;
	}

	void rotate_z(float alpha)
	{
		Mat4f rotate_z(1);
		rotate_z[0] = cos(alpha);
		rotate_z[1] = -sin(alpha);
		rotate_z[4] = sin(alpha);
		rotate_z[5] = cos(alpha);

		model = rotate_z * model;
	}

	void scale(float m)
	{
		Mat4f scalar(m);
		scalar[15] = 1;

		model = scalar * model;
	}

	void shear_x(float m)
	{
		Mat4f shear(1);
		shear[1] = shear[2] = m;

		model = shear * model;
	}
	void shear_y(float m)
	{
		Mat4f shear(1);
		shear[4] = shear[6] = m;

		model = shear * model;
	}
	void shear_z(float m)
	{
		Mat4f shear(1);
		shear[8] = shear[9] = m;

		model = shear * model;
	}

	void reset(bool check)
	{
		if (check)
		{
			model.set(1, 0, 0, 0,
					  0, 1, 0, 0,
					  0, 0, 1, 0,
					  0, 0, 0, 1);
		}
	}
	
	friend void parser(const char* fileName, Mesh& obj);
};


#endif // !MESH_H
