#include "Shpere.h"

void Shpere::ShpereMake()
{
	struct VERTEX {
		XMVECTOR V;
	};

	//���̂Ɋւ���f�[�^��ێ�����ϐ��̐錾
	const int u_max = 30;//�ȉ��Q�s���̂̏c���̕��������w�肷��萔
	const int v_max = 15;
	VERTEX *vertices;    //���̂̒��_�f�[�^��ێ�����ϐ�
	int *indexes;        //���̂̃C���f�b�N�X�f�[�^��ێ�����ϐ�
	int vertex_num = u_max * (v_max + 1);//���_���̌v�Z
	int index_num = 2 * v_max * (u_max + 1);//�C���f�b�N�X���̌v�Z
}

void Shpere::ShpereMaker()
{

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

}
