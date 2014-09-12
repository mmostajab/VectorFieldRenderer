#version 130

uniform vec3 color;

in vec3 pos;
out vec4 outColor;

void main(void)
{
  //outColor = vec4(1, 1, 1, 1);
  outColor = vec4(color, 1.0f);
  //outColor = vec4(color * (1 - (abs(pos.x) + abs(pos.y) + abs(pos.z)) / 20.0f), 1.0f);
}