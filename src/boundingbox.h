#ifndef __VIS_TOOL_BOUNDING_BOX_H__
#define __VIS_TOOL_BOUNDING_BOX_H__

#include "vis3dobject.h"
#include "shaderprogram.h"

#include <vector>

#include <float.h>

class BoundingBox: public Vis3DObject
{
private:
  glm::vec3 m_MinCorner, m_MaxCorner;	// Dimensions
  glm::vec3 m_Segs;		// Number of Segments of each Dimensions
  
  GLuint m_BufferID, m_DetailedBufferID;
  GLuint m_IndicesBufferID, m_DetailedIndicesBufferID;
  std::vector<glm::vec3> m_Points;
  std::vector<int> m_Indices;
  std::vector<glm::vec3> m_DetailedPoints;
  std::vector<int> m_DetailedIndices;
  
  ShaderProgram* m_ShaderPrg;
  
  bool b_DetailedMode;
  
public:
  BoundingBox(const std::string& _pBBName, const glm::vec3& _pCorner1 = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX), const glm::vec3& _pCorner2 = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX));
  BoundingBox(const std::string& _pBBName, const float& _pLength, const float& _pWidth, const float& _pHeight, const int& _pLSegs = 1, const int& _pWSegs = 1, const int& _pHSegs = 1);
  
  void init();
  void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat);
  void render(const glm::mat4& _pModelViewProjMat);
  void deinit();
  
  void addPoint(const glm::vec3& _pPoint);
  void setCorners(const glm::vec3& _pCorner1, const glm::vec3& _pCorner2);
  
  glm::vec3 getDims() const;
  
  void setOutlineMode();
  void setDetailedMode();
  
  ~BoundingBox();
};

#endif