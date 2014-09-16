#ifndef __VIS_TOOL_ANTENNA_H__
#define __VIS_TOOL_ANTENNA_H__

#include "visunit.h"

#include <vector>
#include <string>

class Antenna: public VisUnit
{
private:
  std::string m_AntennaObjName;
  glm::vec3 m_Dims;		// Dimensions of the measurment volume
  
public:
  Antenna(const std::string& _pAntennaName, const float& _pLen, const float& _pWidth, const float& _pHeight);
  
  virtual void init();
  virtual void deinit();
  
  virtual void setPosition(const float& _pX, const float& _pY, const float& _pZ);
  virtual void setOrientation(const float& _pX, const float& _pY, const float& _pZ);
  
  ~Antenna();
};

#endif