#version 130

uniform mat4 ModelViewProj_mat;
uniform vec3 color;

in vec3 a_Vertex;

void main(void)
{
  gl_Position = ModelViewProj_mat * vec4(a_Vertex, 1.0f);
}