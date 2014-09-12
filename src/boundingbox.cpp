#include "boundingbox.h"

#include <iostream>

BoundingBox::BoundingBox(const std::string& _pUnitName, const std::string& _pBBName, const glm::vec3& _pCorner1, const glm::vec3& _pCorner2): Vis3DObject(_pUnitName, _pBBName), m_Segs(1, 1, 1)
{
  //m_MinCorner = glm::vec3(glm::min(_pCorner1.x, _pCorner2.x), glm::min(_pCorner1.y, _pCorner2.y), glm::min(_pCorner1.z, _pCorner2.z));
  //m_MaxCorner = glm::vec3(glm::max(_pCorner1.x, _pCorner2.x), glm::max(_pCorner1.y, _pCorner2.y), glm::max(_pCorner1.z, _pCorner2.z));
  
 m_MinCorner = _pCorner2;
 m_MaxCorner = _pCorner1;
  
 m_Position = ((m_MinCorner + m_MaxCorner) / 2.0f);
 m_ShaderPrg = new ShaderProgram("../src/glsl/boundingbox.vert", "../src/glsl/boundingbox.frag");
}

BoundingBox::BoundingBox(const std::string& _pUnitName, const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs):
  Vis3DObject(_pUnitName, _pBBName), m_MinCorner(-_pLength / 2.0f, -_pWidth / 2.0f, -_pHeight / 2.0f), m_Segs(_pLSegs, _pWSegs, _pHSegs),
  b_DetailedMode(false)
{
  m_ShaderPrg = new ShaderProgram("../src/glsl/boundingbox.vert", "../src/glsl/boundingbox.frag");
}
  
void BoundingBox::init()
{
  //std::cout << "BB = " << m_MinCorner.x << ", " << m_MinCorner.y << ", " << m_MinCorner.z << "\t" << m_MaxCorner.x << ", " << m_MaxCorner.y << ", " << m_MaxCorner.z << "\n";
  
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
  
  m_Indices.push_back(0);	m_Indices.push_back(1);
  m_Indices.push_back(1);	m_Indices.push_back(2);
  m_Indices.push_back(2);	m_Indices.push_back(3);
  m_Indices.push_back(3);	m_Indices.push_back(0);
  
  m_Indices.push_back(4);	m_Indices.push_back(5);
  m_Indices.push_back(5);	m_Indices.push_back(6);
  m_Indices.push_back(6);	m_Indices.push_back(7);
  m_Indices.push_back(7);	m_Indices.push_back(4);
  
  m_Indices.push_back(0);	m_Indices.push_back(4);
  m_Indices.push_back(1);	m_Indices.push_back(5);
  m_Indices.push_back(2);	m_Indices.push_back(6);
  m_Indices.push_back(3);	m_Indices.push_back(7);
  
  glGenBuffers(1, &m_BufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  glBufferData(GL_ARRAY_BUFFER, m_Points.size() * sizeof(glm::vec3), &m_Points[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &m_IndicesBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(int), &m_Indices[0], GL_STATIC_DRAW);
  
  for(int i = 0; i < m_Segs.x + 1; i++)
  {
    for(int j = 0; j < m_Segs.y + 1; j++)
    {
      for(int k = 0; k < m_Segs.z + 1; k++)
      {
	m_DetailedPoints.push_back(glm::vec3(i / static_cast<float>(m_Segs.x) - 0.5f, j / static_cast<float>(m_Segs.y) - 0.5f, k / static_cast<float>(m_Segs.z) - 0.5f));
      }
    }
  }
  
  for(int i = 0; i < m_Segs.x + 1; i++)
  {
    for(int j = 0; j < m_Segs.y + 1; j++)
    {
      for(int k = 0; k < m_Segs.z + 1; k++)
      {
	if(i - 1 >= 0)
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back((i-1) * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	}
	
	if(i + 1 < (m_Segs.x + 1))
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back((i+1) * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	}
	
	if(j - 1 >= 0)
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + (j-1) * (m_Segs.z + 1) + k);
	}
	
	if(j + 1 < (m_Segs.y + 1))
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + (j+1) * (m_Segs.z + 1) + k);
	}
	
	if(k - 1 >= 0)
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k - 1);
	}
	
	if(k + 1 < (m_Segs.z + 1))
	{
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k);
	  m_DetailedIndices.push_back(i * (m_Segs.y + 1) * (m_Segs.z + 1) + j * (m_Segs.z + 1) + k + 1);
	}
      }
    }
  }
  
  glGenBuffers(1, &m_DetailedBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_DetailedBufferID);
  glBufferData(GL_ARRAY_BUFFER, m_DetailedPoints.size() * sizeof(glm::vec3), &m_DetailedPoints[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &m_DetailedIndicesBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DetailedIndicesBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_DetailedIndices.size() * sizeof(int), &m_DetailedIndices[0], GL_STATIC_DRAW);
}

