#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")//以下二つはメイン関数のある所に一回だけ書けばいい
#pragma comment(lib, "d3dcompiler.lib")
 




 
//頂点データのための構造体を定義している

 //一つの頂点情報を格納する構造体
struct VERTEX {
	XMVECTOR V;
};

//数値を入力して描画する頂点データを作成
// GPU(シェーダ側)へ送る数値をまとめた構造体
struct CONSTANT_BUFFER {
	XMMATRIX mWVP;
};

#define WIN_STYLE WS_OVERLAPPEDWINDOW
int CWIDTH;     // クライアント領域の幅
int CHEIGHT;    // クライアント領域の高さ

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




//球体に関するデータを保持する変数の宣言
const int u_max = 30;//以下２行球体の縦横の分割数を指定する定数
const int v_max = 15;
VERTEX *vertices;    //球体の頂点データを保持する変数
int *indexes;        //球体のインデックスデータを保持する変数
int vertex_num = u_max * (v_max + 1);//頂点数の計算
int index_num = 2 * v_max * (u_max + 1);//インデックス数の計算
 float x = 0;

//LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);



LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	

	switch (uMsg) {
	case WM_CREATE:
	{

		// ----- パイプラインの準備 -----
		RECT csize;
		GetClientRect(hwnd, &csize);
		CWIDTH = csize.right;
		CHEIGHT = csize.bottom;

		//イメージを出力するためのバッファ関数を管理しているところ
		//出力イメージの大きさや品質、描画先ウィンドウの指定など
		//スワップチェインの作成
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

		//描画先の作成
		ID3D11Texture2D *pbbTex;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbbTex);
		pDevice->CreateRenderTargetView(pbbTex, NULL, &pBackBuffer_RTV);
		pbbTex->Release();

		// ビューポートの設定
		D3D11_VIEWPORT vp;
		vp.Width = CWIDTH;
		vp.Height = CHEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 2;
		vp.TopLeftY = 0;
		
		
		// シェーダの設定---------------------------------------------------------------------------------------------------------
		//ID3DBlob *pCompileVS = NULL;
		//ID3DBlob *pCompilePS = NULL;
		//D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
		//pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &pVertexShader);
		//D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
		//pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &pPixelShader);
		////
		//// 頂点レイアウト
		////構造体VERTEXの内部構成（ここではメンバVの正体が何なのかをDirectXに知らせるための物です）
		//D3D11_INPUT_ELEMENT_DESC layout[] = {
		//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//};
		//pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
		//pCompileVS->Release();
		//pCompilePS->Release();


		//
		//// 定数バッファの設定(パラメータ受け渡し用)
		//D3D11_BUFFER_DESC cb;
		//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
		//cb.Usage = D3D11_USAGE_DYNAMIC;
		//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//cb.MiscFlags = 0;
		//cb.StructureByteStride = 0;
		//pDevice->CreateBuffer(&cb, NULL, &pConstantBuffer);

	   //----------------------------------------------------------------------------------------------------------------------------------

		// 頂点データの作成
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
		// 頂点データ用バッファの設定
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
		
		// 球体のインデックスデータの作成
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
		// インデックスデータ用バッファの設定
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


		//// ラスタライザの設定
		//D3D11_RASTERIZER_DESC rdc = {};
		//rdc.FillMode = D3D11_FILL_WIREFRAME;
		//rdc.CullMode = D3D11_CULL_NONE;
		//rdc.FrontCounterClockwise = TRUE;
		//pDevice->CreateRasterizerState(&rdc, &pRasterizerState);

		//------------------------------------------------------------

		// ----- パイプラインの構築 -----
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

	// ウィンドウクラスを登録する
	WNDCLASS wc = {};
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = ClassName;
	RegisterClass(&wc);
	

	// ウィンドウの作成
	WHandle = CreateWindow(ClassName, "球体の描画", WIN_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 800, NULL, NULL, hInstance, NULL);
	if (WHandle == NULL) return 0;
	ShowWindow(WHandle, nCmdShow);
	
	// メッセージループの実行
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ----- DXの処理 -----
			float clearColor[4] = { 0.5, 0.5, 0.5, 1 };
			pDeviceContext->ClearRenderTargetView(pBackBuffer_RTV, clearColor);


			// パラメータの計算
			XMVECTOR eye_pos = XMVectorSet(0.0f, 1.0f, -3.5f, 1.0f);
			XMVECTOR eye_lookat = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
			XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
			XMMATRIX World = XMMatrixRotationY(x += 0.0);//回転速度
			XMMATRIX View = XMMatrixLookAtLH(eye_pos, eye_lookat, eye_up);
			XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)CWIDTH / (FLOAT)CHEIGHT, 0.1f, 110.0f);

		
			// パラメータの受け渡し
			D3D11_MAPPED_SUBRESOURCE pdata;
			CONSTANT_BUFFER cb;
			cb.mWVP = XMMatrixTranspose(World * View * Proj);
			pDeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);
			memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));
			pDeviceContext->Unmap(pConstantBuffer, 0);
	
			// 描画実行
			pDeviceContext->DrawIndexed(index_num, 0, 0);
			pSwapChain->Present(0, 0);
		}
	}

	return 0;
}


