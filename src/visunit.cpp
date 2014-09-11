#include "visunit.h"

VisUnit::VisUnit(const std::string& _pObjName): m_Name(_pObjName)
{ 
}

std::string VisUnit::getName() const
{
  return m_Name;
}
  
VisUnit::~VisUnit()
{ 
}