#include "renderer.h"

#include "scenemanager.h"

#include <iostream>

Renderer::Renderer(const int& _pWidth, const int& _pHeight): m_Width(_pWidth), m_Height(_pHeight), m_ProjMat(1.0f), m_Camera()
      //plyobj("../data/happybudhaa/happy.ply")
      //  plyobj("../data/antenne.ply")
      //plyobj("gate", "../data/gate.ply"),
      
      /*m_Camera(glm::vec3(-15, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))*/
      //m_Plane("plane", glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), 10, 10)
{
  //plyobj.setObjectDims(glm::vec3(10, 20, 10));		// happy
  //plyobj.setObjectDims(glm::vec3(5, 10, 10));		// antenna
  
 // plyobj.setPosition(0, 1.5f, 0);
 // plyobj.setOrientation(-glm::pi<float>() / 2.0f, 0.0f, 0.0f);
  //plyobj.setObjectDims(glm::vec3(3, 0.2, 2));	// gate
  
  //plyobj.setObjectDims(glm::vec3(0.5, 1.0f, 1.0f));
  //plyobj.setPosition(3, 3, 3);
  //plyobj.setOrientation(glm::pi<float>() / 4, 0, 0);
}
  
void Renderer::init()
{
  GLenum err = glewInit();
  if(err != GLEW_OK)
  {
    return;
  }
  
  glEnable(GL_DEPTH_TEST);
  
  for(size_t i = 0; i < SceneManager::getSingletonPtr()->m_Nodes.size(); i++)
  {
    for(size_t j = 0; j < SceneManager::getSingletonPtr()->m_Nodes[i]->m_ObjectPtrs.size(); j++)
    {
      SceneManager::getSingletonPtr()->m_Nodes[i]->m_ObjectPtrs[j]->init();
    }
  }
  
  //plyobj.init();
  //m_Plane.init();
  
  b_Initialized = true;
}

void Renderer::initCamera()
{
  m_Camera.SetMode(FREE);
  m_Camera.SetPosition(glm::vec3(2, 2, 4));
  m_Camera.SetLookAt(glm::vec3(0, 0, 0));
  m_Camera.SetClipping(0.01f, 10000.0f);
  m_Camera.SetFOV(60);
}

void Renderer::prepare(const float& _pDeltaTime)
{
}

void Renderer::render()
{
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 projMat;
  glm::mat4 viewMat;
  glm::mat4 modelMat;
  m_Camera.Update();
  m_Camera.GetMatricies(projMat, viewMat, modelMat);
 
  for(size_t i = 0; i < SceneManager::getSingletonPtr()->m_Nodes.size(); i++)
  {
    for(size_t j = 0; j < SceneManager::getSingletonPtr()->m_Nodes[i]->m_ObjectPtrs.size(); j++)
    {
      SceneManager::getSingletonPtr()->m_Nodes[i]->m_ObjectPtrs[j]->render(viewMat, projMat);
    }
  }
  
  //plyobj.render(viewMat, projMat);
  //m_Plane.render(viewMat, projMat);
}

void Renderer::deinit()
{
  
}

void Renderer::onResize(const int& _pWidth, const int& _pHeight)
{
  m_Width = _pWidth;
  m_Height = _pHeight;
  
  initCamera();
  m_Camera.SetViewport(0, 0, m_Width, m_Height);
  m_Camera.Update();
  
  glViewport(0, 0, m_Width, m_Height);
  m_ProjMat = glm::perspective(glm::pi<float>() / 4.0f, static_cast<float>(m_Width) / static_cast<float>(m_Height), 0.01f, 100.0f);
}

void Renderer::moveCam(const float& x, const float& y)
{
  m_Camera.Move2D(x, y);
}

void Renderer::moveCam(bool _pForward, bool _pBack, bool _pLeft, bool _pRight, bool _pUp, bool _pDown)
{
  if(_pForward)
    m_Camera.Move(FORWARD);
  
  if(_pBack)
    m_Camera.Move(BACK);
  
  if(_pLeft)
    m_Camera.Move(LEFT);
  
  if(_pRight)
    m_Camera.Move(RIGHT);
  
  if(_pUp)
    m_Camera.Move(UP);
  
  if(_pDown)
    m_Camera.Move(DOWN);
}

bool Renderer::isInitialized()
{
  return b_Initialized;
}

Renderer::~Renderer()
{
  
}