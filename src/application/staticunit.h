#ifndef __VIS_TOOL_STATIC_UNIT_H__
#define __VIS_TOOL_STATIC_UNIT_H__

#include "visunit.h"

#include <vector>
#include <string>

class StaticUnit: public VisUnit
{
private:
  std::string m_StaticUnitObjName;
  std::string m_UnitFilename;
  glm::vec3 m_Dims;		// Dimensions of the measurment volume
  
public:
  StaticUnit(const std::string& _pStaticUnitName, const std::string& _pUnitFilename, const float& _pLen, const float& _pWidth, const float& _pHeight);
  
  virtual void init();
  virtual void deinit();
  
  virtual void setPosition(const float& _pX, const float& _pY, const float& _pZ);
  virtual void setOrientation(const float& _pX, const float& _pY, const float& _pZ);
  
  ~StaticUnit();
};

#endif