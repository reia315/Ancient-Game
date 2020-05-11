#include "Shpere.h"


Shpere::Shpere()
{

}

Shpere::~Shpere()
{
}

void Shpere::ShpereMaker(ID3D11Device *pDevice, ID3D11Buffer *pVertexBuffer, ID3D11Buffer *pIndexBuffer)
{

	//----------------------------------------------------
	 //一つの頂点情報を格納する構造体
	struct VERTEX {
		XMVECTOR V;
	};


	// GPU(シェーダ側)へ送る数値をまとめた構造体
	struct CONSTANT_BUFFER {
		XMMATRIX mWVP;
	};
	//------------------------------------------------------

	//--------------------------------------------------------------------
//球体に関するデータを保持する変数の宣言
	const int u_max = 30;//以下２行球体の縦横の分割数を指定する定数
	const int v_max = 15;
	VERTEX *vertices;    //球体の頂点データを保持する変数
	int *indexes;        //球体のインデックスデータを保持する変数
	int vertex_num = u_max * (v_max + 1);//頂点数の計算
	int index_num = 2 * v_max * (u_max + 1);//インデックス数の計算
	//---------------------------------------------------------------------


	


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
	pDevice->CreateBuffer(&bd_vertex, &InitData_vertex, &pVertexBuffer);

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
	pDevice->CreateBuffer(&bd_index, &InitData_index, &pIndexBuffer);




}
