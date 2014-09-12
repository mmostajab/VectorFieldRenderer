#include "visunit.h"

VisUnit::VisUnit(const std::string& _pObjName): m_Name(_pObjName), m_SetupModelMat(1.0f), m_ParentModelMat(1.0f)
{ 
}

std::string VisUnit::getName() const
{
  return m_Name;
}
  
VisUnit::~VisUnit()
{ 
}