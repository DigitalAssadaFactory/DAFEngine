#pragma once
#include "../Engine.h"
#include "../ECS.h"
#include "U_Graphics.h"
#include "../Utility.h"
#include "C_Mesh.h"
#include "C_Renderer.h"
#include "C_Texture2D.h"
#include "C_Shader.h"
#include "C_Camera.h"
#include "C_Transform.h"
#include "C_Light.h"
#include "../Utility/DYNAMIC_ARRAY_MACRO.h"
#include "../Geometry.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <DirectXTK/WICTextureLoader.h>
#include <DirectXTK/DDSTextureLoader.h>
#include <map>



using namespace DAF::ECS::Utility::Graphics;
namespace DAF::ECS::System
{

	struct Graphics {
		static void Init(const HWND& windowHandle);
		static void Update();
		static void Exit();

		/*static void Dispatch(
			const std::string& currencyPair,
			const std::vector<float>& ask,
			const std::vector<float>& bid,
			const std::vector<float>& open,
			const std::vector<float>& close,
			const std::vector<float>& high,
			const std::vector<float>& low,
			const std::vector<int>& year,
			const std::vector<int>& mon,
			const std::vector<int>& day,
			const std::vector<int>& hour,
			const std::vector<int>& min,
			const std::vector<int>& sec,
			const std::vector<int>& dow,
			const std::vector<int>& barID
		);*/

		static void AddModel(const Entity& e);
		static void AddModel(const Entity& e, const std::vector<Geometry::Vertex>& vertices,
			const std::vector<unsigned int>& indices, const int& at = 0);
		static void AddTexture(const std::filesystem::path& path, const void* data = nullptr,
			const int& width = 0, const int& height = 0, const DXGI_FORMAT& format = DXGI_FORMAT_UNKNOWN, aiTextureType type = aiTextureType_UNKNOWN,
			const std::string& storageType = "Disc");
		template<typename T>
		static void AddTexture(const std::string& name, const void* data, const int& width = 0, const int& height = 0, const DXGI_FORMAT& format = DXGI_FORMAT_UNKNOWN);
		static void AddCamera(const Entity& e);
		static void AddLight(const Entity& e);

		static void LoadMesh(Entity& e, const std::string& filePath);
		static void LoadTexture(const std::filesystem::path& filePath, Microsoft::WRL::ComPtr<ID3D11Texture2D>& dest);
		static void ExtractTextures(const std::filesystem::path& filePath);

		static size_t GetWidth();
		static size_t GetHeight();

		//static size_t Calculate_All_Vertices();

	private:
		static void InitHard();
		static void InitSoft();
		static void InitShaders();
		static void InitViews();
		static void InitStates();
		static void InitBuffers();

		inline static void Clear();
		inline static void ClearRTV(const size_t rtv, const DirectX::XMFLOAT3& rgb = { 0.0f,0.0f,0.2f });
		inline static void ClearDSV(const size_t dsv, const UINT& clearFlags,
			const FLOAT& depth = 1.0f, const UINT8& stencil = 0);
		inline static void Prepare();
		//inline static void PrepareModels();
		inline static void PrepareCameras();
		inline static void Draw();
		inline static void DrawTransparent();
		inline static void DrawSolid();
		inline static void Present();

		//----------------------   SHADERS   ----------------------//

		static void CreateInputLayout(const std::string& inputLayoutName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& description);
		static void CompileVS(const std::string& vsFileName, const std::string& path = "", const std::string& vsModel = "vs_5_0",
			const std::string& inputLayoutName = "default", const std::string& entryPoint = "main");
		static void CompilePS(const std::string& psFileName, const std::string& path = "",
			const std::string& psModel = "ps_5_0", const std::string& entryPoint = "main");
		static void CompileCS(const std::string& csFileName, const std::string& path = "",
			const std::string& csModel = "cs_5_0", const std::string& entryPoint = "main");

