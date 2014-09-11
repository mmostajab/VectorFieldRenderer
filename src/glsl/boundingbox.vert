#version 130

uniform mat4 ModelViewProj_mat;

in vec3 a_Vertex;

out vec4 color;

void main(void)
{
  color = vec4(1, 0, 0, 1);
  gl_Position = ModelViewProj_mat * vec4(a_Vertex, 1.0f);
}