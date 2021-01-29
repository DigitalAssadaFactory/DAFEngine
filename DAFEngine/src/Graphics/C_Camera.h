#pragma once
#include <DAF_ECS.h>
#include "U_Graphics.h"



namespace DAF
{

	REGISTER_ECSComponent_09(
		Camera,
		DirectX::XMFLOAT3, position,
		DirectX::XMFLOAT3, rotation,
		DirectX::XMMATRIX, viewMatrix,
		DirectX::XMMATRIX, projectionMatrix,
		DirectX::XMMATRIX, rotationMatrix,
		ECS::Utility::Graphics::RTV, renderTargetView,
		ECS::Utility::Graphics::DSV, depthStencilView,
		ECS::Utility::Graphics::VP, viewport,
		Microsoft::WRL::ComPtr<ID3D11Buffer>, mvpConstantBuffer
	)

}