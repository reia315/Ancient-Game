#include "Shpere.h"

void Shpere::ShpereMake()
{
	struct VERTEX {
		XMVECTOR V;
	};

	//球体に関するデータを保持する変数の宣言
	const int u_max = 30;//以下２行球体の縦横の分割数を指定する定数
	const int v_max = 15;
	VERTEX *vertices;    //球体の頂点データを保持する変数
	int *indexes;        //球体のインデックスデータを保持する変数
	int vertex_num = u_max * (v_max + 1);//頂点数の計算
	int index_num = 2 * v_max * (u_max + 1);//インデックス数の計算
}

void Shpere::ShpereMaker()
{

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

}
