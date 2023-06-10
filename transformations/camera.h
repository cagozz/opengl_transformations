#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "matrix.h"
#include <GLFW/glfw3.h>

class Camera
{
private:
	Vec3f position, direction, up;
	Mat4f projection, view;

	float speed;
	int width, height;

	void setPerspective(float n, float f, float r, float l, float t, float b);

public:
	Camera(int width, int height);

	int* getHeight() { return &height; }
	int* getWidth() { return &width; }
	Vec3f& getPos() { return position; }

	void update();
	void updatePerspective(float aspectRatio);
	void input(GLFWwindow* window);

	void move(float x, float y, float z);
	void rotate(float x, float y, float z);

	Mat4f lookAt(Vec3f position, Vec3f target, Vec3f up);

	friend class Scene;
};

#endif // !CAMERA_H
