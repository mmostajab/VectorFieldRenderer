#ifndef __VIS_TOOL_PLY_DATA_READER_H__
#define __VIS_TOOL_PLY_DATA_READER_H__

#include "rply.h"

class CPlyDataReader
{
	friend CPlyDataReaderDestructor;
private:
	static CPlyDataReader* m_SingletonPtr;
	static CPlyDataReaderDestructor m_DestructorObject;

	static p_ply m_PlyParser;

	static unsigned int m_nVertices;
	static unsigned int m_nFaces;

	static char* m_VertexDataPtr;
	static int m_CurrVertexByte;
	static char* m_IndexDataPtr;
	static int m_CurrIndexByte;
	
private:
	CPlyDataReader()
	{
		m_VertexDataPtr = 0;
		m_IndexDataPtr = 0;
	}

	~CPlyDataReader()
	{
		delete m_VertexDataPtr;
		delete m_IndexDataPtr;
		//delete m_PlyParser;
	}

public:
	static CPlyDataReader* getSingletonPtr()
	{
	  if(m_SingletonPtr == 0)
	  {
		  m_SingletonPtr = new CPlyDataReader;
		  m_DestructorObject.setSingletonPointer(m_SingletonPtr);
	  }
	  
	  return m_SingletonPtr;
	}

	void readDataInfo(const char* _pFileName, void* _pUserDataPtr, const long& _pUserDataLen)
	{
	  HRESULT hr;

	  // Open the PLY file
	  m_PlyParser = ply_open(_pFileName, PlyParserMessageHandlerProc, _pUserDataLen, _pUserDataPtr);

	  /**  Read the header of the ply which shows that which data is offered by PLY file. For example, the vertices has which format and how many vertices
	    * exists. The same information for other elements (Faces, Normal Vectors, ...) of the PLY object.
	    */
	  hr = ply_read_header(m_PlyParser);
  
	  p_ply_element CurrElement;
	  CurrElement = ply_get_next_element(m_PlyParser, NULL);

	  while(CurrElement != 0)
	  {
	    long nElements;
	    const char* ElementName;

	    ply_get_element_info(CurrElement, ((const char**)&ElementName), &nElements);

	    if(!strcmp(ElementName, "vertex"))
	    {
		    this->m_nVertices = nElements;
	    }
	    else if(!strcmp(ElementName, "face"))
	    {
		    this->m_nFaces = nElements;
	    }

	    CurrElement = ply_get_next_element(m_PlyParser, CurrElement);

	    ElementName = 0;
	  }
	}

  unsigned int getNumVertices()
  {
	  return m_nVertices;
  }

  unsigned int getNumFaces()
  {
	  return m_nFaces;
  }

  void readData(void* _pVertexBuffer, void* _pIndexBuffer)
  {
	  m_VertexDataPtr = (char*)_pVertexBuffer;
	  m_IndexDataPtr = (char*)_pIndexBuffer;

	  ply_set_read_cb(m_PlyParser, "vertex", "x", VertexHandler, 0, 0);
	  ply_set_read_cb(m_PlyParser, "vertex", "y", VertexHandler, 0, 0);
	  ply_set_read_cb(m_PlyParser, "vertex", "z", VertexHandler, 0, 0);
	  ply_set_read_cb(m_PlyParser, "vertex", "nx", VertexHandler, 0, 0);
	  ply_set_read_cb(m_PlyParser, "vertex", "ny", VertexHandler, 0, 0);
	  ply_set_read_cb(m_PlyParser, "vertex", "nz", VertexHandler, 0, 0);

	  ply_set_read_cb(m_PlyParser, "face", "vertex_indices", FaceHandler, 0, 0);

	  ply_read(m_PlyParser);
  }

  static int VertexHandler(p_ply_argument _pArgument)
  {
    p_ply_property Property;
    const char* PropertyName;
    e_ply_type PropertyType;
    e_ply_type PropertyValueType;

    float Value = (float)ply_get_argument_value(_pArgument);

    ply_get_argument_property(_pArgument, &Property, 0, 0);
    ply_get_property_info(Property, &PropertyName, &PropertyType, 0, &PropertyValueType);
		    
    int WriteLength = getTypeLength(PropertyType);
    memcpy(m_VertexDataPtr + m_CurrVertexByte, &Value,WriteLength);
    m_CurrVertexByte += WriteLength;

    return 1;
  }

  static int FaceHandler(p_ply_argument _pArgument)
  {
    p_ply_property Property;
    
    float Value = (float)ply_get_argument_value(_pArgument);
    long Value_Index = -1;

    ply_get_argument_property(_pArgument, &Property, 0, &Value_Index);

    if(Value_Index >= 0)
    {
	    int WriteLength = 4;
	    memcpy(m_IndexDataPtr + m_CurrIndexByte, &Value, sizeof(float));
	    m_CurrIndexByte += WriteLength;
    }

    return 1;
  }

  static void releaseDataHandles()
  {
	  m_CurrVertexByte = 0;
	  m_CurrIndexByte = 0;
  }

  static void PlyParserMessageHandlerProc(p_ply _pPlyObj, const char* _pMessage)
  {
    std::cout << "===> PLY Parser Message: " << _pMessage << std::endl;
  }

  static int getTypeLength(e_ply_type _pType)
  {
  switch(_pType)
  {
  case PLY_CHAR:
    return 1;
    break;

  case PLY_DOUBLE:
    return 8;
    break;
	  
  case PLY_FLOAT:
    return 4;
    break;

  case PLY_FLOAT32:
    return 4;
    break;

  case PLY_FLOAT64:
    return 8;
    break;

  case PLY_INT:
    return 4;
    break;

  case PLY_INT8:
    return 1;
    break;

  case PLY_INT16:
    return 2;
    break;

  case PLY_INT32:
    return 4;
    break;

  case PLY_SHORT:
    return 2;
    break;

  case PLY_UCHAR:
    return 1;
    break;

  case PLY_UINT:
    return 4;
    break;

  case PLY_UINT8:
    return 1;
    break;

  case PLY_UINT16:
    return 2;
    break;

  case PLY_UIN32:
    return 4;
    break;

  case PLY_USHORT:
    return 2;
    break;

  default:
    return -1;
  }
}

};

#endif