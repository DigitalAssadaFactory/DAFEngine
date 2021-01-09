#include "C_Texture2D.h"



namespace DAF
{

	INIT_ECSComponent_09(
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