#include "Shpere.h"


Shpere::Shpere()
{

}

Shpere::~Shpere()
{
}

void Shpere::ShpereMaker()
{
	
 //一つの頂点情報を格納する構造体
	struct VERTEX {
		XMVECTOR V;
	};


	// GPU(シェーダ側)へ送る数値をまとめた構造体
	struct CONSTANT_BUFFER {
		XMMATRIX mWVP;
	};



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

}
