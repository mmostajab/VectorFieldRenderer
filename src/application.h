#ifndef __VIS_TOOL_APPLICATION_H__
#define __VIS_TOOL_APPLICATION_H__

#include "renderer.h"

class VisApplication
{
private:
  Renderer m_Renderer;
  
  bool b_Initialized;
  
public:
  VisApplication(const int& _pWidth, const int& _pHeight);
  
  void init();
  
  void prepare(const float& _pDeltaTime);
  void render();
  void onResize(const int& _pWidth, const int& _pHeight);
  
  void deinit();
  
  bool isInitialized();
  
  ~VisApplication();
};

#endif