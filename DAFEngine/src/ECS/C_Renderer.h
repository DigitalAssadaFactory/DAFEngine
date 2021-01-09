#pragma once
#include "U_Basic.h"



namespace DAF
{

	REGISTER_ECSComponent_06(
		Renderer,
		std::string, drawMode,
		std::string, vertexShader,
		std::string, pixelShader,
		int, pipelineHandle,
		Microsoft::WRL::ComPtr<ID3D11Buffer>, instanceBuffer,
		std::vector<std::string>, textures
	)

}