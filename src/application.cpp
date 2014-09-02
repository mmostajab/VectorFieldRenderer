#include "application.h"

VisApplication::VisApplication(const int& _pWidth, const int& _pHeight): m_Renderer(_pWidth, _pHeight)
{
  
}
  
void VisApplication::init()
{
  m_Renderer.init();
  
  b_Initialized = true;
}

void VisApplication::prepare(const float& _pDeltaTime)
{
  m_Renderer.prepare(_pDeltaTime);
}

void VisApplication::render()
{
  m_Renderer.render();
}

void VisApplication::onResize(const int& _pWidth, const int& _pHeight)
{
  m_Renderer.onResize(_pWidth, _pHeight);
}

void VisApplication::deinit()
{
  m_Renderer.deinit();
}

bool VisApplication::isInitialized()
{
  return b_Initialized;
}

VisApplication::~VisApplication()
{
  
}