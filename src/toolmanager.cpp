#include "toolmanager.h"

#include "measurmentvolume.h"

ToolManager* ToolManager::m_SingletonPtr = 0;
ToolManagerDestructor ToolManager::m_SingletonDestructor;

ToolManager::ToolManager()
{
  
}
  
ToolManager* ToolManager::getSingletonPtr()
{
  if(m_SingletonPtr == 0)
  {
    m_SingletonPtr = new ToolManager;
    m_SingletonDestructor.setSingletonPointer(m_SingletonPtr);
  }
  
  return m_SingletonPtr;
}

void ToolManager::createMeasurmentVolume(const std::string& _pBoxName, const float& _pLength, const float& _pWidth, const float& _pHeight)
{
  VisUnit* unitptr = new MeasurmentVolume(_pBoxName + "_Unit");  
  m_UnitPtrs.push_back(unitptr);  
}

Vis3DObject* ToolManager::getUnitPtrByName(const std::string& _pObjName)
{
  for(size_t i = 0; i < m_UnitPtrs.size(); i++)
  {
    if(m_UnitPtrs[i]->getName() == _pObjName)
      return m_UnitPtrs[i];
  }
  
  return 0;
}

ToolManager::~ToolManager()
{
  
}