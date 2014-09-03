#ifndef __VIS_TOOL_APPLICATION_H__
#define __VIS_TOOL_APPLICATION_H__

#include "renderer.h"

class VisApplication
{
private:
  Renderer m_Renderer;
  
  bool b_MoveForward, b_MoveBackward, b_MoveLeft, b_MoveRight, b_MoveUp, b_MoveDown;
  bool b_LButtonDown, b_RButtonDown, b_MButtonDown;
  
  bool b_Initialized;
  
public:
  VisApplication(const int& _pWidth, const int& _pHeight);
  
  void init();
  
  void prepare(const float& _pDeltaTime);
  void render();
  void onResize(const int& _pWidth, const int& _pHeight);
  
  void deinit();
  
  void pressKey(int key);
  void releaseKey(int key);
  
  void mouseDown(int button);
  void mouseMove(double x, double y);
  void mouseUp(int button);
  
  bool isInitialized();
  
  ~VisApplication();
};

#endif