#include "mesh.h"

void Mesh::VAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Mesh::VBO()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
}

void Mesh::EBO()
{
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Vec3), &indices[0], GL_STATIC_DRAW);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}


void Mesh::create()
{
	VAO();	VBO();	EBO();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vec3f));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indices.size() * sizeof(Vec3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::update()
{
}

void Mesh::input(GLFWwindow* window, Vec3f &a, Vec3f &b)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		move(0, speed,0);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		move(0, -speed,0);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		move(-speed, 0,0);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		move(speed, 0,0);
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		rotate_x(-speed);
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		rotate_x(speed);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		rotate_y(speed);
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		rotate_y(-speed);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && arbAxis)
	{
		rotateArbitaryAxis(a, b, speed);
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && arbAxis)
	{
		rotateArbitaryAxis(a, b, -speed);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		reset(true);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		scale(1.003);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		scale(0.997);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		shear_x(0.007);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		shear_y(0.007);
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		shear_z(0.007);
	}


	ImGui::Spacing();ImGui::Spacing();
	if (ImGui::Button("Reset Object"))
	{
		reset(true);
	}
	ImGui::Spacing(); ImGui::Spacing();

}


void Mesh::rotateArbitaryAxis(Vec3f p1, Vec3f p2, float alpha)
{
	Vec3f vec = p2 - p1;
	Vec3f u = vec.unit();

	float d = sqrt(pow(u.y(), 2) + pow(u.z(), 2));
	float a = u.x(), b = u.y(), c = u.z();

	Mat4f translate(1);
	translate[3] = -p1.x(); translate[7] = -p1.y(); translate[11] = -p1.z();

	Mat4f rotate_around_x(1);
	rotate_around_x[5] = rotate_around_x[10] = c / d;
	rotate_around_x[9] = b / d; rotate_around_x[6] = - b / d;
	

	Mat4f rotate_around_y(1);
	rotate_around_y[0]  = rotate_around_y[10] = d / u.length();
	rotate_around_y[2]  =  -a / u.length(); rotate_around_y[8]  =  a / u.length();

	Mat4f rotate_around_z(1);
	rotate_around_z[0] = cos(alpha); rotate_around_z[1] = -sin(alpha);
	rotate_around_z[4] = sin(alpha); rotate_around_z[5] = cos(alpha);

	Mat4f undo_y(1);
	undo_y[0] = undo_y[10] = d / u.length();
	undo_y[2] =  a / u.length(); undo_y[8] = - a / u.length();

	Mat4f undo_x(1);
	undo_x[5] = undo_x[10] = c / d;
	undo_x[9] = - b / d; undo_x[6] = b / d;

	Mat4f undo_translate(1);
	undo_translate[3] = p1.x(); undo_translate[7] = p1.y(); undo_translate[11] = p1.z();

	Mat4f result = undo_translate * undo_x * undo_y * rotate_around_z * rotate_around_y * rotate_around_x * translate;

	model = result * model;
}

