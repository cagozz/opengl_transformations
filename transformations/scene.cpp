#include "scene.h"

Scene::Scene(int width, int height, GLFWwindow* window) : camera(width, height), window(window), line{ {5, 5, 0}, {-5, -5, 0} }
{
	addObject("input.off");
}

void Scene::draw()
{
	ImGui::Begin("Controller");

	camera.input(window);
	camera.update();

	ImGui::SliderFloat3("V0", (float*) &line[0], -5, 5);
	ImGui::SliderFloat3("V1", (float*) &line[1], -5, 5);

	/*glLineWidth(2);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &line[0]);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);*/
	Mat4f I(1);
	unsigned int modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &I[0]);
	glBegin(GL_LINES);
		glVertex3f(line[0].x(), line[0].y(), line[0].z());
		glVertex3f(line[1].x(), line[1].y(), line[1].z());
	glEnd();

	glfwGetWindowSize(window, camera.getWidth(), camera.getHeight());
	glViewport(0, 0, *camera.getWidth(), *camera.getHeight());

	glUseProgram(shader);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &object.getModelMat()[0]);

	unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &camera.getProjectionMat()[0]);

	unsigned int viewLoc = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &camera.getViewMat()[0]);

	object.input(window,line[0],line[1]);
	object.draw();

	ImGui::End();
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
