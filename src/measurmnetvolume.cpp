#include "measurmentvolume.h"

MeasurmentVolume::MeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs):
  VisUnit(_pMVName), m_Dims(_pLen, _pWidth, _pHeight), m_Segs(_pLSegs, _pWSegs, _pHSegs)
{
  
}

void MeasurmentVolume::init()
{
  
}

void MeasurmentVolume::render()
{
  
}

void MeasurmentVolume::deinit()
{
  
}

void MeasurmentVolume::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  
}

void MeasurmentVolume::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  
}