#include "measurmentvolume.h"

#include "scenemanager.h"

MeasurmentVolume::MeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs):
  VisUnit(_pMVName), m_Dims(_pLen, _pWidth, _pHeight), m_Segs(_pLSegs, _pWSegs, _pHSegs)
{
}

void MeasurmentVolume::init()
{
  
  SceneManager::getSingletonPtr()->createBoundingBox(m_Name, m_Name + "_BBOX", m_Dims, m_Segs, true);
  
  // for
 // SceneManager::getSingletonPtr()->createBox();
}

void MeasurmentVolume::deinit()
{
  
}

void MeasurmentVolume::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
//  SceneManager::getSingletonPtr()->getObjectPtrByName(m_Name + "_BBOX")->setPosition()
  m_ParentModelMat = glm::translate(glm::mat4(1.0f), glm::vec3(_pX, _pY, _pZ));
}

void MeasurmentVolume::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  
}

MeasurmentVolume::~MeasurmentVolume()
{
}