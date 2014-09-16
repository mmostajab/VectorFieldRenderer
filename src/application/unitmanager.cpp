#include "unitmanager.h"

#include "ground.h"
#include "measurmentvolume.h"
#include "dipole.h"
#include "antenna.h"
#include "staticunit.h"

UnitManager* UnitManager::m_SingletonPtr = 0;
UnitManagerDestructor UnitManager::m_SingletonDestructor;

UnitManager::UnitManager()
{
  VisUnit* nothingUnit = new VisUnit("NOTHING");
  m_UnitPtrs.push_back(nothingUnit);
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

void UnitManager::createGround(const std::string& _pGroundName, const glm::vec3& _pPoint, const float& _pLen, const float& _pWidth)
{
  Ground* groundPtr = new Ground(_pGroundName, _pPoint, glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), _pLen, _pWidth);
  m_UnitPtrs.push_back(groundPtr);
}

void UnitManager::createGate(const std::string& _pGateName, const float& _pLen, const float& _pWidth, const float& _pHeight, const float& _pX, const float& _pY, const float& _pZ)
{
  StaticUnit* gatePtr = new StaticUnit(_pGateName, "../../data/gateN.ply", _pLen, _pWidth, _pHeight);
  m_UnitPtrs.push_back(gatePtr);
}

void UnitManager::createAntenna(const std::string& _pAntennaName, const float& _pLen, const float& _pWidth, const float& _pHeight)
{
  Antenna* antennaPtr = new Antenna(_pAntennaName, _pLen, _pWidth, _pHeight);
  m_UnitPtrs.push_back(antennaPtr);
}

void UnitManager::createDipole(const std::string& _pDipoleName, const float& _pLen, const float& _pWidth, const float& _pHeight)
{
  Dipole* dipolePtr = new Dipole(_pDipoleName, _pLen, _pWidth, _pHeight);  
  m_UnitPtrs.push_back(dipolePtr);
}

void UnitManager::createMeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs)
{
  MeasurmentVolume* unitptr = new MeasurmentVolume(_pMVName, _pLen, _pWidth, _pHeight, _pLSegs, _pWSegs, _pHSegs);  
  m_UnitPtrs.push_back(unitptr);
}

VisUnit* UnitManager::getUnitPtrByName(const std::string& _pObjName)
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