#ifndef __VIS_TOOL_MEASURMENT_VOLUME_H__
#define __VIS_TOOL_MEASURMENT_VOLUME_H__

#include "visunit.h"

#include "../rendering/boundingbox.h"
#include "../rendering/box.h"

#include <vector>
#include <string>

class MeasurmentVolume: public VisUnit
{
private:
  glm::vec3 m_Dims;		// Dimensions of the measurment volume
  glm::vec3 m_Segs;		// Segmentation of the volume in each direction
  
  std::vector<std::string> m_AttachedObjNames;
  
public:
  MeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs);
  
  virtual void init();
  virtual void deinit();
  
  virtual void setPosition(const float& _pX, const float& _pY, const float& _pZ);
  virtual void setOrientation(const float& _pX, const float& _pY, const float& _pZ);
  
  ~MeasurmentVolume();
};

#endif