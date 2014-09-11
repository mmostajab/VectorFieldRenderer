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
class ToolManagerDestructor;

class ToolManager
{
  friend class Application;
  friend class ToolManagerDestructor;
private:
  std::vector<VisUnit*> m_UnitPtrs;
  
  static ToolManager* m_SingletonPtr;
  static ToolManagerDestructor m_SingletonDestructor;
  
private:
  ToolManager();
  ~ToolManager();
  
public:
  
  static ToolManager* getSingletonPtr();
  
  void createMeasurmentVolume(const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight);
  
  Vis3DObject* getUnitPtrByName(const std::string& _pObjName);
};

class ToolManagerDestructor
{
private:
  ToolManager* m_SingletonPtr;

public:
  ToolManagerDestructor()
  {
  }

  void setSingletonPointer(ToolManager* _pSingletonPtr)
  {
    m_SingletonPtr = _pSingletonPtr;
  }

  ~ToolManagerDestructor()
  {
    delete m_SingletonPtr;
  }
};

#endif