#include "box.h"

#include <iostream>

#include "../application/unitmanager.h"

Box::Box(const std::string& _pUnitName, const std::string& _pBoxName, const float& _pLength, const float& _pWidth, const float& _pHeight, const glm::vec3& _pColor):
  Vis3DObject(_pUnitName, _pBoxName), m_Length(_pLength), m_Width(_pWidth), m_Height(_pHeight), m_Color(_pColor)
{
  m_ShaderPrg = new ShaderProgram("../../src/glsl/simple.vert", "../../src/glsl/simple.frag");
}
  
void Box::init()
{  
  if(!b_Initialized)
  {
    m_ShaderPrg->init();
    m_ShaderPrg->bindAttribute(0, "a_Vertex");
    m_ShaderPrg->link();
    
    // Initialization the points to generate the bounding box
    m_Points.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));	// 0
    m_Points.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));	// 1
    m_Points.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));	// 2
    m_Points.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));	// 3
    m_Points.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));	// 4
    m_Points.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));	// 5
    m_Points.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));	// 6
    m_Points.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));	// 7
    
    m_Indices.push_back(0);	m_Indices.push_back(1);		m_Indices.push_back(2);
    m_Indices.push_back(0);	m_Indices.push_back(2);		m_Indices.push_back(3);
    
    m_Indices.push_back(0);	m_Indices.push_back(3);		m_Indices.push_back(4);
    m_Indices.push_back(4);	m_Indices.push_back(3);		m_Indices.push_back(7);
    
    m_Indices.push_back(4);	m_Indices.push_back(5);		m_Indices.push_back(0);
    m_Indices.push_back(0);	m_Indices.push_back(5);		m_Indices.push_back(1);
    
    m_Indices.push_back(2);	m_Indices.push_back(1);		m_Indices.push_back(6);
    m_Indices.push_back(6);	m_Indices.push_back(1);		m_Indices.push_back(5);
    
    m_Indices.push_back(3);	m_Indices.push_back(2);		m_Indices.push_back(7);
    m_Indices.push_back(7);	m_Indices.push_back(2);		m_Indices.push_back(6);
    
    m_Indices.push_back(5);	m_Indices.push_back(6);		m_Indices.push_back(4);
    m_Indices.push_back(4);	m_Indices.push_back(6);		m_Indices.push_back(7);  
    
    glGenBuffers(1, &m_BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, m_Points.size() * sizeof(glm::vec3), &m_Points[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_IndicesBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices[0], GL_STATIC_DRAW);
    
    b_Initialized = true;
  }
}

void Box::render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat)
{
  glm::mat4 modelMat = UnitManager::getSingletonPtr()->getUnitPtrByName(m_UnitName)->getParentModelMat() * glm::translate(glm::mat4(1.0f), m_Position) * glm::scale(glm::mat4(1.0f), glm::vec3(m_Length, m_Width, m_Height));
  
  glm::mat4 modelViewProjMat = _pProjMat * _pViewMat * modelMat;
  
  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("ModelViewProj_mat", modelViewProjMat);
  m_ShaderPrg->sendUniform3fv("color", m_Color);
  
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferID);
  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
  
  glDisableVertexAttribArray(0);
}

void Box::deinit()
{
}

glm::vec3 Box::getDims() const
{
  return glm::vec3(m_Length, m_Width, m_Height);
}

Box::~Box()
{
  
}