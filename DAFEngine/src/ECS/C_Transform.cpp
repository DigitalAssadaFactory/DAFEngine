#include "C_Transform.h"



namespace DAF
{

	INIT_ECSComponent_09(
		Transform,
		DirectX::XMFLOAT3, position,
		DirectX::XMFLOAT3, rotation,
		DirectX::XMFLOAT3, scale,
		DirectX::XMFLOAT3, up,
		DirectX::XMFLOAT3, down,
		DirectX::XMFLOAT3, forward,
		DirectX::XMFLOAT3, backward,
		DirectX::XMFLOAT3, right,
		DirectX::XMFLOAT3, left
	)

}