#ifndef __VIS_TOOL_CONE_H__
#define __VIS_TOOL_CONE_H__

#include "vis3dobject.h"

#include <string>

class Cone: public Vis3DObject
{
private:
  
  
public:
  Cone(const std::string& _pConeName);
  
  void init();
  void render();
  
  ~Cone();
};

#endif