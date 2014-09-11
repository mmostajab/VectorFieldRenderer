#ifndef __VIS_TOOL_MODELVIEWCAMERA_H__
#define __VIS_TOOL_MODELVIEWCAMERA_H__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ModelViewerCam
{
private:
  glm::vec3 m_EyePos;
  glm::vec3 m_LookAtPos;
  glm::vec3 m_UpVec;
  
  glm::mat4 m_ViewMat;
  
public:
  ModelViewerCam(const glm::vec3& _pEyePos, const glm::vec3& _pLookAtPos, const glm::vec3& _pUpVec);
  
  void init();
  
  glm::mat4 getViewMat() const;
  
  ~ModelViewerCam();
};

#endif