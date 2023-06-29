#ifndef SCENE_H
#define SCENE_H

#include "mesh.h"
#include "camera.h"
#include "parser.h"
#include <GLFW/glfw3.h>

#define SPACE ImGui::Spacing();ImGui::Spacing();

enum shaders {TOON, PHONG};
bool ButtonCenteredOnLine(const char*, float);

struct Light
{
	Vec3f position;
	Vec3f color;
};

class Scene
{
private:
	Camera camera;
	Mesh object;
	Light light;

	GLFWwindow* window;
	unsigned int shader;
	void createShader(const char* vertex, const char* fragment);

	//gui inputs
	Vec3f line[2];
	Vec3f point;
	Mesh plane;
	bool arbAxisActive;
	bool planeActive;
	bool pointActive;
	int shaderSelector;

	Vec3f pos;

public:

	Scene(int width, int height, GLFWwindow* window);

	void draw();
	Camera& getCamera() { return camera; }
	void gui(unsigned int);

	void addObject(const char* objectFile);
	void setShader(const char* vertexFileName, const char* fragmentFileName);
};

#endif // !SCENE_H
