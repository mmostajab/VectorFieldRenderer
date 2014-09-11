#include "unitmanager.h"

#include "measurmentvolume.h"

UnitManager* UnitManager::m_SingletonPtr = 0;
UnitManagerDestructor UnitManager::m_SingletonDestructor;

UnitManager::UnitManager()
{
  
}
  
UnitManager* UnitManager::getSingletonPtr()
{
  if(m_SingletonPtr == 0)
  {
    m_SingletonPtr = new UnitManager;
    m_SingletonDestructor.setSingletonPointer(m_SingletonPtr);
  }
  
  return m_SingletonPtr;
}

void UnitManager::createMeasurmentVolume(const std::string& _pBoxName, const float& _pLength, const float& _pWidth, const float& _pHeight)
{
  VisUnit* unitptr = new MeasurmentVolume(_pBoxName + "_Unit");  
  m_UnitPtrs.push_back(unitptr);  
}

Vis3DObject* UnitManager::getUnitPtrByName(const std::string& _pObjName)
{
  for(size_t i = 0; i < m_UnitPtrs.size(); i++)
  {
    if(m_UnitPtrs[i]->getName() == _pObjName)
      return m_UnitPtrs[i];
  }
  
  return 0;
}

UnitManager::~UnitManager()
{
  
}