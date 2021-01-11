#pragma once
#include "../ECS.h"
#include "../Utility.h"



namespace DAF
{
	enum class LightType
	{
		Directional = 0,
		Point,
		Spot
	};

	REGISTER_ECSComponent_05(
		Light,
		DirectX::XMFLOAT3, position,
		DirectX::XMFLOAT3, direction,
		DirectX::XMFLOAT3, color,
		float, intensity,
		LightType, type
	)

}