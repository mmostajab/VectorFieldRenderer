#ifndef __VIS_TOOL_VIS_UNIT_H__
#define __VIS_TOOL_VIS_UNIT_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

class VisUnit
{
protected:
  std::string m_Name;
  
  glm::vec3 m_Position;
  glm::vec3 m_Orientation;
  glm::vec3 m_Dims;
  
  glm::mat4 m_SetupModelMat;			// The matrix which will set the model in right direction and position
  glm::mat4 m_ParentModelMat;			// The matrix which will update the object based on the parent unit model
  
public:
  VisUnit(const std::string& _pObjName);
  
  virtual void init() = 0;
  virtual void deinit() = 0;
  
  virtual void setPosition(const float& _pX, const float& _pY, const float& _pZ) = 0;
  virtual void setOrientation(const float& _pX, const float& _pY, const float& _pZ) = 0;
  
  std::string getName() const;
  
  virtual ~VisUnit(); 
};

#endif // __VIS_TOOL_VIS_UNIT_H__