void BoundingBox::render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat)
{
  glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::scale(glm::mat4(1.0f), m_MaxCorner - m_MinCorner);
  
  glm::mat4 modelViewProjMat = _pProjMat * _pViewMat * modelMat;
  
  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("ModelViewProj_mat", modelViewProjMat);

  glEnableVertexAttribArray(0);
  
  if(!b_DetailedMode)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  }
  else
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_DetailedBufferID);
  }
  
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  if(!b_DetailedMode)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferID);
    glDrawElements(GL_LINES, m_Indices.size(), GL_UNSIGNED_INT, 0);
  }
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DetailedIndicesBufferID);
    glDrawElements(GL_LINES, m_DetailedIndices.size(), GL_UNSIGNED_INT, 0);
  }
  
  glDisableVertexAttribArray(0);
}

void BoundingBox::render(const glm::mat4& _pModelViewProjMat)
{
  glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::scale(glm::mat4(1.0f), m_MaxCorner - m_MinCorner);
  
  glm::mat4 modelViewProjMat = _pModelViewProjMat * modelMat;
  
  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("ModelViewProj_mat", modelViewProjMat);
  
  glEnableVertexAttribArray(0);
  
  if(!b_DetailedMode)
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
  }
  else
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_DetailedBufferID);
  }
  
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  if(!b_DetailedMode)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBufferID);
    glDrawElements(GL_LINES, m_Indices.size(), GL_UNSIGNED_INT, 0);
  }
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_DetailedIndicesBufferID);
    glDrawElements(GL_LINES, m_DetailedIndices.size(), GL_UNSIGNED_INT, 0);
  }
  
  glDisableVertexAttribArray(0);
}

void BoundingBox::deinit()
{
}

void BoundingBox::addPoint(const glm::vec3& _pPoint)
{
  m_MinCorner = glm::vec3(glm::min(m_MinCorner.x, _pPoint.x), glm::min(m_MinCorner.y, _pPoint.y), glm::min(m_MinCorner.z, _pPoint.z));
  m_MaxCorner = glm::vec3(glm::max(m_MaxCorner.x, _pPoint.x), glm::max(m_MaxCorner.y, _pPoint.y), glm::max(m_MaxCorner.z, _pPoint.z));
  
  m_Position = (m_MinCorner + m_MaxCorner) / 2.0f;
}

void BoundingBox::setCorners(const glm::vec3& _pCorner1, const glm::vec3& _pCorner2)
{
  m_MinCorner = glm::vec3(glm::min(_pCorner1.x, _pCorner2.x), glm::min(_pCorner1.y, _pCorner2.y), glm::min(_pCorner1.z, _pCorner2.z));
  m_MaxCorner = glm::vec3(glm::max(_pCorner1.x, _pCorner2.x), glm::max(_pCorner1.y, _pCorner2.y), glm::max(_pCorner1.z, _pCorner2.z));

  m_Position = (m_MinCorner + m_MaxCorner) / 2.0f;
}

glm::vec3 BoundingBox::getDims() const
{
  return glm::vec3(m_MaxCorner - m_MinCorner);
}

void BoundingBox::setOutlineMode()
{
  b_DetailedMode = false;
}

void BoundingBox::setDetailedMode()
{
  b_DetailedMode = true;
}

BoundingBox::~BoundingBox()
{
  
}