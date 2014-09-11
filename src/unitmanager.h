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
class Application;

// Singleton Destructor
class UnitManagerDestructor;

class UnitManager
{
  friend class Application;
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
  
  void createMeasurmentVolume(const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight);
  
  Vis3DObject* getUnitPtrByName(const std::string& _pObjName);
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