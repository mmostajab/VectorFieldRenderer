#ifndef __VIS_TOOL_RENDER_H__
#define __VIS_TOOL_RENDER_H__

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "boundingbox.h"
#include "plyobject.h"
#include "camera.h"
#include "plane.h"

class Renderer
{
private:
  int m_Width, m_Height;
  glm::mat4 m_ProjMat;
  
  bool b_Initialized;
  
  Camera m_Camera;
  
public:
  Renderer(const int& _pWidth, const int& _pHeight);
  
  void init();
  void initCamera();
  
  void prepare(const float& _pDeltaTime);
  void render();
  
  void deinit();
  
  void onResize(const int& _pWidth, const int& _pHeight);
  void moveCam(const float& x, const float& y);
  void moveCam(bool _pForward, bool _pBack, bool _pLeft, bool _pRight, bool _pUp, bool _pDown);
  
  bool isInitialized();
  
  ~Renderer();
};

#endif