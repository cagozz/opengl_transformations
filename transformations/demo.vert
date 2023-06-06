#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 transform;
uniform mat4 perspective;
uniform mat4 camera;

void main()
{
    vec4 newPos = perspective*camera*transform*aPos;

    gl_Position = newPos;
}