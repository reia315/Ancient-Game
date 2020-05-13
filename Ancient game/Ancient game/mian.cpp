#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")//�ȉ���̓��C���֐��̂��鏊�Ɉ�񂾂������΂���
#pragma comment(lib, "d3dcompiler.lib")
 




 
//���_�f�[�^�̂��߂̍\���̂��`���Ă���

 //��̒��_�����i�[����\����
struct VERTEX {
	XMVECTOR V;
};

//���l����͂��ĕ`�悷�钸�_�f�[�^���쐬
// GPU(�V�F�[�_��)�֑��鐔�l���܂Ƃ߂��\����
struct CONSTANT_BUFFER {
	XMMATRIX mWVP;
};

#define WIN_STYLE WS_OVERLAPPEDWINDOW
int CWIDTH;     // �N���C�A���g�̈�̕�
int CHEIGHT;    // �N���C�A���g�̈�̍���

HWND WHandle;
const char *ClassName = "Temp_Window";

IDXGISwapChain *pSwapChain;
ID3D11Device *pDevice;
ID3D11DeviceContext *pDeviceContext;
   
ID3D11RenderTargetView *pBackBuffer_RTV;

ID3D11RasterizerState *pRasterizerState;
ID3D11VertexShader *pVertexShader;
ID3D11InputLayout *pVertexLayout;
ID3D11PixelShader *pPixelShader;
ID3D11Buffer *pConstantBuffer;
ID3D11Buffer *pVertexBuffer;
ID3D11Buffer *pIndexBuffer;




//���̂Ɋւ���f�[�^��ێ�����ϐ��̐錾
const int u_max = 30;//�ȉ��Q�s���̂̏c���̕��������w�肷��萔
const int v_max = 15;
VERTEX *vertices;    //���̂̒��_�f�[�^��ێ�����ϐ�
int *indexes;        //���̂̃C���f�b�N�X�f�[�^��ێ�����ϐ�
int vertex_num = u_max * (v_max + 1);//���_���̌v�Z
int index_num = 2 * v_max * (u_max + 1);//�C���f�b�N�X���̌v�Z
 float x = 0;

//LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);



LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	

	switch (uMsg) {
	case WM_CREATE:
	{

		// ----- �p�C�v���C���̏��� -----
		RECT csize;
		GetClientRect(hwnd, &csize);
		CWIDTH = csize.right;
		CHEIGHT = csize.bottom;

		//�C���[�W���o�͂��邽�߂̃o�b�t�@�֐����Ǘ����Ă���Ƃ���
		//�o�̓C���[�W�̑傫����i���A�`���E�B���h�E�̎w��Ȃ�
		//�X���b�v�`�F�C���̍쐬
		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.BufferCount = 1;
		scd.BufferDesc.Width = CWIDTH;
		scd.BufferDesc.Height = CHEIGHT;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 6;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = hwnd;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = TRUE;
		D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &fl, 1, D3D11_SDK_VERSION, &scd, &pSwapChain, &pDevice, NULL, &pDeviceContext);

		//�`���̍쐬
		ID3D11Texture2D *pbbTex;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbbTex);
		pDevice->CreateRenderTargetView(pbbTex, NULL, &pBackBuffer_RTV);
		pbbTex->Release();

		// �r���[�|�[�g�̐ݒ�
		D3D11_VIEWPORT vp;
		vp.Width = CWIDTH;
		vp.Height = CHEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 2;
		vp.TopLeftY = 0;
		
		
		// �V�F�[�_�̐ݒ�---------------------------------------------------------------------------------------------------------
		//ID3DBlob *pCompileVS = NULL;
		//ID3DBlob *pCompilePS = NULL;
		//D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		//pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
		//D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		//pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
		////
		//// ���_���C�A�E�g
		////�\����VERTEX�̓����\���i�����ł̓����oV�̐��̂����Ȃ̂���DirectX�ɒm�点�邽�߂̕��ł��j
		//D3D11_INPUT_ELEMENT_DESC layout[] = {
		//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//};
		//pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
		//pCompileVS->Release();
		//pCompilePS->Release();


		//
		//// �萔�o�b�t�@�̐ݒ�(�p�����[�^�󂯓n���p)
		//D3D11_BUFFER_DESC cb;
		//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		//cb.Usage = D3D11_USAGE_DYNAMIC;
		//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//cb.MiscFlags = 0;
		//cb.StructureByteStride = 0;
		//pDevice->CreateBuffer(&cb, NULL, &pConstantBuffer);

	   //----------------------------------------------------------------------------------------------------------------------------------

		// ���_�f�[�^�̍쐬
		vertices = new VERTEX[vertex_num];
		for (int v = 0; v <= v_max; v++) {
			for (int u = 0; u < u_max; u++) {
				double theta = XMConvertToRadians(180.0f * v / v_max);
				double phi = XMConvertToRadians(360.0f * u / u_max);
				double x = sin(theta) * cos(phi);
				double y = cos(theta);
				double z = sin(theta) * sin(phi);
				vertices[u_max * v + u].V = XMVectorSet(x, y, z, 1.0f);
			}
			
		}

		//-----------------------------------------------------------------------------------
		// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	/*	D3D11_BUFFER_DESC bd_vertex;
		bd_vertex.ByteWidth = sizeof(VERTEX) * vertex_num;
		bd_vertex.Usage = D3D11_USAGE_DEFAULT;
		bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_vertex.CPUAccessFlags = 0;
		bd_vertex.MiscFlags = 0;
		bd_vertex.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA InitData_vertex;
		InitData_vertex.pSysMem = vertices;
		pDevice->CreateBuffer(&bd_vertex, &InitData_vertex, &pVertexBuffer);*/
		//------------------------------------------------------------------------------------
		
		// ���̂̃C���f�b�N�X�f�[�^�̍쐬
		int i = 0;
		indexes = new int[index_num];
		for (int v = 0; v < v_max; v++) {
			for (int u = 0; u <= u_max; u++) {
				if (u == u_max) {
					indexes[i++] = v * u_max;
					indexes[i++] = (v + 1) * u_max;
				}
				else {
					indexes[i++] = (v * u_max) + u;
					indexes[i++] = indexes[i - 1] + u_max;
				}
			}
		}
	//---------------------------------------------------------------
		// �C���f�b�N�X�f�[�^�p�o�b�t�@�̐ݒ�
		//D3D11_BUFFER_DESC bd_index;
		//bd_index.ByteWidth = sizeof(int) * index_num;
		//bd_index.Usage = D3D11_USAGE_DEFAULT;
		//bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//bd_index.CPUAccessFlags = 0;
		//bd_index.MiscFlags = 0;
		//bd_index.StructureByteStride = 0;
		//D3D11_SUBRESOURCE_DATA InitData_index;
		//InitData_index.pSysMem = indexes;
		//pDevice->CreateBuffer(&bd_index, &InitData_index, &pIndexBuffer);


		//// ���X�^���C�U�̐ݒ�
		//D3D11_RASTERIZER_DESC rdc = {};
		//rdc.FillMode = D3D11_FILL_WIREFRAME;
		//rdc.CullMode = D3D11_CULL_NONE;
		//rdc.FrontCounterClockwise = TRUE;
		//pDevice->CreateRasterizerState(&rdc, &pRasterizerState);

		//------------------------------------------------------------

		// ----- �p�C�v���C���̍\�z -----
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
		pDeviceContext->IASetInputLayout(pVertexLayout);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		pDeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		pDeviceContext->VSSetShader(pVertexShader, NULL, 0);
		pDeviceContext->PSSetShader(pPixelShader, NULL, 0);
		pDeviceContext->RSSetState(pRasterizerState);
		pDeviceContext->OMSetRenderTargets(1, &pBackBuffer_RTV, NULL);
		pDeviceContext->RSSetViewports(1, &vp);

		return 0;
	}
	case WM_DESTROY:
		//------------------------------------------------
		/*pSwapChain->Release();
		pDeviceContext->Release();
		pDevice->Release();

		pBackBuffer_RTV->Release();

		pRasterizerState->Release();
		pVertexShader->Release();
		pVertexLayout->Release();
		pPixelShader->Release();
		pConstantBuffer->Release();
		pVertexBuffer->Release();
		pIndexBuffer->Release();

		delete[] vertices;
		delete[] indexes;*/
		//-------------------------------------------------
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow) 
{

	// �E�B���h�E�N���X��o�^����
	WNDCLASS wc = {};
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = ClassName;
	RegisterClass(&wc);
	

	// �E�B���h�E�̍쐬
	WHandle = CreateWindow(ClassName, "���̂̕`��", WIN_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 800, NULL, NULL, hInstance, NULL);
	if (WHandle == NULL) return 0;
	ShowWindow(WHandle, nCmdShow);
	
	// ���b�Z�[�W���[�v�̎��s
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ----- DX�̏��� -----
			float clearColor[4] = { 0.5, 0.5, 0.5, 1 };
			pDeviceContext->ClearRenderTargetView(pBackBuffer_RTV, clearColor);


			// �p�����[�^�̌v�Z
			XMVECTOR eye_pos = XMVectorSet(0.0f, 1.0f, -3.5f, 1.0f);
			XMVECTOR eye_lookat = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
			XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
			XMMATRIX World = XMMatrixRotationY(x += 0.0);//��]���x
			XMMATRIX View = XMMatrixLookAtLH(eye_pos, eye_lookat, eye_up);
			XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)CWIDTH / (FLOAT)CHEIGHT, 0.1f, 110.0f);

		
			// �p�����[�^�̎󂯓n��
			D3D11_MAPPED_SUBRESOURCE pdata;
			CONSTANT_BUFFER cb;
			cb.mWVP = XMMatrixTranspose(World * View * Proj);
			pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
			pDeviceContext->Unmap(pConstantBuffer, 0);
	
			// �`����s
			pDeviceContext->DrawIndexed(index_num, 0, 0);
			pSwapChain->Present(0, 0);
		}
	}

	return 0;
}


