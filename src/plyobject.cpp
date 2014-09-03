#include "PlyObject.h"

#include "Vertex.h"

CPlyObject::CPlyObject(const long& _pUserDataLength, void* _pUserDataPtr):	m_UserDataLength(_pUserDataLength), m_UserDataPtr(_pUserDataPtr),
																			m_VertexData(0), m_IndexData(0), m_VertexDataLength(0), m_IndexDataLength(0)
{
}

void CPlyObject::load(const char* _pFileName)
{
	CPlyDataReader::getSingletonPtr()->readDataInfo(_pFileName, 0, 0);
	
	m_VertexDataLength = CPlyDataReader::getSingletonPtr()->getNumVertices();
	m_VertexData = new VertexPN[m_VertexDataLength];
	
	m_nFaces = CPlyDataReader::getSingletonPtr()->getNumFaces();
	m_IndexDataLength = 3 * m_nFaces;
	m_IndexData = new unsigned int[m_IndexDataLength];

	CPlyDataReader::getSingletonPtr()->readData(m_VertexData, m_IndexData);

	CPlyDataReader::getSingletonPtr()->releaseDataHandles();
}

void CPlyObject::create(ID3D11Device* _pD3DDevicePtr)
{
	D3D11_BUFFER_DESC bd = {0};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = m_VertexDataLength * sizeof(VertexPN);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData = {0};
	InitData.pSysMem = m_VertexData;

	_pD3DDevicePtr->CreateBuffer(&bd, &InitData, &m_VertexBuffer);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = m_IndexDataLength * sizeof(unsigned int);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	InitData.pSysMem = m_IndexData;

	_pD3DDevicePtr->CreateBuffer(&bd, &InitData, &m_IndexBuffer);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT nElements = sizeof(layout) / sizeof(layout[0]);

	m_Effect->createLayout(_pD3DDevicePtr, layout, nElements, &m_InputLayout);
}

void CPlyObject::render(ID3D11DeviceContext* _pD3DDeviceContextPtr)
{
	UINT Stride = sizeof(VertexPN);
	UINT Offset = 0;

	_pD3DDeviceContextPtr->IASetVertexBuffers(0, 1, &m_VertexBuffer, &Stride, &Offset);
	_pD3DDeviceContextPtr->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	_pD3DDeviceContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_pD3DDeviceContextPtr->IASetInputLayout(m_InputLayout);

	m_Effect->apply(0, _pD3DDeviceContextPtr);
	_pD3DDeviceContextPtr->DrawIndexed(m_nFaces * 3, 0, 0);
	//_pD3DDeviceContextPtr->Draw(3, 0);
}

void CPlyObject::release()
{
	C3DMesh::release();
	/*
	if(m_IndexData)
		delete[] m_IndexData;
	m_IndexData = 0;
	m_IndexDataLength = 0;
	*/
	if(m_IndexBuffer)
		m_IndexBuffer->Release();
	m_IndexBuffer = 0;
	/*
	if(m_UserDataPtr)
		delete[] m_UserDataPtr;
	m_UserDataPtr = 0;
	m_UserDataLength = 0;
	
	if(m_VertexData)
		delete[] m_VertexData;
	m_UserDataPtr = 0;
	*/
	if(m_IndexBuffer)
		m_IndexBuffer->Release();
	m_IndexBuffer = 0;

	if(m_InputLayout)
		m_InputLayout->Release();
	m_InputLayout = 0;

	if(m_VertexBuffer)
		m_VertexBuffer->Release();
	m_VertexBuffer = 0;
}

CPlyObject::~CPlyObject(void)
{
	
}