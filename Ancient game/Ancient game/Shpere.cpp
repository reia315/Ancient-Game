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

}
