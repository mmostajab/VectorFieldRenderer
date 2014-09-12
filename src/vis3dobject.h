#ifndef __VIS_TOOL_3D_OBJECT_H__
#define __VIS_TOOL_3D_OBJECT_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

class Vis3DObject
{
protected:
  std::string m_UnitName;
  std::string m_Name;
  
  glm::vec3 m_Position;
  glm::vec3 m_Orientation;
  glm::vec3 m_ObjDims;
  
  bool b_Initialized;
  
public:
  Vis3DObject(const std::string& _pUnitName, const std::string& _pObjName);
  
  virtual void init() = 0;
  virtual void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat) = 0;
  virtual void deinit() = 0;
  
  void setPosition(const float& _pX, const float& _pY, const float& _pZ);
  void setOrientation(const float& _pX, const float& _pY, const float& _pZ);
  void setObjectDims(const float& _pX, const float& _pY, const float& _pZ);
  void setObjectDims(const glm::vec3& _pDims);
  
  std::string getName() const;
  
  virtual ~Vis3DObject(); 
};

#endif // __VIS_TOOL_3D_OBJECT_H__