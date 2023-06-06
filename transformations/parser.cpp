#include "parser.h"

void parser(const char* fileName, Mesh& obj)
{
	std::fstream file;
	file.open(fileName, std::ios::in);

	std::string line;

	int vertices, faces;
	std::getline(file, line);

	if (line == "OFF")
	{
		std::getline(file, line);
		std::istringstream(line) >> vertices >> faces;
	}
	else
	{	
		std::istringstream(line) >> vertices >> faces;
	}

	obj.vertices.reserve(vertices);
	obj.indices.reserve(faces);
	//obj.normals.reserve(faces);

	for (int i = 0; i < vertices; i++)
	{
		double x, y, z;
		std::getline(file, line);
		std::istringstream(line) >> x >> y >> z;
		obj.vertices.push_back({ Vec4f(x, y, z, 1) });
	}

	for (int i = 0; i < faces; i++)
	{
		int data;
		unsigned int ind[3] = { 0,0,0 };
		std::getline(file, line);
		std::istringstream(line) >> data;
		if (data == 3)
		{
			std::istringstream(line) >> data >> ind[0] >> ind[1] >> ind[2];
		}

		//Vec3f normal = (obj.vertices[ind[1]] - obj.vertices[ind[0]]).cross(obj.vertices[ind[2]] - obj.vertices[ind[0]]);

		//obj.normals.push_back(normal);
		obj.indices.push_back({ ind[0], ind[1], ind[2] });
	}

}

Shader shaderParser(const char* vertexFileName, const char* fragmentFileName)
{
	Shader out;

	std::fstream file;
	file.open(vertexFileName, std::ios::in);

	std::string line;
	std::stringstream data;

	while (std::getline(file, line))
	{
		data << line << "\n";
	}
	file.close();

	out.vertex = data.str();
	data.str("");

	file.open(fragmentFileName, std::ios::in);

	while (std::getline(file, line))
	{
		data << line << "\n";
	}
	file.close();

	out.fragment = data.str();

	return out;
}



/*
   glfwGetFramebufferSize(window, &width, &height);

		const float aspectRatio = (float)width / height;
		float sx = aspectRatio > 1.0f ? aspectRatio : 1.0f;
		float sy = aspectRatio > 1.0f ? 1.0f : 1.0f / aspectRatio;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluOrtho2D(-sx, sx, -sy, sy);
		glOrtho(-sx, sx, -sy, sy, -1, 1);
		glViewport(0, 0, width, height);

*/

/*unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, obj.vertices.size() * sizeof(Vec3f), &obj.vertices[0], GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.indices.size() * sizeof(Vec3), &obj.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vec3f), (void*)0);*/