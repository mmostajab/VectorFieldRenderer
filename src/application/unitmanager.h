#ifndef __VIS_TOOL_TOOL_MANAGER_H__
#define __VIS_TOOL_TOOL_MANAGER_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>

#include "visunit.h"

// The main parts of the engine which uses the scene manager
class VisApplication;

// Singleton Destructor
class UnitManagerDestructor;

class UnitManager
{
  friend class VisApplication;
  friend class UnitManagerDestructor;
private:
  std::vector<VisUnit*> m_UnitPtrs;
  
  static UnitManager* m_SingletonPtr;
  static UnitManagerDestructor m_SingletonDestructor;
  
private:
  UnitManager();
  ~UnitManager();
  
public:
  
  static UnitManager* getSingletonPtr();
  
  void createGround(const std::string& _pGroundName, const glm::vec3& _pPoint, const float& _pLen, const float& _pWidth);
  void createGate(const std::string& _pGateName, const float& _pLen, const float& _pWidth, const float& _pHeight, const float& _pX, const float& _pY, const float& _pZ);
  void createAntenna(const std::string& _pAntennaName, const float& _pLen, const float& _pWidth, const float& _pHeight);
  void createDipole(const std::string& _pDipoleName, const float& _pLen, const float& _pWidth, const float& _pHeight);
  void createMeasurmentVolume(const std::string& _pMVName, const float& _pLen, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs);
  
  VisUnit* getUnitPtrByName(const std::string& _pObjName);
};

class UnitManagerDestructor
{
private:
  UnitManager* m_SingletonPtr;

public:
  UnitManagerDestructor()
  {
  }

  void setSingletonPointer(UnitManager* _pSingletonPtr)
  {
    m_SingletonPtr = _pSingletonPtr;
  }

  ~UnitManagerDestructor()
  {
    delete m_SingletonPtr;
  }
};

#endif