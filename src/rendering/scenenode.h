#ifndef __VIS_TOOL_SCENE_NODE_H__
#define __VIS_TOOL_SCENE_NODE_H__

#include "vis3dobject.h"

#include <vector>
#include <string>

class SceneManager;
class Renderer;

class SceneNode
{
  friend class SceneManager;
  friend class Renderer;
private:
  std::string m_Name;
  std::vector<Vis3DObject*> m_ObjectPtrs;
  
public:
  SceneNode(const std::string& _pNodeName);
  
  void addObject(Vis3DObject* _pObj);
  
  ~SceneNode();
};

#endif