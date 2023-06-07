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

void Mesh::rotateArbitaryAxis(Vec3f p1, Vec3f p2, float alpha)
{
	Vec3f vec = p2 - p1;
	Vec3f u = vec.unit();
	
	/*float a = u.x(), b = u.y(), c = u.z();

	Vec3f v(0,0,0);
	if (a <= b && a <= c)
		v = Vec3f(0, -c, b);
	else if (b <= a && b <= c)
		v = Vec3f(-c, 0, a);
	else
		v = Vec3f(-b, a, 0);


	Vec3f w = u.cross(v);

	Mat4f reverse(u.x(), v.x(), w.x(), 0,
				  u.y(), v.y(), w.y(), 0,
				  u.z(), v.z(), w.z(), 0,
				  0,	 0,		0,	   1);
	Mat4f normal(u.x(), u.y(), u.z(), 0,
				 v.x(), v.y(), v.z(), 0,
				 w.x(), w.y(), w.z(), 0,
				 0,		0,	   0,	  1);

	Mat4f rotate_x(1);
	rotate_x[5] = cos(alpha);
	rotate_x[6] = -sin(alpha);
	rotate_x[9] = sin(alpha);
	rotate_x[10] = cos(alpha);
	
	Mat4f result = reverse * rotate_x * normal;
	*/

	float d = sqrt(pow(u.y(), 2) + pow(u.z(), 2));
	float a = u.x(), b = u.y(), c = u.z();

	Mat4f translate(1);
	translate[3] = -p1.x(); translate[7] = -p1.y(); translate[11] = -p1.z();

	Mat4f rotate_around_x(1);
	rotate_around_x[5] = rotate_around_x[10] = c / d;
	rotate_around_x[9] = b / d; rotate_around_x[6] = -b / d;
	

	Mat4f rotate_around_y(1);
	rotate_around_y[0]  = rotate_around_y[10] = sqrt(pow(b, 2) + pow(c, 2)) / u.length();
	rotate_around_y[2]  =   a / u.length(); rotate_around_y[8]  = - a / u.length();

	Mat4f rotate_around_z(1);
	rotate_around_z[0] = cos(alpha); rotate_around_z[1] = -sin(alpha);
	rotate_around_z[4] = sin(alpha); rotate_around_z[5] = cos(alpha);

	Mat4f undo_y(1);
	undo_y[0] = undo_y[10] = sqrt(pow(b, 2) + pow(c, 2)) / u.length();
	undo_y[2] = - a / u.length(); undo_y[8] = a / u.length();

	Mat4f undo_x(1);
	undo_x[5] = undo_x[10] = c / d;
	undo_x[9] = - b / d; undo_x[6] = b / d;

	Mat4f undo_translate(1);
	undo_translate[3] = p1.x(); undo_translate[7] = p1.y(); undo_translate[11] = p1.z();

	//std::cout << undo_y * rotate_around_y;

	Mat4f result = undo_translate * undo_x * undo_y * rotate_around_z * rotate_around_y * rotate_around_x * translate;

	//std::cout << result;

	transformation = result * transformation;
}

