#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 normal;
out vec3 hitPoint;

void main()
{
    vec4 newPos = projection*view*model*vec4(aPos,1.0);

    gl_Position = newPos;
    hitPoint = vec3(model*vec4(aPos,1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;
}