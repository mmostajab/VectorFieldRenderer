#include "vis3dobject.h"

Vis3DObject::Vis3DObject(const std::string& _pUnitName, const std::string& _pObjName): m_UnitName(_pUnitName), m_Name(_pObjName), b_Initialized(false)
{
}
  
void Vis3DObject::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  m_Position = glm::vec3(_pX, _pY, _pZ);
}

void Vis3DObject::setOrientation(const float& _pX, const float& _pY, const float& _pZ)
{
  m_Orientation = glm::vec3(_pX, _pY, _pZ);
}

void Vis3DObject::setObjectDims(const float& _pX, const float& _pY, const float& _pZ)
{
  m_ObjDims = glm::vec3(_pX, _pY, _pZ);
}

void Vis3DObject::setObjectDims(const glm::vec3& _pDims)
{
  m_ObjDims = _pDims;
}

std::string Vis3DObject::getName() const
{
  return m_Name;
}
  
Vis3DObject::~Vis3DObject()
{
  
}