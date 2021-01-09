#include "U_Graphics.h"



namespace DAF
{

	namespace ECS::Utility::Graphics {

		size_t                                   Defaults::FULL_SCREEN_WIDTH(GetSystemMetrics(SM_CXFULLSCREEN));
		size_t                                   Defaults::FULL_SCREEN_HEIGHT(GetSystemMetrics(SM_CYFULLSCREEN));
		std::vector<D3D11_INPUT_ELEMENT_DESC>    Defaults::InputLayoutDesc = {
					{ "POSITION",   0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,   0,  D3D11_INPUT_PER_VERTEX_DATA,  0 },
					{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,        0,  16,  D3D11_INPUT_PER_VERTEX_DATA,  0 },
					{ "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  24,  D3D11_INPUT_PER_VERTEX_DATA,  0 },
					{ "NORMAL",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  40,  D3D11_INPUT_PER_VERTEX_DATA,  0 } };
	}

}