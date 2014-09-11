#ifndef __VIS_TOOL_SCENE_MANAGER_H__
#define __VIS_TOOL_SCENE_MANAGER_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>

#include "scenenode.h"

// The main parts of the engine which uses the scene manager
class Renderer;

// Singleton Destructor
class SceneManagerDestructor;

class SceneManager
{
  friend class Renderer;
  friend class SceneManagerDestructor;
private:
  std::vector<SceneNode*> m_Nodes;
  
  static SceneManager* m_SingletonPtr;
  static SceneManagerDestructor m_SingletonDestructor;
  
private:
  SceneManager();
  ~SceneManager();
  
public:
  
  static SceneManager* getSingletonPtr();
  
  void createBox(const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight);
  void createPlane(const std::string& _pPlaneName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWid);
  void createPlyObject(const std::string& _pPlyObjNAme, const std::string& _pPlyFilename);  
  
  Vis3DObject* getObjectPtrByName(const std::string& _pObjName);
};

class SceneManagerDestructor
{
private:
  SceneManager* m_SingletonPtr;

public:
  SceneManagerDestructor()
  {
  }

  void setSingletonPointer(SceneManager* _pSingletonPtr)
  {
    m_SingletonPtr = _pSingletonPtr;
  }

  ~SceneManagerDestructor()
  {
    delete m_SingletonPtr;
  }
};

#endif