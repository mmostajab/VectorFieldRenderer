#ifndef __VIS_TOOL_PLANE_H__
#define __VIS_TOOL_PLANE_H__

#include <GL/glew.h>

#include "vis3dobject.h"
#include "shaderprogram.h"

#include <vector>
#include <string>

class Plane: public Vis3DObject
{
private:
  glm::vec3 m_Point;
  glm::vec3 m_XDir, m_YDir;
  float m_Len, m_Width;

  GLuint m_BufferID;
  std::vector<glm::vec3> m_Points;
  
  ShaderProgram* m_ShaderPrg;
  
public:
  Plane(const std::string& _pObjName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWidth);
  
  void init();
  void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat);
  void deinit();
  
  ~Plane();
};

#endif 