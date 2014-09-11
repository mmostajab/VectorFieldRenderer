#ifndef __SPHERE_3D_H__
#define __SPHERE_3D_H__

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"
//#include "Texture2D.h"
//#include "TextureCube.h"

#include <string>
#include <math.h>

struct SphereVert
{
	float x, y, z;
	float s, t;
	float nx, ny, nz;

	SphereVert(const float& _pX, const float& _pY, const float& _pZ, const float& _pS, const float& _pT):
		x(_pX), y(_pY), z(_pZ), s(_pS), t(_pT), nx(_pX), ny(_pY), nz(_pZ)
	{
	}

	void normalizeNormal()
	{
		float l2 = nx * nx + ny * ny + nz * nz;
		float l = sqrt(l2);

		if(l > 0.0001f)
		{
			nx /= l;
			ny /= l;
			nz /= l;
		}
	}

	void computeNormal()
	{
		float l2 = x * x + y * y + z * z;
		float l = sqrt(l2);

		if(l > 0.0001f)
		{
			nx = x / l;
			ny = y / l;
			nz = z / l;
		}	
	}
};

class Sphere3D
{
private:
	GLuint m_BufferId;

	float m_Radius;
	int m_Slices, m_Stacks;

	std::string m_ShaderHeader;
	ShaderProgram* m_ShaderPrg;

	std::string m_TextureFilename;
	bool b_CubeMapping;
	bool b_Initialized;
	
	float m_X, m_Y, m_Z;
	float m_RotDeg;

// 	union {
// 		glcTexture2D* m_TexturePtr;
// 		glcTextureCube* m_CubeTexturePtr;
// 	};

public:
	Sphere3D(const float& _pRadius, const int& _pSlices, const int& _pStacks, const char* _pTextureFilename);
	Sphere3D(const float& _pRadius, const int& _pSlices, const int& _pStacks);

	void init(const float& _pX = 0.0f, const float& _pY = 0.0f, const float& _pZ = 0.0f);

	void render(const glm::mat4& _pViewMat, const glm::mat4& _pProjMat);

	void deinit();
	
	void setPosition(const float& _pX, const float& _pY, const float& _pZ);

	~Sphere3D();
};

#endif