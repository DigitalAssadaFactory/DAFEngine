#pragma once
#include <DAF_ECS.h>
#include <DAF_Utility.h>



namespace DAF
{

	REGISTER_ECSComponent_09(
		Texture2D,
		std::string, name,
		Microsoft::WRL::ComPtr<ID3D11Texture2D>, DX11Texture,
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, DX11View,
		DXGI_FORMAT, format,
		int, width,
		int, height,
		std::string, type,
		std::string, storageType,
		std::vector<std::vector<float>>, data
	)

}