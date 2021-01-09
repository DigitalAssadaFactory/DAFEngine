#pragma once
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
		Utility::Graphics::RTV, renderTargetView,
		Utility::Graphics::DSV, depthStencilView,
		Utility::Graphics::VP, viewport,
		Microsoft::WRL::ComPtr<ID3D11Buffer>, mvpConstantBuffer
	)

}