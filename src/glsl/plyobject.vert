#version 130

uniform mat4 ModelViewProj_mat;

in vec3 a_Vertex;
in vec3 a_Normal;

out vec3 normal;

void main(void)
{
  //normal = (normalize(a_Vertex) + vec3(1, 1, 1)) / 2;
  normal = (a_Normal + vec3(1, 1, 1)) / 2;
  gl_Position = ModelViewProj_mat * vec4(a_Vertex, 1.0f);
}