		static void LoadVS(const std::string& vsFileName, const std::string& path = "",
			const std::string& inputLayoutName = "default");
		static void LoadPS(const std::string& psFileName, const std::string& path = "");
		static void LoadCS(const std::string& csFileName, const std::string& path = "");

		//----------------------   VIEWS   ----------------------//

		static void CreateViewport(const float& width = m_width,
			const float& height = m_height, const float& topLeftX = 0.0f,
			const float& topLeftY = 0.0f, const float& minDepth = 0.0f, const float& maxDepth = 1.0f);
		static void CreateRenderTargetView();
		static void CreateDepthStencilView(const size_t& width = m_width,
			const size_t& height = m_height);
		static void CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer);
		static void CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& dest);
		static void CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& dest);
		static void CreateUAV(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer);

		//----------------------   STATES   ----------------------//

		static void CreateRasterizerState(const D3D11_RASTERIZER_DESC& desc);
		static void CreateRasterizerState(const bool isClockwise = 1, const Fill fillMode = Fill::Solid,
			const Cull cullMode = Cull::Back);
		static void CreateDepthStencilState(const bool depthEnable = 1,
			const DepthWriteMask mask = DepthWriteMask::All,
			const Comparison depthFunc = Comparison::LessEqual, const bool stencilEnable = 0);
		static void CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc);
		static void CreateBlendState(const bool blendEnable = 1, const Blend srcBlend = Blend::One,
			const Blend destBlend = Blend::Zero, const BlendOp blendOp = BlendOp::Add,
			const Blend srcBlendAlpha = Blend::One, const Blend destBlendAlpha = Blend::Zero,
			const BlendOp blendOpAlpha = BlendOp::Add,
			const ColorWriteMask mask = ColorWriteMask::EnableAll);
		static void CreateBlendState(const D3D11_RENDER_TARGET_BLEND_DESC& desc);
		static void CreateBlendState(const std::vector<D3D11_RENDER_TARGET_BLEND_DESC>& desc);
		static void CreateSamplerState();

		//----------------------   BUFFERS   ----------------------//

		template<typename T>
		static void CreateStagingBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest);
		template<typename T>
		static void CreateResourceBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest);
		template<typename T>
		static void CreateUnorderedBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest);
		template<typename T>
		static void CreateConstantBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest,
			const size_t& usage = Usage::Dynamic, const size_t& accessFlag = Access::Write);
		template<typename T>
		static void CreateConstantBuffer(const T& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest,
			const Usage usage = Usage::Dynamic, const Access accessFlag = Access::Write);
		template<typename T>
		static void CreateVertexBuffer(const std::vector<T>& vertices, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest,
			const Usage usage = Usage::Default);
		static void CreateIndexBuffer(const std::vector<unsigned int> indices,
			Microsoft::WRL::ComPtr<ID3D11Buffer>& dest, const Usage usage = Usage::Default);

		//----------------------   RESOURCES   ----------------------//

		template<typename T>
		static void CreateTexture(const void* data, const int& width, const int& height,
			Microsoft::WRL::ComPtr<ID3D11Texture2D>& dest, const DXGI_FORMAT& format = DXGI_FORMAT_R8G8B8A8_UINT);


		//----------------------   Setters   ----------------------//

		inline static void SetRenderTargets(const RTV renderTargetView = RTV::BackBuffer,
			const DSV depthStencilView = DSV::Default);
		inline static void SetViewports(const VP viewport = VP::Default);
		inline static void SetRasterizerState(const RS rasterizerState = RS::CW);
		inline static void SetBlendState(const BS blendState = BS::Default);
		inline static void SetDepthStencilState(const DSS depthStencilState = DSS::Default);
		inline static void SetStates(const RS rasterizerState, const BS blendState);
		inline static void SetSamplerVS(const SS samplerState = SS::Default);
		inline static void SetSamplerPS(const SS samplerState = SS::Default);
		template<typename T>
		static void UpdateConstantBuffer(T& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
			const size_t& mapType = D3D11_MAP_WRITE_DISCARD);
		inline static void SetVertexShader(const VS vertexShader = VS::Default);
		inline static void SetPixelShader(const PS pixelShader = PS::Default);
		inline static void SetShaders(const VS vertexShader, const PS pixelShader);
		inline static void SetTopology(const Topology topology);

		static void ASSIMP_LoadMeshRec(Entity& e, aiNode* pNode, const aiScene* pScene, const DirectX::XMMATRIX& transform);
		static void ASSIMP_LoadMeshRec(Entity& e, aiNode* pNode, const aiScene* pScene,
			const DirectX::XMFLOAT3& offset, const DirectX::XMFLOAT3& rotation);
		static int ASSIMP_ExtractTextures(const std::filesystem::path& filePath, aiMaterial* pMaterial, const aiScene* pScene,
			aiTextureType texType = aiTextureType_DIFFUSE);
		//static std::string ASSIMP_GetTextureStorageType()

		static HRESULT   hr;
		static HWND      m_hWnd;
		static size_t    m_width;
		static size_t    m_height;
		static bool      m_vSync;

		// main infrastructure
		static Microsoft::WRL::ComPtr<IDXGIFactory>          m_pFactory;
		static Microsoft::WRL::ComPtr<IDXGIAdapter>          m_pAdapter;
		static Microsoft::WRL::ComPtr<IDXGIOutput>           m_pOutput;
		static Microsoft::WRL::ComPtr<IDXGISwapChain>        m_pSwapChain;
		static Microsoft::WRL::ComPtr<ID3D11Device>          m_pDevice;
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>   m_pContext;

		// states and views
		static std::vector<D3D11_VIEWPORT>                                     m_VP_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>>     m_RTV_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11DepthStencilView>>     m_DSV_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>   m_SRV_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>>  m_UAV_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11RasterizerState>>      m_RS_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11DepthStencilState>>    m_DSS_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11BlendState>>           m_BS_array;
		static std::vector<Microsoft::WRL::ComPtr<ID3D11SamplerState>>         m_SS_array;

		// buffers
		static std::vector<
			std::vector< Microsoft::WRL::ComPtr<ID3D11Buffer>>>           m_CB_array;
		static std::vector<std::string>                                   m_CB_datatype_array;

		struct DrawData {
			Microsoft::WRL::ComPtr<ID3D11Buffer>                          vertexBuffer;
			unsigned int                                                  vertexStride;
			Microsoft::WRL::ComPtr<ID3D11Buffer>                          indexBuffer;
			unsigned int                                                  indexCount;
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>              instanceBufferView;
			unsigned int                                                  instanceCount;
			std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> psResources;
		};

		static std::map<int, std::vector<DrawData>> m_DrawCache;

		static std::vector<size_t>           m_activeCameras;

		static Entity* core;
		static std::string UniqueName(const std::string& name);
	};





	template<typename T>
	void Graphics::CreateStagingBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_STAGING;
		desc.ByteWidth = data.size() * sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.StructureByteStride = sizeof(T);

		hr = m_pDevice->CreateBuffer(&desc, NULL, dest.GetAddressOf());
		LogError(hr, "StagingBuffer creation failed.");
	}

	template<typename T>
	void Graphics::CreateResourceBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.ByteWidth = data.size() * sizeof(T);
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = data.data();

		hr = m_pDevice->CreateBuffer(&desc, &subData, dest.GetAddressOf());
		LogError(hr, "ResourceBuffer creation failed.");
	}

	template<typename T>
	void Graphics::CreateUnorderedBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
		desc.ByteWidth = data.size() * sizeof(T);// +(16 - (sizeof(data) % 16));
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = data.data();

		hr = m_pDevice->CreateBuffer(&desc, &subData, dest.GetAddressOf());
		LogError(hr, "UnorderedBuffer creation failed.");
	}

	template<typename T>
	void Graphics::CreateConstantBuffer(const std::vector<T>& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest,
		const size_t& usage, const size_t& accessFlag) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = data.size() * sizeof(T) + (16 - ((data.size() * sizeof(T)) % 16));
		desc.Usage = D3D11_USAGE(usage);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG(accessFlag);

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = data.data();

		hr = m_pDevice->CreateBuffer(&desc, &subData, dest.GetAddressOf());
		LogError(hr, "ConstantBuffer creation failed.");
	}

	template<typename T>
	void Graphics::CreateConstantBuffer(const T& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& dest,
		const Usage usage, const Access accessFlag) {
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(data) + (16 - (sizeof(data) % 16));
		desc.Usage = D3D11_USAGE(usage);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG(accessFlag);

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = &data;

		hr = m_pDevice->CreateBuffer(&desc, &subData, dest.GetAddressOf());
		LogError(hr, "ConstantBuffer creation failed.");
	}

	template<typename T>
	void Graphics::CreateVertexBuffer(const std::vector<T>& vertices,
		Microsoft::WRL::ComPtr<ID3D11Buffer>& dest, const Usage usage)
	{
		if (vertices.size() == 0)
			Logger::ThrowBox("CreateVertexBuffer funcion failed. The size of vector with Vertices is 0.");

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(T) * vertices.size();
		desc.Usage = D3D11_USAGE(usage);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = vertices.data();

		hr = m_pDevice->CreateBuffer(&desc, &subData, dest.GetAddressOf());
		LogError(hr, "VertexBuffer creation failed.");
	}

	template<typename T>
	void Graphics::UpdateConstantBuffer(T& data, Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
		const size_t& mapType)
	{
		D3D11_BUFFER_DESC bd;
		buffer.Get()->GetDesc(&bd);
		size_t datawidth = sizeof(data) + (16 - (sizeof(data) % 16));

		if (bd.ByteWidth != datawidth)
			Logger::ThrowBox("UpdateConstantBuffer failed. Invalid data type.");

		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		hr = m_pContext->Map(buffer.Get(), 0u, D3D11_MAP(mapType), 0u, &mappedSubresource);
		LogError(hr, "Mapping ConstantBuffer failed.");
		CopyMemory(mappedSubresource.pData, &data, sizeof(data));
		m_pContext->Unmap(buffer.Get(), 0);
	}

	template<typename T>
	void Graphics::CreateTexture(const void* data, const int& width, const int& height,
		Microsoft::WRL::ComPtr<ID3D11Texture2D>& dest, const DXGI_FORMAT& format)
	{
		CD3D11_TEXTURE2D_DESC desc(format, width, height);

		/*D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = w;
		desc.Height = h;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

		static std::vector<DirectX::XMFLOAT4> v =
		{
			{1.0f,0.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f,1.0f}
		};
		*/


		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = data;
		subData.SysMemPitch = width * sizeof(T);

		hr = m_pDevice->CreateTexture2D(&desc, NULL, dest.GetAddressOf());
		LogError(hr, "Texture creation failed.");

		m_pContext->UpdateSubresource(dest.Get(), 0, NULL, data, width * sizeof(T), 0);
	}

	template<typename T>
	void Graphics::AddTexture(const std::string& name, const void* data, const int& width, const int& height, const DXGI_FORMAT& format)
	{
		core->AddComponent<ECS::Component::Texture2D>();
		auto _tex = core->GetComponent<ECS::Component::Texture2D>(-1);
		_tex.name = UniqueName(name);
		_tex.format = format;
		_tex.width = width;
		_tex.height = height;
		_tex.type = "";
		_tex.storageType = "Runtime";

		CreateTexture<T>(data, width, height, _tex.DX11Texture, format);
		CreateSRV(_tex.DX11Texture, _tex.DX11View);
	}

}