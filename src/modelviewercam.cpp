#include "modelviewercam.h"

ModelViewerCam::ModelViewerCam(const glm::vec3& _pEyePos, const glm::vec3& _pLookAtPos, const glm::vec3& _pUpVec): m_EyePos(_pEyePos), m_LookAtPos(_pLookAtPos), m_UpVec(_pUpVec)
{
}
  
void ModelViewerCam::init()
{
  m_ViewMat = glm::lookAt(m_EyePos, m_LookAtPos, m_UpVec);
}

glm::mat4 ModelViewerCam::getViewMat() const
{
  return m_ViewMat;
}
  
ModelViewerCam::~ModelViewerCam()
{
  
}