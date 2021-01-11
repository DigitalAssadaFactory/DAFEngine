#include "C_Light.h"


namespace DAF
{

	INIT_ECSComponent_05(
		Light,
		DirectX::XMFLOAT3, position,
		DirectX::XMFLOAT3, direction,
		DirectX::XMFLOAT3, color,
		float, intensity,
		LightType, type
	)

}