#include "Shpere.h"


Shpere::Shpere()
{

}

Shpere::~Shpere()
{
}

void Shpere::ShpereMaker()
{
	
 //��̒��_�����i�[����\����
	struct VERTEX {
		XMVECTOR V;
	};


	// GPU(�V�F�[�_��)�֑��鐔�l���܂Ƃ߂��\����
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




	//���̂Ɋւ���f�[�^��ێ�����ϐ��̐錾
	const int u_max = 30;//�ȉ��Q�s���̂̏c���̕��������w�肷��萔
	const int v_max = 15;
	VERTEX *vertices;    //���̂̒��_�f�[�^��ێ�����ϐ�
	int *indexes;        //���̂̃C���f�b�N�X�f�[�^��ێ�����ϐ�
	int vertex_num = u_max * (v_max + 1);//���_���̌v�Z
	int index_num = 2 * v_max * (u_max + 1);//�C���f�b�N�X���̌v�Z



	//		 //���_���C�A�E�g
	//D3D11_INPUT_ELEMENT_DESC layout[] = {
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	//pDevice->CreateInputLayout(layout, 1, pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &pVertexLayout);
	//pCompileVS->Release();
	//pCompilePS->Release();







	//�������牺��ǉ����ăG���[���o���̂ŏ�̃R�����g�A�E�g������ǉ�

	//// �萔�o�b�t�@�̐ݒ�(�p�����[�^�󂯓n���p)
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;
	//pDevice->CreateBuffer(&cb, NULL, &pConstantBuffer);




	//// ���_�f�[�^�̍쐬
	//vertices = new VERTEX[vertex_num];
	//for (int v = 0; v <= v_max; v++) {
	//	for (int u = 0; u < u_max; u++) {
	//		double theta = XMConvertToRadians(180.0f * v / v_max);
	//		double phi = XMConvertToRadians(360.0f * u / u_max);
	//		double x = sin(theta) * cos(phi);
	//		double y = cos(theta);
	//		double z = sin(theta) * sin(phi);
	//		vertices[u_max * v + u].V = XMVectorSet(x, y, z, 1.0f);
	//	}

	//}

	//// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	//D3D11_BUFFER_DESC bd_vertex;
	//bd_vertex.ByteWidth = sizeof(VERTEX) * vertex_num;
	//bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	//bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd_vertex.CPUAccessFlags = 0;
	//bd_vertex.MiscFlags = 0;
	//bd_vertex.StructureByteStride = 0;
	//D3D11_SUBRESOURCE_DATA InitData_vertex;
	//InitData_vertex.pSysMem = vertices;
	//pDevice->CreateBuffer(&bd_vertex, &InitData_vertex, &pVertexBuffer);

	//// ���̂̃C���f�b�N�X�f�[�^�̍쐬
	//int i = 0;
	//indexes = new int[index_num];
	//for (int v = 0; v < v_max; v++) {
	//	for (int u = 0; u <= u_max; u++) {
	//		if (u == u_max) {
	//			indexes[i++] = v * u_max;
	//			indexes[i++] = (v + 1) * u_max;
	//		}
	//		else {
	//			indexes[i++] = (v * u_max) + u;
	//			indexes[i++] = indexes[i - 1] + u_max;
	//		}
	//	}
	//}

}
