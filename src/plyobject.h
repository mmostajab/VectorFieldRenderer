#pragma once

#include "vis3dobject.h"

#include "plydatareader.h"

class PlyObject: public Vis3DObject
{
protected:
	long m_UserDataLength;
	void* m_UserDataPtr;

	int m_VertexDataLength;
	void* m_VertexData;
	int m_nVertices;
	

	void* m_IndexData;
	int m_IndexDataLength;
	int m_nFaces;
	SIZE_T m_nIndicesInFaceStride;
	int m_IndexStride;
	
	

public:
	PlyObject(const char* _pFileName);

	void init();
	virtual void render();
	void deinit();

	~PlyObject(void);

private:
	
	int getTypeLength(e_ply_type _pType);
};