#ifndef __VIS_TOOL_RENDER_H__
#define __VIS_TOOL_RENDER_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
private:
  int m_Width, m_Height;
  glm::mat4 m_ViewMat, m_ProjMat;
  
  bool b_Initialized;
  
public:
  Renderer(const int& _pWidth, const int& _pHeight);
  
  void init();
  void prepare(const float& _pDeltaTime);
  void render();
  
  ~Renderer();
};

#endif