#ifndef __VIS_TOOL_GROUND_H__
#define __VIS_TOOL_GROUND_H__

#include "visunit.h"

#include <vector>
#include <string>

class Ground: public VisUnit
{
private:
  std::string m_GroundObjName;
  glm::vec3 m_Point;
  glm::vec3 m_XDir, m_YDir;
  float m_Length, m_Width;
  
public:
  Ground(const std::string& _pGroundUnitName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWidth);
  
  virtual void init();
  virtual void deinit();
  
  virtual void setPosition(const float& _pX, const float& _pY, const float& _pZ);
  virtual void setOrientation(const float& _pX, const float& _pY, const float& _pZ);
  
  ~Ground();
};

#endif