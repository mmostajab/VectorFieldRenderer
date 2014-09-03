#include "application.h"

#include <iostream>

VisApplication::VisApplication(const int& _pWidth, const int& _pHeight): m_Renderer(_pWidth, _pHeight), 
  b_MoveForward(false), b_MoveBackward(false), b_MoveLeft(false), b_MoveRight(false), b_MoveUp(false), b_MoveDown(false),
  b_LButtonDown(false), b_RButtonDown(false), b_MButtonDown(false)
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
  m_Renderer.moveCam(b_MoveForward, b_MoveBackward, b_MoveLeft, b_MoveRight, b_MoveUp, b_MoveDown);
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

void VisApplication::pressKey(int key)
{
  if(key == 'W')
    b_MoveForward = true;
      
  if(key == 'A')
    b_MoveLeft = true;
      
  if(key == 'S')
    b_MoveBackward = true;
      
  if(key == 'D')
    b_MoveRight = true;
      
  if(key == 'Q')
    b_MoveUp = true;      
    
  if(key == 'E')
    b_MoveDown = true;
}

void VisApplication::releaseKey(int key)
{
  if(key == 'W')
    b_MoveForward = false;
      
  if(key == 'A')
    b_MoveLeft = false;
      
  if(key == 'S')
    b_MoveBackward = false;
      
  if(key == 'D')
    b_MoveRight = false;
      
  if(key == 'Q')
    b_MoveUp = false;      
    
  if(key == 'E')
    b_MoveDown = false;
}

void VisApplication::mouseDown(int button)
{
  if(button == 0)
    b_LButtonDown = true;
  
  if(button == 1)
    b_RButtonDown = true;
  
  if(button == 2)
    b_MButtonDown = true;
}

void VisApplication::mouseMove(double x, double y)
{
  if(b_LButtonDown)
    m_Renderer.moveCam(x, y);
}

void VisApplication::mouseUp(int button)
{
  if(button == 0)
    b_LButtonDown = false;
  
  if(button == 1)
    b_RButtonDown = false;
  
  if(button == 2)
    b_MButtonDown = false;
}

bool VisApplication::isInitialized()
{
  return b_Initialized;
}

VisApplication::~VisApplication()
{
  
}