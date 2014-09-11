#ifndef __GLC_SHADER_PROGRAM__
#define __GLC_SHADER_PROGRAM__

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <map>

struct ShaderInfo
{
	GLuint id;
	std::string fileName;
	std::string source;
};

class ShaderProgram
{
private:
	GLuint m_ProgramID;

	ShaderInfo m_VS, m_FS;
	bool b_Initialized;

	std::map<std::string, GLuint> m_UniformsMap;
	std::map<std::string, GLuint> m_AttributesMap;

public:
	ShaderProgram(const char* _pVSFileName, const char* _pFSFileName);

	void init();
	void init(const std::string& _pShaderHeader);

	void link();
	void use();

	GLuint getUniformLocation(const std::string& _pUniformName);
	GLuint getAttributeLocation(const std::string& _pAttributeName);

	void sendUniform(const std::string& _pUniformName, const int& _pId);
	void sendUniformMatrix4fv(const std::string& _pUniformName, const float* _pMatrixPtr, bool _pTranspose = false);
	void sendUniformMatrix4fv(const std::string& _pUniformName, const glm::mat4& _pMatrix, bool _pTranspose = false);
	void sendUniform3fv(const std::string& _pUniformName, const float& _pV1, const float& _pV2, const float& _pV3);
	void sendUniform3fv(const std::string& _pUniformName, const glm::vec3& _pVec);
	void bindAttribute(const unsigned int& _pIndex, const std::string& _pAttributeName);

	void deinit();

	bool isInitialized();

	~ShaderProgram();

private:
	std::string readFile(const std::string& _pFileName);
	bool compileShader(const ShaderInfo& _pShaderInfo);
	void outputShaderLog(const ShaderInfo& _pShaderInfo);
};

#endif