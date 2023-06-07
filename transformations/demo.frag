#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

void main()
{
    vec3 lightPos = vec3(2,2,2);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 lightColor = vec3(1,1,1);
    vec3 objectColor = vec3(1.0f, 0.5f, 0.2f);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0f);
}