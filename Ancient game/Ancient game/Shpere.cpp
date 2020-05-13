#include "Shpere.h"

//コンストラクタ
Shpere::Shpere(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	:m_pDevice{ device }, m_pDeviceContext{deviceContext}
{
	// シェーダの設定
	ID3DBlob *pCompileVS = NULL;
	D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	m_pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &m_pVertexShader);

	ID3DBlob *pCompilePS = NULL;
	D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	m_pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &m_pPixelShader);

	// 頂点レイアウト
		//構造体VERTEXの内部構成（ここではメンバVの正体が何なのかをDirectXに知らせるための物です）
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	m_pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &m_pVertexLayout);
	pCompileVS->Release();
	pCompilePS->Release();

	// 定数バッファの設定(パラメータ受け渡し用)
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer);

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertex_num;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA InitData_vertex;
	InitData_vertex.pSysMem = vertices;
	m_pDevice->CreateBuffer(&bd_vertex, &InitData_vertex, &m_pVertexBuffer);
	
	// インデックスデータ用バッファの設定
    D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * index_num;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA InitData_index;
	InitData_index.pSysMem = indexes;
	m_pDevice->CreateBuffer(&bd_index, &InitData_index, &m_pIndexBuffer);

	// ラスタライザの設定
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.FillMode = D3D11_FILL_WIREFRAME;
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FrontCounterClockwise = TRUE;
	m_pDevice->CreateRasterizerState(&rdc, &m_pRasterizerState);

	
}

Shpere::~Shpere()
{
	m_pSwapChain->Release();
	m_pDeviceContext->Release();
	m_pDevice->Release();

	m_pBackBuffer_RTV->Release();

	m_pRasterizerState->Release();
	m_pVertexShader->Release();
	m_pVertexLayout->Release();
	m_pPixelShader->Release();
	m_pConstantBuffer->Release();
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();

	delete[] vertices;
	delete[] indexes;
}

void Shpere::ShpereMaker()
{



}
