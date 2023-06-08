#include "camera.h"

void Camera::setPerspective(float n, float f, float r, float l, float t, float b)
{
	projection[0] = 2 * n / (r - l);		projection[2] = (r + l) / (r - l);
	projection[5] = 2 * n / (t - b);		projection[6] = (t + b) / (t - b);
	projection[10] = -(f + n) / (f - n);	projection[11] = -2 * (f * n) / (f - n);

	projection[14] = -1;
}

Camera::Camera(int width, int height) : position(0, 0, 5), up(0, 1, 0), projection(0), speed(0.1)
{
	direction = (position - Vec3f(0, 0, 0)).normalize();
	Vec3f right = up.cross(direction);

	Mat4f align(right.x()		, right.y()		  , right.z()		, 0,
				up.x()			, up.y()		  , up.z()			, 0,
				direction.x()   , direction.y()   , direction.z()   , 0,
				0				, 0				  , 0				, 1);

	Mat4f translate(1);
	translate[3] = -position.x(), translate[7] = -position.y(), translate[11] = -position.z();

	view = align * translate;

	float near = 0.1;
	float far = 100;

	float aspectRatio = (float)width / height;
	float angle = 45;
	float scale = tan(angle * 0.5 * 3.141592 / 180) * near;
	float r = aspectRatio * scale, l = -r;
	float t = scale, bottom = -t;

	setPerspective(near, far, r, l, t, bottom);
}

void Camera::update()
{
	view = lookAt(position, position - direction, up);
}

void Camera::input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		position = position - speed * direction;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		position = position + speed * direction;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		position = position -  up.cross(direction).normalize() * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		position = position + up.cross(direction).normalize() * speed;
	}
}

void Camera::move(float x, float y, float z)
{
	position.x() += x;
	position.y() += y;
	position.z() += z;
}

void Camera::rotate(float x, float y, float z)
{
}

Mat4f Camera::lookAt(Vec3f position, Vec3f target, Vec3f up)
{
	Vec3f direction = (position - target).normalize();
	Vec3f right = up.cross(direction);

	Mat4f align(right.x()		, right.y()		  , right.z()		, 0,
				up.x()			, up.y()		  , up.z()			, 0,
				direction.x()   , direction.y()   , direction.z()   , 0,
				0				, 0				  , 0				, 1);

	Mat4f translate(1);
	translate[3] = -position.x(), translate[7] = -position.y(), translate[11] = -position.z();

	return align * translate;
}
