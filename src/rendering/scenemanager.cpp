#include "scenemanager.h"
#include "../application/unitmanager.h"
//#include "staticunit.h"

#include "boundingbox.h"
#include "box.h"
#include "plane.h"
#include "plyobject.h"

SceneManager* SceneManager::m_SingletonPtr = 0;
SceneManagerDestructor SceneManager::m_SingletonDestructor;

SceneManager::SceneManager()
{
  
}
  
SceneManager* SceneManager::getSingletonPtr()
{
  if(m_SingletonPtr == 0)
  {
    m_SingletonPtr = new SceneManager;
    m_SingletonDestructor.setSingletonPointer(m_SingletonPtr);
  }
  
  return m_SingletonPtr;
}

Vis3DObject* SceneManager::createBoundingBox(const std::string& _pUnitName, const std::string& _pBBName, const glm::vec3& _pDims, const glm::vec3& _pSegs, const bool& _pDetailed)
{
  return createBoundingBox(_pUnitName, _pBBName, _pDims.x, _pDims.y, _pDims.z, _pSegs.x, _pSegs.y, _pSegs.z, _pDetailed);
}

Vis3DObject* SceneManager::createBoundingBox(const std::string& _pUnitName, const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight, const int& _pLSegs, const int& _pWSegs, const int& _pHSegs, const bool& _pDetailed)
{
  SceneNode* scenenode = new SceneNode(_pBBName + "_Node");
  BoundingBox* boundingboxobj = new BoundingBox(_pUnitName, _pBBName, _pLength, _pWidth, _pHeight, _pLSegs, _pWSegs, _pHSegs);
  
  if(_pDetailed)
    boundingboxobj->setDetailedMode();
  else
    boundingboxobj->setOutlineMode();
  
  scenenode->addObject(boundingboxobj);
  
  m_Nodes.push_back(scenenode);  
  
  return boundingboxobj;
}

Vis3DObject* SceneManager::createBox(const std::string& _pUnitName, const std::string& _pBoxName, const float& _pLength, const float& _pWidth, const float& _pHeight)
{
  SceneNode* scenenode = new SceneNode(_pBoxName + "_Node");
  Box* boxobj = new Box(_pUnitName, _pBoxName, _pLength, _pWidth, _pHeight);
  scenenode->addObject(boxobj);
  
  m_Nodes.push_back(scenenode);  
  
  return boxobj;
}

Vis3DObject* SceneManager::createPlane(const std::string& _pUnitName, const std::string& _pPlaneName, const glm::vec3& _pPoint, const glm::vec3& _pXDir, const glm::vec3& _pYDir, const float& _pLen, const float& _pWidth)
{
  SceneNode* scenenode = new SceneNode(_pPlaneName + "_Node");
  Plane* planeobj = new Plane(_pUnitName, _pPlaneName, _pPoint, _pXDir, _pYDir, _pLen, _pWidth);
  scenenode->addObject(planeobj);
  
  m_Nodes.push_back(scenenode);  
  
  return planeobj;
}

Vis3DObject* SceneManager::createPlyObject(const std::string& _pUnitName, const std::string& _pPlyObjName, const std::string& _pPlyFilename)
{
  SceneNode* scenenode = new SceneNode(_pPlyObjName + "_Node");
  PlyObject* plyobj = new PlyObject(_pUnitName, _pPlyObjName, _pPlyFilename);
  scenenode->addObject(plyobj);
  
  m_Nodes.push_back(scenenode);
  
  return plyobj;
}

Vis3DObject* SceneManager::getObjectPtrByName(const std::string& _pObjName)
{
  for(size_t i = 0; i < m_Nodes.size(); i++)
  {
    for(size_t j = 0; j < m_Nodes[i]->m_ObjectPtrs.size(); j++)
    {
      if(m_Nodes[i]->m_ObjectPtrs[j]->getName() == _pObjName)
	return m_Nodes[i]->m_ObjectPtrs[j];
    }
  }
  
  return 0;
}

SceneManager::~SceneManager()
{
  
}