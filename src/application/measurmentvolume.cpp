#include "measurmentvolume.h"

#include "../rendering/scenemanager.h"

#include <iostream>
#include <stdio.h>

MeasurmentVolume::MeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs):
  VisUnit(_pMVName), m_Dims(_pLen, _pWidth, _pHeight), m_Segs(_pLSegs, _pWSegs, _pHSegs)
{
}

void MeasurmentVolume::init()
{
  
  SceneManager::getSingletonPtr()->createBoundingBox(m_Name, m_Name + "_BBOX", m_Dims, m_Segs, true);
  
  char strBoxNum[4];
  glm::vec3 elementDim = m_Dims / (m_Segs * glm::vec3(8.0f, 8.0f, 8.0f));
  Vis3DObject* boxPtr = 0;
  
  for(int i = 0; i < m_Segs.x; i++)
  {
    for(int j = 0; j < m_Segs.y; j++)
    {
      for(int k = 0; k < m_Segs.z; k++)
      {
	sprintf (strBoxNum , "%d", static_cast<int>(i * (m_Segs.y * m_Segs.z) + j * m_Segs.z + k)) ;      
	glm::vec3 origin = glm::vec3(i, j, k) * (m_Dims / (m_Segs)) - (m_Dims / glm::vec3(2.0f, 2.0f, 2.0f)) + (m_Dims / (m_Segs * glm::vec3(2.0f, 2.0f, 2.0f)));
	std::cout << origin.x << " " << origin.y << " " << origin.z << std::endl;
	boxPtr = SceneManager::getSingletonPtr()->createBox(m_Name, m_Name + "_BOX" + strBoxNum, elementDim.x, elementDim.y, elementDim.z);
	//boxPtr = SceneManager::getSingletonPtr()->createBox(m_Name, m_Name + "_BOX" + strBoxNum, 10, 10, 10);
	boxPtr->setPosition(origin.x, origin.y, origin.z);
	//boxPtr->setOrientation(0, glm::pi<float>() / 2.0f, 0);
      }
    }
  }
  
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