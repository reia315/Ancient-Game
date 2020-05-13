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


	//���_�f�[�^�̂��߂̍\���̂��`���Ă���
//----------------------------------------------------
 //��̒��_�����i�[����\����
	struct VERTEX {
		XMVECTOR V;
	};

	//���l����͂��ĕ`�悷�钸�_�f�[�^���쐬
	// GPU(�V�F�[�_��)�֑��鐔�l���܂Ƃ߂��\����
	struct CONSTANT_BUFFER {
		XMMATRIX mWVP;
	};
	//------------------------------------------------------

	const int u_max = 30;//�ȉ��Q�s���̂̏c���̕��������w�肷��萔
	const int v_max = 15;
	VERTEX *vertices;    //���̂̒��_�f�[�^��ێ�����ϐ�
	int *indexes;        //���̂̃C���f�b�N�X�f�[�^��ێ�����ϐ�
	int vertex_num = u_max * (v_max + 1);//���_���̌v�Z
	int index_num = 2 * v_max * (u_max + 1);//�C���f�b�N�X���̌v�Z
};