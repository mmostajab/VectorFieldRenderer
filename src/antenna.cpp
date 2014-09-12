#include "antenna.h"

#include "scenemanager.h"

Antenna::Antenna(const std::string& _pAntennaName, const float& _pLen, const float& _pWidth, const float& _pHeight):
  VisUnit(_pAntennaName), m_AntennaObjName(_pAntennaName), m_Dims(_pLen, _pWidth, _pHeight)
{
}

void Antenna::init()
{
  SceneManager::getSingletonPtr()->createPlyObject(m_AntennaObjName, m_AntennaObjName, "../data/antenna.ply");
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_AntennaObjName)->setObjectDims(m_Dims);	// antenna
}

void Antenna::deinit()
{
  
}

void Antenna::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  m_ParentModelMat = glm::translate(glm::mat4(1.0f), glm::vec3(_pX, _pY, _pZ));
}

void Antenna::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  // SceneManager::getSingletonPtr()->getObjectPtrByName(m_AntennaObjName)->setOrientation(_pX * glm::pi<float>() / 180.0f, _pY * glm::pi<float>() / 180.0f, _pZ * glm::pi<float>() / 180.0f);
}

Antenna::~Antenna()
{
}