#include "C_Renderer.h"



namespace DAF
{

	INIT_ECSComponent_06(
		Renderer,
		std::string, drawMode,
		std::string, vertexShader,
		std::string, pixelShader,
		int, pipelineHandle,
		Microsoft::WRL::ComPtr<ID3D11Buffer>, instanceBuffer,
		std::vector<std::string>, textures
	)

}