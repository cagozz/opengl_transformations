#version 330

in vec3 hitPoint;
in vec3 normal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    vec3 normalUnit = normalize(normal);
    vec3 lightDir = normalize(lightPos - hitPoint);

    vec3 objectColor = vec3(0.75f, 0.75f, 0.75f);
    float ambientConstant = 0.15;
    vec3 ambient = ambientConstant * lightColor;

    float diff = max(dot(normalUnit, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularConstant = 0.5;
    vec3 viewDir = normalize(viewPos - hitPoint);
    vec3 reflectDir = reflect(-lightDir, normalUnit);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularConstant * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    gl_FragColor = vec4(result, 1.0f);
}