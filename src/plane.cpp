#include "plane.h"

Plane::Plane(const std::string& _pObjName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWidth): 
  Vis3DObject(_pObjName), m_Point(_pPoint), m_XDir(_pXDir), m_YDir(_pYDir), m_Len(_pLen), m_Width(_pWidth)
{
  m_ShaderPrg = new ShaderProgram("../src/glsl/simple.vert", "../src/glsl/simple.frag");
}
  
void Plane::init()
{
  m_ShaderPrg->init();
  m_ShaderPrg->bindAttribute(0, "a_Vertex");
  m_ShaderPrg->link();
  
  glm::normalize(m_XDir);
  glm::normalize(m_YDir);
  
  m_Points.push_back( m_Len / 2.0f * m_XDir - m_Width / 2.0f * m_YDir);
  m_Points.push_back( m_Len / 2.0f * m_XDir + m_Width / 2.0f * m_YDir);
  m_Points.push_back(-m_Len / 2.0f * m_XDir - m_Width / 2.0f * m_YDir);
  m_Points.push_back(-m_Len / 2.0f * m_XDir + m_Width / 2.0f * m_YDir);
  
  glGenBuffers(1, &m_BufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  glBufferData(GL_ARRAY_BUFFER, m_Points.size() * sizeof(glm::vec3), &m_Points[0], GL_STATIC_DRAW);
}

void Plane::render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat)
{
  glDisable(GL_CULL_FACE);
  
  glm::mat4 modelViewProjMat = _pProjMat * _pViewMat * glm::translate(glm::mat4(1.0f), m_Point);
  
  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("ModelViewProj_mat", modelViewProjMat);
  m_ShaderPrg->sendUniform3fv("color", 1.0f, 1.0f, 1.0f);
  
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glDisableVertexAttribArray(0);  
}

void Plane::deinit()
{
  
}
  
Plane::~Plane()
{
  
}