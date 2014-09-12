#include "dipole.h"

#include "scenemanager.h"

Dipole::Dipole(const std::string& _pDipoleName, const float& _pLen, const float& _pWidth, const float& _pHeight):
  VisUnit(_pDipoleName), m_DipoleObjName(_pDipoleName), m_Dims(_pLen, _pWidth, _pHeight)
{
}

void Dipole::init()
{
  SceneManager::getSingletonPtr()->createPlyObject(m_DipoleObjName, m_DipoleObjName, "../data/dipole.ply");
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_DipoleObjName)->setObjectDims(m_Dims);	// dipole
}

void Dipole::deinit()
{
  
}

void Dipole::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_DipoleObjName)->setPosition(_pX, _pY, _pZ);
}

void Dipole::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  SceneManager::getSingletonPtr()->getObjectPtrByName(m_DipoleObjName)->setOrientation(_pX * glm::pi<float>() / 180.0f, _pY * glm::pi<float>() / 180.0f, _pZ * glm::pi<float>() / 180.0f);
}

Dipole::~Dipole()
{
}