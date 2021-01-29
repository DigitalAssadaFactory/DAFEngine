#pragma once
#include <DAF_ECS.h>
#include <DAF_Utility.h>


namespace DAF::ECS::Utility::Graphics
{

	struct Defaults {
		struct Vector {
			static constexpr DirectX::XMVECTOR Forward = { 0.0f, 0.0f, 1.0f };
			static constexpr DirectX::XMVECTOR Backward = { 0.0f, 0.0f, -1.0f };
			static constexpr DirectX::XMVECTOR Right = { 1.0f, 0.0f, 0.0f };
			static constexpr DirectX::XMVECTOR Left = { -1.0f, 0.0f, 1.0f };
			static constexpr DirectX::XMVECTOR Up = { 0.0f, 1.0f, 1.0f };
			static constexpr DirectX::XMVECTOR Down = { 0.0f, -1.0f, 1.0f };
		};

		static size_t                                    FULL_SCREEN_WIDTH;
		static size_t                                    FULL_SCREEN_HEIGHT;
		static std::vector<D3D11_INPUT_ELEMENT_DESC>     InputLayoutDesc;
	};



	// NOTE: The values in each utility struct has to match the order of
	//       Implementation::Create... function calls inside related Implementation::Init... function
	enum class VS {
		Default = 0,
		Reflection,
		Refraction,
		Fresnel,
		Ambient
	};
	enum class PS {
		Default = 0,
		Reflection,
		Refraction,
		Fresnel,
		Ambient
	};
	enum class GS {
		Default = 0
	};
	enum class DS {
		Default = 0
	};
	enum class HS {
		Default = 0
	};
	enum class VP {
		Default = 0
	};
	enum class RTV {
		BackBuffer = 0
	};
	enum class DSV {
		Default = 0
	};
	enum class RS {
		CW = 0,
		CCW = 1
	};
	enum class DSS {
		Default = 0
	};
	enum class BS {
		Default = 0
	};
	enum class SS {
		Default = 0
	};
	enum class CB {
		Default = 0
	};

	// DM stands for DrawMode and defines context states and buffer count (single or multi)
	// Single means to merge all models with same shader pipeline into 1 buffer and draw them with a single draw call
	enum class DM {
		_Count = 6,
		_CountSingle = 3,
		_CountMulti = 3,

		SingleSolid = 0,
		SingleTransparent = 1,
		SingleWireframe = 2,
		MultiSolid = 3,
		MultiTransparent = 4,
		MultiWireframe = 5
	};

	enum class Fill {
		Solid = D3D11_FILL_SOLID,
		Wireframe = D3D11_FILL_WIREFRAME
	};
	enum class Cull {
		Back = D3D11_CULL_BACK,
		Front = D3D11_CULL_FRONT,
		None = D3D11_CULL_NONE
	};
	enum class Usage {
		Default = D3D11_USAGE_DEFAULT,
		Dynamic = D3D11_USAGE_DYNAMIC,
		Immutable = D3D11_USAGE_IMMUTABLE,
		Staging = D3D11_USAGE_STAGING
	};
	enum class Access {
		Write = D3D11_CPU_ACCESS_WRITE,
		Read = D3D11_CPU_ACCESS_READ
	};
	enum class Blend {
		Zero = D3D11_BLEND_ZERO,
		One = D3D11_BLEND_ONE,
		SrcColor = D3D11_BLEND_SRC_COLOR,
		InvSrcColor = D3D11_BLEND_INV_SRC_COLOR,
		SrcAlpha = D3D11_BLEND_SRC_ALPHA,
		InvSrcAlpha = D3D11_BLEND_INV_SRC_ALPHA,
		DestAlpha = D3D11_BLEND_DEST_ALPHA,
		InvDestAlpha = D3D11_BLEND_INV_DEST_ALPHA,
		DestColor = D3D11_BLEND_DEST_COLOR,
		InvDestColor = D3D11_BLEND_INV_DEST_COLOR,
		SrcAlphaSAT = D3D11_BLEND_SRC_ALPHA_SAT,
		BlenFactor = D3D11_BLEND_BLEND_FACTOR,
		InvBlendFactor = D3D11_BLEND_INV_BLEND_FACTOR,
		Src1Color = D3D11_BLEND_SRC1_COLOR,
		InvSrc1Color = D3D11_BLEND_INV_SRC1_COLOR,
		Src1Alpha = D3D11_BLEND_SRC1_ALPHA,
		InvSrc1Alpha = D3D11_BLEND_INV_SRC1_ALPHA
	};
	enum class BlendOp {
		Add = D3D11_BLEND_OP_ADD,
		Sub = D3D11_BLEND_OP_SUBTRACT,
		RevSub = D3D11_BLEND_OP_REV_SUBTRACT,
		Min = D3D11_BLEND_OP_MIN,
		Max = D3D11_BLEND_OP_MAX
	};
	enum class ColorWriteMask {
		EnableAll = D3D11_COLOR_WRITE_ENABLE_ALL,
		EnableAlpha = D3D11_COLOR_WRITE_ENABLE_ALPHA,
		EnableRed = D3D11_COLOR_WRITE_ENABLE_RED,
		EnableGreen = D3D11_COLOR_WRITE_ENABLE_GREEN,
		EnableBlue = D3D11_COLOR_WRITE_ENABLE_BLUE
	};
	enum class DepthWriteMask {
		All = D3D11_DEPTH_WRITE_MASK_ALL,
		None = D3D11_DEPTH_WRITE_MASK_ZERO
	};
	enum class Comparison {
		Never = D3D11_COMPARISON_NEVER,
		Less = D3D11_COMPARISON_LESS,
		Equal = D3D11_COMPARISON_EQUAL,
		LessEqual = D3D11_COMPARISON_LESS_EQUAL,
		Greater = D3D11_COMPARISON_GREATER,
		NotEqual = D3D11_COMPARISON_NOT_EQUAL,
		GreaterEqual = D3D11_COMPARISON_GREATER_EQUAL,
		Always = D3D11_COMPARISON_ALWAYS,
	};
	enum class Topology {
		TriangleList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		TriangleListAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
		TriangleStrip = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		TriangleStripAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
		LineList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		LineListAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
		LineStrip = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		LineStripAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
		PointList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		Undefined = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED
	};

}