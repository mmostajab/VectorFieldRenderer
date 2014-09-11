#include "shaderprogram.h"

#include <iostream>
#include <fstream>
#include <vector>

ShaderProgram::ShaderProgram(const char* _pVSFileName, const char* _pFSFileName): b_Initialized(false)
{
	m_VS.fileName = _pVSFileName;
	m_FS.fileName = _pFSFileName;
}

void ShaderProgram::init()
{
	m_VS.id = glCreateShader(GL_VERTEX_SHADER);
	m_FS.id = glCreateShader(GL_FRAGMENT_SHADER);
	m_ProgramID = glCreateProgram();

	m_VS.source = readFile(m_VS.fileName);
	m_FS.source = readFile(m_FS.fileName);

	const GLchar* vsProgramTextPtr = static_cast<const GLchar*>(m_VS.source.c_str());
	const GLchar* fsProgramTextPtr = static_cast<const GLchar*>(m_FS.source.c_str());
 
	glShaderSource(m_VS.id, 1, &vsProgramTextPtr, NULL);
	glShaderSource(m_FS.id, 1, &fsProgramTextPtr, NULL);

	if(!compileShader(m_VS) || !compileShader(m_FS))
	{
		std::cerr << "Could not compile the shaders. There is something wrong!!!";
		b_Initialized = false;
		return;
	}

	glAttachShader(m_ProgramID, m_VS.id);
	glAttachShader(m_ProgramID, m_FS.id);

	glLinkProgram(m_ProgramID);
	b_Initialized = true;
}

void ShaderProgram::init(const std::string& _pShaderHeader)
{
    m_VS.id = glCreateShader(GL_VERTEX_SHADER);
    m_FS.id = glCreateShader(GL_FRAGMENT_SHADER);
    m_ProgramID = glCreateProgram();

    m_VS.source = _pShaderHeader;
    m_FS.source = _pShaderHeader;

    m_VS.source += readFile(m_VS.fileName);
    m_FS.source += readFile(m_FS.fileName);
    
    const GLchar* vsProgramTextPtr = static_cast<const GLchar*>(m_VS.source.c_str());
    const GLchar* fsProgramTextPtr = static_cast<const GLchar*>(m_FS.source.c_str());
 
    glShaderSource(m_VS.id, 1, &vsProgramTextPtr, NULL);
    glShaderSource(m_FS.id, 1, &fsProgramTextPtr, NULL);

    if(!compileShader(m_VS) || !compileShader(m_FS))
    {
        std::cerr << "Could not compile the shaders. There is something wrong!!!";
        b_Initialized = false;
        return;
    }

    glAttachShader(m_ProgramID, m_VS.id);
    glAttachShader(m_ProgramID, m_FS.id);

    glLinkProgram(m_ProgramID);
    b_Initialized = true;
}

void ShaderProgram::link()
{
	glLinkProgram(m_ProgramID);
}

void ShaderProgram::use()
{
	glUseProgram(m_ProgramID);
}

GLuint ShaderProgram::getUniformLocation(const std::string& _pUniformName)
{
	std::map<std::string, GLuint>::iterator i = m_UniformsMap.find(_pUniformName);
    if (i == m_UniformsMap.end())
    {
        GLuint location = glGetUniformLocation(m_ProgramID, _pUniformName.c_str());
        m_AttributesMap.insert(std::make_pair(_pUniformName, location));
        return location;
    }

    return (*i).second;
}

GLuint ShaderProgram::getAttributeLocation(const std::string& _pAttributeName)
{
	std::map<std::string, GLuint>::iterator i = m_AttributesMap.find(_pAttributeName);
    if (i == m_AttributesMap.end())
    {
        GLuint location = glGetAttribLocation(m_ProgramID, _pAttributeName.c_str());
        m_AttributesMap.insert(std::make_pair(_pAttributeName, location));
        return location;
    }

    return (*i).second;
}

void ShaderProgram::deinit()
{
	glDetachShader(m_ProgramID, m_VS.id);
	glDetachShader(m_ProgramID, m_FS.id);
    glDeleteShader(m_VS.id);
    glDeleteShader(m_FS.id);
    glDeleteShader(m_ProgramID);
}

bool ShaderProgram::isInitialized()
{
	return b_Initialized;
}

ShaderProgram::~ShaderProgram()
{
	deinit();
}

std::string ShaderProgram::readFile(const std::string& _pFileName)
{
	std::ifstream fileIn(_pFileName.c_str());

    if (!fileIn.good())
    {
        std::cerr << "Could not load shader: " << _pFileName << std::endl;
        return std::string();
    }

    std::string stringBuffer(std::istreambuf_iterator<char>(fileIn), (std::istreambuf_iterator<char>()));
    return stringBuffer;
}

bool ShaderProgram::compileShader(const ShaderInfo& _pShaderInfo)
{
	glCompileShader(_pShaderInfo.id);
    GLint result = 0xDEADBEEF;
    glGetShaderiv(_pShaderInfo.id, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        std::cout << "Could not compile shader: " << _pShaderInfo.id << " : " << _pShaderInfo.fileName << std::endl;
        outputShaderLog(_pShaderInfo);
	
	std::cout << "Source = \n\n" << _pShaderInfo.source;
        
        return false;
    }

    return true;
}

void ShaderProgram::sendUniform(const std::string& _pUniformName, const int& _pId)
{
    GLuint location = getUniformLocation(_pUniformName);
    glUniform1i(location, _pId);
}

void ShaderProgram::sendUniformMatrix4fv(const std::string& _pUniformName, const float* _pMatrixPtr, bool _pTranspose)
{
	GLuint location = getUniformLocation(_pUniformName);
	glUniformMatrix4fv(location, 1, _pTranspose, _pMatrixPtr);
}

void ShaderProgram::sendUniformMatrix4fv(const std::string& _pUniformName, const glm::mat4& _pMatrix, bool _pTranspose)
{
	GLuint location = getUniformLocation(_pUniformName);
	glUniformMatrix4fv(location, 1, _pTranspose, glm::value_ptr(_pMatrix));
}

void ShaderProgram::sendUniform3fv(const std::string& _pUniformName, const float& _pV1, const float& _pV2, const float& _pV3)
{
    GLuint location = getUniformLocation(_pUniformName);
    glUniform3f(location, _pV1, _pV2, _pV3);
}

void ShaderProgram::sendUniform3fv(const std::string& _pUniformName, const glm::vec3& _pVec)
{
  GLuint location = getUniformLocation(_pUniformName);
  glUniform3f(location, _pVec.x, _pVec.y, _pVec.z);
}

void ShaderProgram::bindAttribute(const unsigned int& _pIndex, const std::string& _pAttributeName)
{
	glBindAttribLocation(m_ProgramID, _pIndex, _pAttributeName.c_str());
}

void ShaderProgram::outputShaderLog(const ShaderInfo& _pShaderInfo)
{
	std::vector<char> infoLog;
	infoLog.resize(1000);
    GLint infoLen;
	glGetShaderiv(_pShaderInfo.id, GL_INFO_LOG_LENGTH, &infoLen);
	infoLog.resize(infoLen);

    std::cerr << "GLSL Shader: Shader contains errors, please validate this shader!" << std::endl;
    glGetShaderInfoLog(_pShaderInfo.id, infoLog.size(), &infoLen, &infoLog[0]);

    std::cerr << std::string(infoLog.begin(), infoLog.end()) << std::endl;
}