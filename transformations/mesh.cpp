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
	glDeleteShader(shader);
}

void Mesh::setShader(const char* vertex, const char* fragment)
{
	unsigned int t_vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int t_fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(t_vertex, 1, &vertex, NULL);
	glCompileShader(t_vertex);

	glShaderSource(t_fragment, 1, &fragment, NULL);
	glCompileShader(t_fragment);

	shader = glCreateProgram();
	
	glAttachShader(shader, t_vertex);
	glAttachShader(shader, t_fragment);
	glLinkProgram(shader);

	glDeleteShader(t_vertex);
	glDeleteShader(t_fragment);
}

void Mesh::create()
{
	VAO();	VBO();	EBO();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);


	glUseProgram(shader);
	unsigned int transformLoc = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &transformation[0]);

	unsigned int perspectiveLoc = glGetUniformLocation(shader, "perspective");
	glUniformMatrix4fv(perspectiveLoc, 1, GL_TRUE, &perspective[0]);
	
	unsigned int cameraLoc = glGetUniformLocation(shader, "camera");
	glUniformMatrix4fv(cameraLoc, 1, GL_TRUE, &camera[0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indices.size() * sizeof(Vec3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::setPerspective(float n, float f, float r, float l, float t, float b)
{
	perspective[0] = 2 * n / (r - l); perspective[2] = (r + l) / (r - l);
	perspective[5] = 2 * n / (t - b); perspective[6] = (t + b) / (t - b);
	perspective[10] = -(f + n) / (f - n); perspective[11] = -2 * (f * n) / (f - n);
	perspective[15] = 0;
	perspective[14] = -1;
}









