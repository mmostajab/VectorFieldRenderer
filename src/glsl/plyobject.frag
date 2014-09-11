#version 130

in vec3 normal;

out vec4 outColor;

void main(void)
{
  outColor = vec4(normal, 1.0f);
}