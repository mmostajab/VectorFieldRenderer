#include "scenenode.h"

SceneNode::SceneNode(const std::string& _pNodeName): m_Name(_pNodeName)
{
  
}
  
void SceneNode::addObject(Vis3DObject* _pObj)
{
  m_ObjectPtrs.push_back(_pObj);
}

SceneNode::~SceneNode()
{
  for(size_t i = 0; i < m_ObjectPtrs.size(); i++)
  {
    delete m_ObjectPtrs[i];
  }
}