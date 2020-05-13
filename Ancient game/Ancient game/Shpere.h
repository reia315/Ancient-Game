#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;


class Shpere
{
public:

	explicit Shpere(ID3D11Device* device, ID3D11DeviceContext* deviceContext );

	~Shpere();

	void  ShpereMaker();
	

private:
	IDXGISwapChain *m_pSwapChain;
	ID3D11Device *m_pDevice{nullptr};
	ID3D11DeviceContext *m_pDeviceContext{nullptr};
	ID3D11DeviceContext *m_pDeviceContext{nullptr};

	ID3D11RenderTargetView *m_pBackBuffer_RTV{nullptr};

	ID3D11RasterizerState *m_pRasterizerState{nullptr};
	ID3D11VertexShader *m_pVertexShader{nullptr};
	ID3D11InputLayout *m_pVertexLayout{nullptr};
	ID3D11PixelShader *m_pPixelShader{nullptr};
	ID3D11Buffer *m_pConstantBuffer{nullptr};
	ID3D11Buffer *m_pVertexBuffer{nullptr};
	ID3D11Buffer *m_pIndexBuffer{nullptr};


	//頂点データのための構造体を定義している
//----------------------------------------------------
 //一つの頂点情報を格納する構造体
	struct VERTEX {
		XMVECTOR V;
	};

	//数値を入力して描画する頂点データを作成
	// GPU(シェーダ側)へ送る数値をまとめた構造体
	struct CONSTANT_BUFFER {
		XMMATRIX mWVP;
	};
	//------------------------------------------------------

	const int u_max = 30;//以下２行球体の縦横の分割数を指定する定数
	const int v_max = 15;
	VERTEX *vertices;    //球体の頂点データを保持する変数
	int *indexes;        //球体のインデックスデータを保持する変数
	int vertex_num = u_max * (v_max + 1);//頂点数の計算
	int index_num = 2 * v_max * (u_max + 1);//インデックス数の計算
};