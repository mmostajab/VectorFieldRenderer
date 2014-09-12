#include "plyobject.h"

#include <iostream>

PlyObject::PlyObject(const std::string& _pUnitName, const std::string& _pObjName, const std::string&  _pFilename, const long int& _pUserDataLength, void* _pUserDataPtr): 
  Vis3DObject(_pUnitName, _pObjName), m_UserDataLength(_pUserDataLength), m_UserDataPtr(_pUserDataPtr),
  m_nVertices(0), m_nFaces(0), m_nIndices(0), m_BBox(_pUnitName, _pObjName + "_BBOX")
{
  m_Filename = _pFilename;
  m_ShaderPrg = new ShaderProgram("../src/glsl/plyobject.vert", "../src/glsl/plyobject.frag");
}

void PlyObject::init()
{
  m_ShaderPrg->init();
  m_ShaderPrg->bindAttribute(0, "a_Vertex");
  m_ShaderPrg->bindAttribute(1, "a_Normal");
  m_ShaderPrg->link();
  
  // load the data into the variables
  PlyDataReader::getSingletonPtr()->readDataInfo(m_Filename.c_str(), m_UserDataPtr, m_UserDataLength);
  
  m_nVertices = PlyDataReader::getSingletonPtr()->getNumVertices();
  m_VertexData.resize(m_nVertices);
  
  m_nFaces = PlyDataReader::getSingletonPtr()->getNumFaces();
  m_nIndices = 3 * m_nFaces;
  m_IndexData.resize(m_nIndices);

  PlyDataReader::getSingletonPtr()->readData(&m_VertexData[0], &m_IndexData[0]);
  
  PlyDataReader::getSingletonPtr()->releaseDataHandles();
  
  // create the required buffers
  glGenBuffers(1, &m_VertexBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, m_VertexData.size() * sizeof(PlyObjVertex), &m_VertexData[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &m_IndexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexData.size() * sizeof(unsigned int), &m_IndexData[0], GL_STATIC_DRAW);
  
  for(size_t i = 0; i < m_VertexData.size(); i++)
  {
    m_CenterPos += m_VertexData[i].pos;
    m_BBox.addPoint(m_VertexData[i].pos);
  }
  
  m_CenterPos /= m_VertexData.size();
  
  m_BBox.init();
}

void PlyObject::render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat)
{
  glDisable(GL_CULL_FACE);
  
  glm::mat4 modelViewProjMat;
  if(glm::length(m_ObjDims) < 0.0001f)
    modelViewProjMat = _pProjMat * _pViewMat * glm::translate(glm::mat4(1.0f), -m_CenterPos);
  else
    // First, move to the center to (0,0,0)
    // Second, put the object in a cube of 1
    // Third, resize it to the dimensions that we want
    // Forth, 
    // Fifth, 
    // Sixth, put it in the view coordinate
    // Seventh, put it in projection space
    modelViewProjMat = _pProjMat * _pViewMat * glm::translate(glm::mat4(1.0f), m_Position) * 
    glm::rotate(glm::mat4(1.0f), m_Orientation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), m_Orientation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), m_Orientation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
    glm::scale(glm::mat4(1.0f), m_ObjDims) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / m_BBox.getDims())) * glm::translate(glm::mat4(1.0f), -m_CenterPos) ;
  
  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("ModelViewProj_mat", modelViewProjMat);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  
  int stride = sizeof(PlyObjVertex);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, stride, 0);
  glVertexAttribPointer((GLint)1, 3, GL_FLOAT, GL_FALSE, stride, (char*)0 + 12);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
  
  //std::cout << "Try to draw...\n";
  glDrawElements(GL_TRIANGLES, m_IndexData.size(), GL_UNSIGNED_INT, 0);
 // std::cout << "Drawing done...\n";
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  
  // Render the bounding box related to
  m_BBox.render(modelViewProjMat);
  
  //std::cout << "Rendering done...\n";
}

void PlyObject::deinit()
{
  
}

PlyObject::~PlyObject(void)
{
	
}