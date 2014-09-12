#ifndef __VIS_TOOL_BOX_H__
#define __VIS_TOOL_BOX_H__

#include "vis3dobject.h"
#include "shaderprogram.h"

#include <vector>

#include <float.h>

class Box: public Vis3DObject
{
private:
  float m_Length, m_Width, m_Height;
  glm::vec3 m_Color;
  
  GLuint m_BufferID;
  GLuint m_IndicesBufferID;
  std::vector<glm::vec3> m_Points;
  std::vector<int> m_Indices;
  
  ShaderProgram* m_ShaderPrg;
  
public:
  Box(const std::string& _pUnitName, const std::string& _pBoxName, const float& _pLength, const float& _pWidth, const float& _pHeight, const glm::vec3& _pColor = glm::vec3(0, 1, 0));
  
  void init();
  void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat);
  void deinit();
  
  glm::vec3 getDims() const;
  
  ~Box();
};

#endif