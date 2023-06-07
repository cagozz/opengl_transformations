#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 perspective;
uniform mat4 camera;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    vec4 newPos = perspective*camera*transform*vec4(aPos,1.0);

    gl_Position = newPos;
    FragPos = vec3(transform*vec4(aPos,1.0));
    Normal = mat3(transpose(inverse(transform))) * aNormal;
}