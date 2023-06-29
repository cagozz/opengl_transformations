#include "scene.h"

Scene::Scene(int width, int height, GLFWwindow* window) : camera(width, height), window(window), line{ {5, 5, 0}, {-5, -5, 0} },
														  arbAxisActive(false), planeActive(true), point{0,0,0}
{
	light.position = Vec3f(2, 2, 2);
	light.color = Vec3f(1, 1, 1);
	addObject("input.off");
	glLineWidth(2);
	glPointSize(6);

	plane.vertices.push_back({ { -10,0,10 }, { 0,1,0 } });
	plane.vertices.push_back({ { 10,0,10 }, { 0,1,0 } });
	plane.vertices.push_back({ { 10,0,-10 }, { 0,1,0 } });
	plane.vertices.push_back({ { -10,0,-10 }, { 0,1,0 } });

	plane.indices.push_back({ 0,1,2 });
	plane.indices.push_back({ 0,2,3 });
	pos = plane.vertices[0].position;

	plane.create();
}

void Scene::draw()
{
	ImGui::Begin("Controller", 0, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);
	camera.input(window);
	camera.update();

	unsigned int modelLoc = glGetUniformLocation(shader, "model");

	gui(modelLoc);
	
	glfwGetWindowSize(window, camera.getWidth(), camera.getHeight());
	glViewport(0, 0, *camera.getWidth(), *camera.getHeight());

	glUseProgram(shader);

	glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, (float*) &light.position);
	glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, (float*) &light.color);
	glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, (float*) &camera.getPos());

	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &object.model[0]);

	unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, &camera.projection[0]);

	unsigned int viewLoc = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &camera.view[0]);

	
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

bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Button(label);
}

void Scene::gui(unsigned int modelLoc)
{
	SPACE;
	if (ButtonCenteredOnLine("Reset Object", 0.5f))
	{
		object.reset(true);
	}
	SPACE;
	ImGui::Checkbox("Activate Arbitary Line", &arbAxisActive);
	object.setArbAxis(arbAxisActive);
	SPACE
		if (arbAxisActive)
		{
			ImGui::Text("ROTATE WITH 'T' and 'Y' KEYS");
			SPACE
				ImGui::SliderFloat3("V0", (float*)&line[0], -5, 5);
			SPACE
				ImGui::SliderFloat3("V1", (float*)&line[1], -5, 5);
			Mat4f I(1);
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &I[0]);
			glBegin(GL_LINES);
			glVertex3f(line[0].x(), line[0].y(), line[0].z());
			glVertex3f(line[1].x(), line[1].y(), line[1].z());
			glEnd();
			SPACE
				if (ImGui::Button("Reset Axis"))
				{
					line[0] = Vec3f(5, 5, 0);
					line[1] = Vec3f(-5, -5, 0);
				}
		}
	SPACE;
	ImGui::Checkbox("Activate Point for Scale", &pointActive);
	SPACE;
	if (pointActive)
	{
		ImGui::Text("SCALE WITH 'LEFT SHIFT' and 'LEFT CTRL'");
		SPACE;
		Mat4f I(1);
		ImGui::SliderFloat3("Point", (float*)&point, -5, 5);
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &I[0]);
		object.fixedPoint = point;
		glBegin(GL_POINTS);
		glVertex3f(point.x(), point.y(), point.z());
		glEnd();
		SPACE;
		if (ImGui::Button("Reset Point"))
		{
			point = Vec3f(0, 0, 0);
		}
		SPACE;
	}
	SPACE;
	ImGui::Checkbox("Activate Arbitary Plane (HERE IS NOT READY)", &planeActive);
	if (planeActive)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &plane.model[0]);
		plane.draw();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		SPACE
			if (ImGui::Button("Rotate Plane"))
			{
				plane.rotate_z(15);
				plane.vertices[0].normal = plane.model * plane.vertices[0].normal;
				pos = plane.model * pos;
				plane.pos = pos;
			}
		ImGui::SameLine();
		if (ImGui::Button("REFLECT"))
		{
			object.reflect(plane);
		}
		ImGui::SameLine();
		if (ImGui::Button("RESET"))
		{
			plane.model = Mat4f(1);
			plane.vertices[0].normal = Vec3f(0, 1, 0);
		}
	}
	SPACE
	{
	ImGui::Text("Light Position");
	SPACE
	ImGui::SliderFloat3("XYZ", (float*)&light.position, -10, 10);
	ImGui::SameLine();
	if (ImGui::Button("Reset Light"))
	{
		light.position = Vec3f(2, 2, 2);
	}
	SPACE
	ImGui::Text("Light Color");
	SPACE
	ImGui::SliderFloat3("RGB", (float*)&light.color, 0, 1);
	ImGui::SameLine();
	if (ImGui::Button("Reset Color"))
	{
		light.color = Vec3f(1, 1, 1);
	}
	}


	SPACE; SPACE; SPACE; SPACE; SPACE;
	ImGui::Text("Select Shader: ");
	ImGui::SameLine();
	ImGui::RadioButton("Toon Shader", &shaderSelector, 0);
	ImGui::SameLine();
	ImGui::RadioButton("Phong Shader", &shaderSelector, 1);
	SPACE;
	if (ButtonCenteredOnLine("Apply", 0.5f))
	{
		if (shaderSelector == 0)
		{
			setShader("toon.vert", "toon.frag");
		}
		if (shaderSelector == 1)
		{
			setShader("phong.vert", "phong.frag");
		}
	}
	SPACE; SPACE; SPACE;
	ImGui::Text("MOVE OBJECT: W A S D Q E");
	SPACE;
	ImGui::Text("MOVE CAMERA: UP DOWN RIGHT LEFT N M");
	SPACE;
	ImGui::Text("ROTATE OBJECT: I J K L U O");
	SPACE;
	ImGui::Text("SHEAR OBJECT: Z X C");
	SPACE;
	ImGui::Text("ROTATE OBJECT(ARBITRARY AXIS): T Y");
	SPACE;
	ImGui::Text("SCALE OBJECT: LEFT SHIFT and LEFT CTRL");
}