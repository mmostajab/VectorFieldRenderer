#include "renderer.h"

Renderer::Renderer(const int& _pWidth, const int& _pHeight): m_Width(_pWidth), m_Height(_pHeight), m_ProjMat(1.0f), m_ViewMat(1.0f)
{
}
  
void Renderer::init()
{
  GLenum err = glewInit();
  if(err != GLEW_OK)
  {
    return;
  }
  
  glEnable(GL_DEPTH_TEST);
  
  b_Initialized = true;
}

void Renderer::prepare(const float& _pDeltaTime)
{
  
}

void Renderer::render()
{
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::deinit()
{
  
}

void Renderer::onResize(const int& _pWidth, const int& _pHeight)
{
  m_Width = _pWidth;
  m_Height = _pHeight;
  
  glViewport(0, 0, m_Width, m_Height);
  m_ProjMat = glm::perspective(glm::pi<float>() / 3.0f, static_cast<float>(m_Width) / static_cast<float>(m_Height), 0.01f, 100.0f);
}

bool Renderer::isInitialized()
{
  return b_Initialized;
}

Renderer::~Renderer()
{
  
}