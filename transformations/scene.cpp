#include "scene.h"

Scene::Scene(int width, int height, GLFWwindow* window) : camera(width, height), window(window)
{
	addObject("input.off");
}

void Scene::draw()
{
	camera.input(window);
	camera.update();

	object.input(window);

	glUseProgram(shader);
	unsigned int modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &object.getModelMat()[0]);

	unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &camera.getProjectionMat()[0]);

	unsigned int viewLoc = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &camera.getViewMat()[0]);

	object.draw();
}

void Scene::createShader(const char* vertex, const char* fragment)
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


void Scene::addObject(const char* objectFile)
{
	parser(objectFile, object);
	object.create();
}

void Scene::setShader(const char* vertexFileName, const char* fragmentFileName)
{
	Shader newShader = shaderParser(vertexFileName, fragmentFileName);
	createShader(newShader.vertex.c_str(), newShader.fragment.c_str());
}
