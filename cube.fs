#version 330 core
out vec4 FragColor;
 
in vec3 normal;
in vec3 fragPos;
in vec3 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{    
    FragColor = vec4(fragColor, 0.8);
}