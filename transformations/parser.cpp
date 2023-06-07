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

	std::vector<Vec3f> locations;
	std::vector<Vec3f> normals;

	locations.reserve(vertices);
	normals.reserve(vertices);

	obj.vertices.reserve(vertices);
	obj.indices.reserve(faces);

	for (int i = 0; i < vertices; i++)
	{
		float x, y, z;
		std::getline(file, line);
		std::istringstream(line) >> x >> y >> z;
		locations.push_back(Vec3f(x, y, z));
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

		obj.indices.push_back({ ind[0], ind[1], ind[2] });
	}

	
	for (int i = 0; i < vertices; i++)
	{
		int count = 0;
		Vec3f sum(0, 0, 0);
		for (int j = 0; j < faces; j++)
		{
			if (obj.indices[j].x == i || obj.indices[j].y == i || obj.indices[j].z == i)
			{
				Vec3f normal = (locations[obj.indices[j].y] - locations[obj.indices[j].x]).cross(locations[obj.indices[j].z] - locations[obj.indices[j].x]).unit();
				sum = sum + normal;
				count++;
			}
		}

		obj.vertices.push_back({ locations[i], sum / count });
		//obj.vertices.push_back({ locations[i], {1,1,1} });
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