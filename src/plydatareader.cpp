#include "PlyDataReader.h"

char* CPlyDataReader::m_VertexDataPtr = 0;
int CPlyDataReader::m_CurrVertexByte = 0;
unsigned int CPlyDataReader::m_nVertices = 0;
unsigned int CPlyDataReader::m_nFaces = 0;

char* CPlyDataReader::m_IndexDataPtr = 0;
int CPlyDataReader::m_CurrIndexByte = 0;

CPlyDataReader* CPlyDataReader::m_SingletonPtr = 0;
CPlyDataReaderDestructor CPlyDataReader::m_DestructorObject;
p_ply CPlyDataReader::m_PlyParser;