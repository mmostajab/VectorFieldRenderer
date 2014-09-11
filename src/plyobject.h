#pragma once

#include <GL/glew.h>

#include "vis3dobject.h"
#include "plydatareader.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shaderprogram.h"

#include "boundingbox.h"

struct PlyObjVertex
{
  glm::vec3 pos;
  glm::vec3 normal;
};

class PlyObject: public Vis3DObject
{
protected:
  long m_UserDataLength;
  void* m_UserDataPtr;

  int m_nVertices;
  int m_nFaces;
  int m_nIndices;
  
  glm::vec3 m_CenterPos;
  std::vector<PlyObjVertex> m_VertexData;
  std::vector<int> m_IndexData;
  
  GLuint m_VertexBufferID, m_IndexBufferID;
  
  ShaderProgram* m_ShaderPrg;
  std::string m_Filename;
  
  BoundingBox m_BBox;

public:
  PlyObject(const std::string& _pObjName, const std::string& _pFileName, const long int& _pUserDataLength = -1, void* _pUserDataPtr = 0);

  void init();
  void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat);
  void deinit();

  ~PlyObject(void);

private:
  
  int getTypeLength(e_ply_type _pType);
};