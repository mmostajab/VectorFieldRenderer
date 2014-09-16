#include "sphere.h"

#include <vector>

Sphere3D::Sphere3D(const float& _pRadius, const int& _pSlices, const int& _pStacks, const char* _pTextureFilename):
	m_Radius(_pRadius), m_Slices(_pSlices), m_Stacks(_pStacks), m_TextureFilename(_pTextureFilename), m_X(0.0f), m_Y(0.0f), m_Z(0.0f), m_RotDeg(0.0f)
{
  //m_ShaderHeader = "#version 130\n#define SIMPLE_TEXTURING\n";
  m_ShaderHeader = "#version 130\n#define SPHERICAL_MAPPING\n";
  m_ShaderPrg = new ShaderProgram("../../srcsphere.vert", "../../srcsphere.frag");
//   m_TexturePtr = new glcTexture2D(m_TextureFilename.c_str());

  b_Initialized = false;
  b_CubeMapping = false;
}

Sphere3D::Sphere3D(const float& _pRadius, const int& _pSlices, const int& _pStacks):
	m_Radius(_pRadius), m_Slices(_pSlices), m_Stacks(_pStacks), m_RotDeg(0.0f)
{
  m_ShaderHeader = "#version 130\n#define CUBE_MAPPING\n";
  m_ShaderPrg = new ShaderProgram("../../srcsphere.vert", "../../srcsphere.frag");

//   m_CubeTexturePtr = new glcTextureCube();

  b_Initialized = false;
  b_CubeMapping = true;
}

void Sphere3D::init(const float& _pX, const float& _pY, const float& _pZ)
{
	m_ShaderPrg->init(m_ShaderHeader);
	m_ShaderPrg->bindAttribute(0, "a_Vertex");
	m_ShaderPrg->bindAttribute(1, "a_TexCoord");
	m_ShaderPrg->bindAttribute(2, "a_Normal");
	m_ShaderPrg->link();

// 	if(b_CubeMapping)
// 		m_CubeTexturePtr->init(_pX, _pY, _pZ);
// 	else
// 		m_TexturePtr->init();

	const float PI = 3.141562f;
	const float PI2overSlices = 2 * PI / m_Slices;
	const float PIoverStacks = PI / m_Stacks;

	std::vector<SphereVert> vertices;
	float phi, thetha, cosPhi, sinPhi;
	float x, y, z;
	float s, t;
	for(int i = 0; i < m_Stacks; i++)
	{
		int begIndx = vertices.size();
		phi = (float)i * PIoverStacks;
		cosPhi = cos(phi);
		sinPhi = sin(phi);
		for(int j = 0; j < m_Slices; j++)
		{
			thetha = (float)j * PI2overSlices;
			x = cos(thetha) * sinPhi * m_Radius;
			y = sin(thetha) * sinPhi * m_Radius;
			z = cosPhi * m_Radius;

			s  = (float)j / (float)m_Slices;
			t  = (float)i / (float)m_Stacks;
			//s = thetha / (2 * PI);
			//t = phi / PI;


			SphereVert v(x, y, z, s, t);
			v.computeNormal();
			vertices.push_back(v);

			float phi2 = (float)(i + 1) / (float)m_Stacks * PI;
			float cosPhi2 = cos(phi2);
			float sinPhi2 = sin(phi2);
			x = cos(thetha) * sinPhi2 * m_Radius;
			y = sin(thetha) * sinPhi2 * m_Radius;
			z = cosPhi2 * m_Radius;

			s = (float)j / (float)m_Slices;
			t = (float)(i + 1) / (float)m_Stacks;
			//s = thetha / (2 * PI);
			//t = phi2 / PI;

			SphereVert v2(x, y, z, s, t);
			v2.computeNormal();
			vertices.push_back(v2);
		}

		vertices.push_back(vertices[begIndx]);
		vertices.push_back(vertices[begIndx+1]);
	}

	glGenBuffers(1, &m_BufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SphereVert), &vertices[0], GL_STATIC_DRAW);

	m_X = _pX;
	m_Y = _pY;
	m_Z = _pZ;
	
	b_Initialized = true;
}

void Sphere3D::render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat)
{
  glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(m_X, m_Y, m_Z));

  if(!b_CubeMapping)
  {
    //m_RotDeg += 0.3;
    //modelMat *= glm::rotate(glm::mat4(1.0f), m_RotDeg / 180.0f * glm::pi<float>(), glm::vec3(1, 1, 1));
  }

  m_ShaderPrg->use();
  m_ShaderPrg->sendUniformMatrix4fv("model_matrix", modelMat);
  m_ShaderPrg->sendUniformMatrix4fv("view_matrix", _pViewMat);
  m_ShaderPrg->sendUniformMatrix4fv("projection_matrix", _pProjMat);
  m_ShaderPrg->sendUniform("texture0", 0);

//   if(b_CubeMapping)
//   {
//     m_ShaderPrg->sendUniform3fv("camera_position", 0.0f, 0.0f, 0.0f);
//     m_CubeTexturePtr->use();
//   }
//   else
//     m_TexturePtr->use();

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  unsigned int stride = sizeof(SphereVert);
  glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
  glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, stride, (char*)0);
  glVertexAttribPointer((GLint)1, 2, GL_FLOAT, GL_FALSE, stride, ((char*)0) + 3 * sizeof(float));
  glVertexAttribPointer((GLint)2, 3, GL_FLOAT, GL_FALSE, stride, ((char*)0) + 5 * sizeof(float));

  int nVerticesPerStrip = 2 * (m_Slices + 1);
  int start = 0;
  for(int i = 0; i < m_Stacks; i++)
  {
    glDrawArrays(GL_TRIANGLE_STRIP, start, 2 * (m_Slices + 1));
    start += nVerticesPerStrip;
  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

void Sphere3D::deinit()
{
	
}

void Sphere3D::setPosition(const float& _pX, const float& _pY, const float& _pZ)
{
  m_X = _pX;
  m_Y = _pY;
  m_Z = _pZ;
  
//   m_CubeTexturePtr->setPosition(m_X, m_Y, m_Z);
}

// glcTextureCube* Sphere3D::getTextureCubePtr()
// {
//   return m_CubeTexturePtr;
// }

Sphere3D::~Sphere3D()
{

}