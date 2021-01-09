#pragma once
#include "ECSCore.h"
#include "U_Basic.h"



namespace DAF
{

	REGISTER_ECSComponent_02(
		InputLayout,
		std::string, name,
		std::vector<D3D11_INPUT_ELEMENT_DESC>, description
	)

		REGISTER_ECSComponent_09(
			VertexShader,
			std::string, name,
			std::string, model,
			std::string, path,
			std::string, inputLayout,
			Microsoft::WRL::ComPtr<ID3DBlob>, blob,
			Microsoft::WRL::ComPtr<ID3D11InputLayout>, DX11InputLayout,
			Microsoft::WRL::ComPtr<ID3D11VertexShader>, DX11VertexShader,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ConstantBuffers,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ResourceBuffers
		)

		REGISTER_ECSComponent_07(
			PixelShader,
			std::string, name,
			std::string, model,
			std::string, path,
			Microsoft::WRL::ComPtr<ID3DBlob>, blob,
			Microsoft::WRL::ComPtr<ID3D11PixelShader>, DX11PixelShader,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ConstantBuffers,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ResourceBuffers
		)

		REGISTER_ECSComponent_08(
			ComputeShader,
			std::string, name,
			std::string, model,
			std::string, path,
			Microsoft::WRL::ComPtr<ID3DBlob>, blob,
			Microsoft::WRL::ComPtr <ID3D11ComputeShader>, DX11ComputeShader,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ConstantBuffers,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11ResourceBuffers,
			std::vector < Microsoft::WRL::ComPtr<ID3D11Buffer> >, DX11UnorderedAccessBuffers
		)

}