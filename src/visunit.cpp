#include "visunit.h"

VisUnit::VisUnit(const std::string& _pObjName): m_Name(_pObjName), m_SetupModelMat(1.0f), m_ParentModelMat(1.0f)
{ 
}

void VisUnit::init()
{
  
}

void VisUnit::deinit()
{
  
}

void VisUnit::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  
}

void VisUnit::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  
}

std::string VisUnit::getName() const
{
  return m_Name;
}

void VisUnit::setSetupModelMat(const glm::mat4& _pSetupModelMat)
{
  m_SetupModelMat = _pSetupModelMat;
}

glm::mat4 VisUnit::getSetupModelMat()
{
  return m_SetupModelMat;
}

glm::mat4 VisUnit::getParentModelMat()
{
  return m_ParentModelMat;
}

VisUnit::~VisUnit()
{ 
}