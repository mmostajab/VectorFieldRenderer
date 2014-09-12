#include "ground.h"

#include <iostream>
#include "scenemanager.h"

Ground::Ground(const std::string& _pGroundName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWidth):
  VisUnit(_pGroundName), m_GroundObjName(_pGroundName), m_Point(_pPoint), m_XDir(_pXDir), m_YDir(_pYDir), m_Length(_pLen), m_Width(_pWidth)
{
}

void Ground::init()
{
  SceneManager::getSingletonPtr()->createPlane(m_GroundObjName, m_GroundObjName, m_Point, m_XDir, m_YDir, m_Length, m_Width);
}

void Ground::deinit()
{
  
}

void Ground::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  std::cout << "Will not affect the position\n";
}

void Ground::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  std::cout << "Will not affect the orientation\n";
}

Ground::~Ground()
{
}