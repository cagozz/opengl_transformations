#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vector.h"
#include "matrix.h"
#include <GL/glew.h>

struct Vertex
{
	Vec4f position;
};

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<Vec3> indices;
	Mat4f transformation;
	Mat4f perspective;
	Mat4f camera;

	unsigned int shader;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

private:

	void VAO();
	void VBO();
	void EBO();

public:

	Mesh() : transformation(1), camera(1), perspective(1), vao(0), vbo(0), ebo(0), shader(0) {}
	~Mesh();
	void setShader(const char* vertex, const char* fragment);
	void create();
	void draw();
	void setPerspective(float n, float f, float r, float l, float t, float b);

	void move(float x, float y, float z) {
		Mat4f mv(1);
		mv[3]  = x;
		mv[7]  = y;
		mv[11] = z;

		transformation = mv*transformation;
	}

	void rotate_y(float alpha)
	{
		Mat4f rotate_y(1);
		rotate_y[0] = cos(alpha);
		rotate_y[2] = sin(alpha);
		rotate_y[8] = -sin(alpha);
		rotate_y[10] = cos(alpha);

		transformation = rotate_y * transformation;
	}

	void rotate_x(float alpha)
	{
		Mat4f rotate_x(1);
		rotate_x[5] = cos(alpha);
		rotate_x[6] = -sin(alpha);
		rotate_x[9] = sin(alpha);
		rotate_x[10] = cos(alpha);

		transformation = rotate_x * transformation;
	}

	void rotate_z(float alpha)
	{
		Mat4f rotate_z(1);
		rotate_z[0] = cos(alpha);
		rotate_z[1] = -sin(alpha);
		rotate_z[4] = sin(alpha);
		rotate_z[5] = cos(alpha);

		transformation = rotate_z * transformation;
	}

	void scale(float m)
	{
		Mat4f scalar(m);
		scalar[15] = 1;

		transformation = scalar * transformation;
	}

	void reset(bool check)
	{
		if (check)
		{
			transformation.set(1, 0, 0, 0,
							   0, 1, 0, 0,
							   0, 0, 1, 0,
							   0, 0, 0, 1);
		}
	}

	void rotate(float alpha, float beta)
	{
		transformation[0] = cos(beta);
		transformation[2] = sin(beta);
		transformation[4] = sin(alpha) * sin(beta);
		transformation[5] = cos(alpha);
		transformation[6] = -sin(alpha) * cos(beta);
		transformation[8] = -cos(alpha) * sin(beta);
		transformation[9] = sin(alpha);
		transformation[10] = cos(alpha) * cos(beta);
	}

	void camera_move(float x, float y, float z)
	{
		camera[3] -= x;
		camera[7] -= y;
		camera[11] -= z;
	}

	void print() { std::cout << transformation; }
	friend void parser(const char* fileName, Mesh& obj);
};


#endif // !MESH_H
