#include "staticunit.h"

#include "scenemanager.h"

StaticUnit::StaticUnit(const std::string& _pStaticUnitName, const std::string& _pUnitFilename, const float& _pLen, const float& _pWidth, const float& _pHeight):
  VisUnit(_pStaticUnitName), m_StaticUnitObjName(_pStaticUnitName), m_UnitFilename(_pUnitFilename), m_Dims(_pLen, _pWidth, _pHeight)
{
}

void StaticUnit::init()
{
  SceneManager::getSingletonPtr()->createPlyObject(m_StaticUnitObjName, m_StaticUnitObjName, m_UnitFilename);
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_StaticUnitObjName)->setObjectDims(m_Dims);	// antenna
}

void StaticUnit::deinit()
{
  
}

void StaticUnit::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_StaticUnitObjName)->setPosition(_pX, _pY, _pZ);
}

void StaticUnit::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_StaticUnitObjName)->setOrientation(_pX * glm::pi<float>() / 180.0f, _pY * glm::pi<float>() / 180.0f, _pZ * glm::pi<float>() / 180.0f);
}

StaticUnit::~StaticUnit()
{
}