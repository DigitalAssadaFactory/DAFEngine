#pragma once
#include <DirectXMath.h>



namespace DAF::Geometry
{

	struct SingleMatrixBuffer {
		SingleMatrixBuffer(DirectX::XMMATRIX matrix) : m0(matrix) {}
		DirectX::XMMATRIX m0;
	};

}