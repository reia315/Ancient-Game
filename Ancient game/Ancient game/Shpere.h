#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;


class Shpere
{
public:

	Shpere();

	~Shpere();

	void  ShpereMaker(ID3D11Device *pDevice, ID3D11Buffer *pVertexBuffer, ID3D11Buffer *pIndexBuffer);
	

private:

	int i{ 0 };
};