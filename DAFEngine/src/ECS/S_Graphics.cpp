#include "S_Graphics.h"



namespace DAF
{
	using namespace ECS;
	using namespace ECSBase;
	using namespace ECS::Component;
	using namespace ECS::Utility::Graphics;
	using namespace Geometry;
	using namespace DirectX;


	// Static definitions
	namespace ECS::System {
#define __COM__ Microsoft::WRL::ComPtr

		Entity* Graphics::core;

		HRESULT      Graphics::hr;
		HWND         Graphics::m_hWnd;
		size_t       Graphics::m_width;
		size_t       Graphics::m_height;
		bool         Graphics::m_vSync(false);

		__COM__<IDXGIFactory>                             Graphics::m_pFactory;
		__COM__<IDXGIAdapter>                             Graphics::m_pAdapter;
		__COM__<IDXGIOutput>                              Graphics::m_pOutput;
		__COM__<IDXGISwapChain>                           Graphics::m_pSwapChain;
		__COM__<ID3D11Device>                             Graphics::m_pDevice;
		__COM__<ID3D11DeviceContext>                      Graphics::m_pContext;

		std::vector<D3D11_VIEWPORT>                       Graphics::m_VP_array;
		std::vector<__COM__<ID3D11RenderTargetView>>      Graphics::m_RTV_array;
		std::vector<__COM__<ID3D11DepthStencilView>>      Graphics::m_DSV_array;
		std::vector<__COM__<ID3D11ShaderResourceView>>    Graphics::m_SRV_array;
		std::vector<__COM__<ID3D11UnorderedAccessView>>   Graphics::m_UAV_array;
		std::vector<__COM__<ID3D11RasterizerState>>       Graphics::m_RS_array;
		std::vector<__COM__<ID3D11DepthStencilState>>     Graphics::m_DSS_array;
		std::vector<__COM__<ID3D11BlendState>>            Graphics::m_BS_array;
		std::vector<__COM__<ID3D11SamplerState>>          Graphics::m_SS_array;

		std::vector<std::vector<__COM__<ID3D11Buffer>>>   Graphics::m_CB_array(6, std::vector<__COM__<ID3D11Buffer>>());
		std::vector<std::string>                          Graphics::m_CB_datatype_array;


		std::map<int, std::vector<Graphics::DrawData>>    Graphics::m_DrawCache;
		std::vector<size_t>                               Graphics::m_activeCameras;
	}


	namespace ECS::System {

		void Graphics::Init(const HWND& windowHandle) {
			m_hWnd = windowHandle;

			core = new Entity();

			// NOTE: The order of Graphics::Create... function calls inside Graphics::Init... function
			//       has to match the values in related utility struct 
			InitHard();
			InitSoft();
			InitShaders();
			InitViews();
			InitStates();
			InitBuffers();
		}

		void Graphics::Update() {
			Clear();
			Prepare();
			Draw();
			Present();
		}

		void Graphics::Exit() {
			delete core;
		}

		/*void Graphics::Dispatch(
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
		)
		{
			int _Total = (int)ask.size();
			Time::Hourglass timer;

			static __COM__<ID3D11Buffer> askBuffer;
			static __COM__<ID3D11Buffer> bidBuffer;
			static __COM__<ID3D11Buffer> openBuffer;
			static __COM__<ID3D11Buffer> closeBuffer;
			static __COM__<ID3D11Buffer> highBuffer;
			static __COM__<ID3D11Buffer> lowBuffer;
			static __COM__<ID3D11Buffer> yearBuffer;
			static __COM__<ID3D11Buffer> monBuffer;
			static __COM__<ID3D11Buffer> dayBuffer;
			static __COM__<ID3D11Buffer> hourBuffer;
			static __COM__<ID3D11Buffer> minBuffer;
			static __COM__<ID3D11Buffer> secBuffer;
			static __COM__<ID3D11Buffer> dowBuffer;
			static __COM__<ID3D11Buffer> candleBuffer;

			static __COM__<ID3D11Buffer> cBuffer;

			struct Params {
				int Total, Digits, TP, SL, Stride, Scale, Offset, Range;
				float Fading, HRatio, ARatio, Huge;
			};

			Params params;
			params.Digits = 5;
			params.TP = 30;
			params.SL = -100;
			params.Total = (int)ask.size();
			params.Fading = 1.5f;
			params.Stride = 0;
			params.Scale = 1;
			params.HRatio = 0.5f + (0 * 0.05f);
			params.ARatio = 1.0f + (0 * 0.2f);
			params.Range = 10 + 0;
			params.Huge = 0.3f + 0 * 0.1f;


			static __COM__<ID3D11Buffer> outBuffer;
			static __COM__<ID3D11Buffer> ampBuffer;
			static __COM__<ID3D11Buffer> resultBuffer;
			static __COM__<ID3D11Buffer> isDoneBuffer;
			{
				CreateConstantBuffer(params, cBuffer);

				CreateResourceBuffer(ask, askBuffer);
				CreateResourceBuffer(bid, bidBuffer);
				CreateResourceBuffer(open, openBuffer);
				CreateResourceBuffer(close, closeBuffer);
				CreateResourceBuffer(high, highBuffer);
				CreateResourceBuffer(low, lowBuffer);
				CreateResourceBuffer(year, yearBuffer);
				CreateResourceBuffer(mon, monBuffer);
				CreateResourceBuffer(day, dayBuffer);
				CreateResourceBuffer(hour, hourBuffer);
				CreateResourceBuffer(min, minBuffer);
				CreateResourceBuffer(sec, secBuffer);
				CreateResourceBuffer(dow, dowBuffer);
				CreateResourceBuffer(barID, candleBuffer);

				CreateSRV(askBuffer);
				CreateSRV(bidBuffer);
				CreateSRV(openBuffer);
				CreateSRV(closeBuffer);
				CreateSRV(highBuffer);
				CreateSRV(lowBuffer);
				CreateSRV(yearBuffer);
				CreateSRV(monBuffer);
				CreateSRV(dayBuffer);
				CreateSRV(hourBuffer);
				CreateSRV(minBuffer);
				CreateSRV(secBuffer);
				CreateSRV(dowBuffer);
				CreateSRV(candleBuffer);

				std::vector<MyOutput> myOutput(_Total, { 0, 0, 0, 0.0f });
				std::vector<float> myAmplitude(_Total, 0.0f);
				CreateUnorderedBuffer(myOutput, outBuffer);
				CreateUAV(outBuffer);
				CreateUnorderedBuffer(myAmplitude, ampBuffer);
				CreateUAV(ampBuffer);
			}

			m_pContext->CSSetConstantBuffers(0, 1, cBuffer.GetAddressOf());
			m_pContext->CSSetShaderResources(0, 14, m_SRV_array[0].GetAddressOf());
			m_pContext->CSSetUnorderedAccessViews(0, 2, m_UAV_array[0].GetAddressOf(), NULL);

			static __COM__<ID3D11Buffer> stagProfitBuffer;
			std::vector<MyOutput> stagProfit(_Total, { 0,0,0,0.0f });
			CreateStagingBuffer(stagProfit, stagProfitBuffer);
			D3D11_MAPPED_SUBRESOURCE mapped;


			//------
			//          std::future<MyResult> wynik;
			//          
			//          m_pContext->CSSetShader(m_CS_array[0].Get(), 0, 0);
			//          m_pContext->Dispatch(65000, 4, 1);
			//          
			//          m_pContext->CSSetShader(m_CS_array[1].Get(), 0, 0);
			//          m_pContext->Dispatch(65000, 4, 1);
			//          
			//          m_pContext->CSSetShader(m_CS_array[2].Get(), 0, 0);
			//          m_pContext->Dispatch(65000, 4, 1);
			//          
			//          m_pContext->CopyResource(stagProfitBuffer.Get(), outBuffer.Get());
			//          m_pContext->Map(stagProfitBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
			//          MyOutput* o = (MyOutput*)(mapped.pData);
			//          
			//          wynik = std::async(std::launch::async, Stock::DoHomework, std::vector<MyOutput>(o, o + _Total));
			//          
			//          m_pContext->Unmap(stagProfitBuffer.Get(), 0);
			//          
			//          std::string swynik = std::to_string(wynik.get().totalProfit);
			//          
			//          Logger::ThrowBox(swynik);
			//------------






			int dim1 = 11; int dim2 = 21; int dim3 = 21; int dim4 = 7;
			//int dim1 = 3; int dim2 = 1; int dim3 = 1; int dim4 = 1;

			Params newParams;
			newParams.Digits = 5;
			newParams.TP = 30;
			newParams.SL = -100;
			newParams.Total = _Total;
			newParams.Scale = 1;
			newParams.HRatio = 0.6f;

			timer.Start();
			for (int _TP = 1; _TP < dim1; ++_TP)
			{
				DYNAMIC_ARRAY_04(std::future<MyResult>) finalResult;

				finalResult.resize(1);

				for (auto& _2d : finalResult)
					_2d.resize(dim2);

				for (auto& _2d : finalResult)
					for (auto& _3d : _2d)
						_3d.resize(dim3);

				for (auto& _2d : finalResult)
					for (auto& _3d : _2d)
						for (auto& _4d : _3d)
							_4d.resize(dim4);

				for (int _ARatio = 0; _ARatio < dim2; ++_ARatio)
					for (int _Range = 0; _Range < dim3; ++_Range)
						for (int _Huge = 0; _Huge < dim4; ++_Huge)
						{
							newParams.TP = _TP;
							newParams.ARatio = 0.5f + (_ARatio * 0.1f);
							newParams.Range = 10 + _Range;
							newParams.Huge = 0.3f + _Huge * 0.1f;
							UpdateConstantBuffer(newParams, cBuffer);

							m_pContext->CSSetShader(ComputeShader::DX11ComputeShader[1].Get(), 0, 0);
							m_pContext->Dispatch(65000, 4, 1);

							m_pContext->CSSetShader(ComputeShader::DX11ComputeShader[2].Get(), 0, 0);
							m_pContext->Dispatch(65000, 4, 1);

							m_pContext->CSSetShader(ComputeShader::DX11ComputeShader[3].Get(), 0, 0);
							m_pContext->Dispatch(65000, 4, 1);

							m_pContext->CopyResource(stagProfitBuffer.Get(), outBuffer.Get());
							m_pContext->Map(stagProfitBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
							MyOutput* o = (MyOutput*)(mapped.pData);

							std::vector<MyOutput> fwd(o, o + _Total);
							finalResult[0][_ARatio][_Range][_Huge] =
								std::async(std::launch::async, Stock::DoHomework, fwd);

							m_pContext->Unmap(stagProfitBuffer.Get(), 0);
						}

				std::vector<MyResultPrint> finalResultPrint;
				for (int j = 0; j < dim2; ++j)
					for (int k = 0; k < dim3; ++k)
						for (int l = 0; l < dim4; ++l)
						{
							MyResult result = finalResult[0][j][k][l].get();

							MyResultPrint print;
							print.maxLifetime = result.maxLifetime;
							print.profit = result.profit;
							print.loss = result.loss;
							print.tradeCount = result.tradeCount;
							print.__tp = _TP;
							print.__aratio = j;
							print.__range = k;
							print.__huge = l;

							finalResultPrint.push_back(print);
						}

				CacheVector<MyResultPrint>(finalResultPrint, "OUTPUT/" + currencyPair + "/FINAL_RESULT_CACHE_" + std::to_string(_TP));
			}
			timer.End();

			Logger::ThrowBox("DONE"
				"\nElapsed: " + std::to_string(timer.GetDelta() / 3600.0f)
			);
		}*/

		void Graphics::AddModel(const Entity& e)
		{
			/*
			if( ECS_GetHandle(e.GetID(), Mesh).size() == 0 ) Logger::ThrowBox("AddModel:\nEntity doesn't have Mesh Component.");
			if (ECS_GetHandle(e.GetID(), Renderer).size() == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Renderer Component.");
			if (ECS_GetHandle(e.GetID(), Transform).size() == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Transform Component.");
			*/
			std::vector<int> vertexCount;

			for (int mesh_iter = 0; mesh_iter < ECS_GetHandle(e.GetID(), Mesh).size(); ++mesh_iter)
			{
				auto _mesh = e.GetComponent<Mesh>(mesh_iter);

				for (int rend_iter = 0; rend_iter < ECS_GetHandle(e.GetID(), Renderer).size(); ++rend_iter)
				{
					auto _rend = e.GetComponent<Renderer>(rend_iter);
					auto _tra = e.GetComponent<Transform>();

					if (_mesh.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Mesh Component.");
					if (_rend.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Renderer Component.");
					if (_tra.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Transform Component.");

					vertexCount.push_back(_mesh.vertices.size());
					if (_mesh.vertices.size())
					{
						int _vs = 0;
						for (auto& name : Component::VertexShader::name)
							if (name == _rend.vertexShader) break;
							else ++_vs;

						if (_vs >= Component::VertexShader::name.size())
							Logger::ThrowBox("AddModel failed.\nVertexShader with name " + _rend.vertexShader + " doesn't exist.");

						int _ps = 0;
						for (auto& name : Component::PixelShader::name)
							if (name == _rend.pixelShader) break;
							else ++_ps;

						if (_ps >= Component::PixelShader::name.size())
							Logger::ThrowBox("AddModel failed.\nPixelShader with name " + _rend.pixelShader + " doesn't exist.");

						DrawData _dd;
						CreateVertexBuffer(_mesh.vertices, _dd.vertexBuffer);
						CreateIndexBuffer(_mesh.indices, _dd.indexBuffer);
						_dd.vertexStride = sizeof(_mesh.vertices[0]);
						_dd.indexCount = (unsigned int)_mesh.indices.size();

						_dd.instanceCount = 0;
						std::vector<XMMATRIX> _m;
						_m.push_back(_mesh.fix);
						for (const auto& i : ECS_GetHandle(e.GetID(), Transform))
						{
							auto __tra = Transform::Wrapper(i);
							XMMATRIX __tm = XMMatrixTranslation(__tra.position.x, __tra.position.y, __tra.position.z);
							XMMATRIX __rm = XMMatrixRotationRollPitchYaw(
								XMConvertToRadians(__tra.rotation.x),
								XMConvertToRadians(__tra.rotation.y),
								XMConvertToRadians(__tra.rotation.z));

							_m.push_back(XMMatrixIdentity() * _mesh.fix * __rm * __tm);
							++_dd.instanceCount;
						}
						CreateResourceBuffer(_m, _rend.instanceBuffer);
						CreateSRV(_rend.instanceBuffer, _dd.instanceBufferView);

						for (auto& t : _rend.textures)
						{
							int i = 0;
							for (int i = 1; i < Component::Texture2D::name.size(); ++i)
							{
								if (Component::Texture2D::name[i] == t)
								{
									Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
									CreateSRV(Component::Texture2D::DX11Texture[i], srv);
									_dd.psResources.push_back(srv);
									break;
								}
								else ++i;
							}
						}

						int _key = (_vs << 8) | _ps;
						if (m_DrawCache.find(_key) == m_DrawCache.end())
							m_DrawCache.emplace(_key, std::vector<DrawData>());

						_rend.pipelineHandle = (int)m_DrawCache[_key].size();
						m_DrawCache[_key].push_back(_dd);
					}
				}
			}

			std::string out;
			for (auto& vc : vertexCount)
				out += std::to_string(vc) + "\n";

			//Logger::ThrowBox(out);
		}

		void Graphics::AddModel(const Entity& e, const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices, const int& at)
		{
			auto _mesh = e.GetComponent<Mesh>(at);
			auto _rend = e.GetComponent<Renderer>(at);
			auto _tra = e.GetComponent<Transform>();
			
			if (_mesh.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Mesh Component.");
			if (_rend.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Renderer Component.");
			if (_tra.id == 0) Logger::ThrowBox("AddModel:\nEntity doesn't have Transform Component.");

			size_t _offset = _mesh.vertices.size();
			for (auto i : indices)
				_mesh.indices.push_back(i + _offset);

			for (auto& v : vertices)
				_mesh.vertices.push_back(v);


			int _vs = 0;
			for (auto& name : Component::VertexShader::name)
				if (name == _rend.vertexShader) break;
				else ++_vs;

			if (_vs >= Component::VertexShader::name.size())
				Logger::ThrowBox("AddModel failed.\nVertexShader with name " + _rend.vertexShader + " doesn't exist.");

			int _ps = 0;
			for (auto& name : Component::PixelShader::name)
				if (name == _rend.pixelShader) break;
				else ++_ps;

			if (_ps >= Component::PixelShader::name.size())
				Logger::ThrowBox("AddModel failed.\nPixelShader with name " + _rend.pixelShader + " doesn't exist.");

			DrawData _dd;
			CreateVertexBuffer(_mesh.vertices, _dd.vertexBuffer);
			CreateIndexBuffer(_mesh.indices, _dd.indexBuffer);
			_dd.vertexStride = sizeof(_mesh.vertices[0]);
			_dd.indexCount = (unsigned int)_mesh.indices.size();

			_dd.instanceCount = 0;
			std::vector<XMMATRIX> _m;
			for (const auto& i : ECS_GetHandle(e.GetID(), Transform))
			{
				auto __tra = Transform::Wrapper(i);
				XMMATRIX __tm = XMMatrixTranslation(__tra.position.x, __tra.position.y, __tra.position.z);
				XMMATRIX __rm = XMMatrixRotationRollPitchYaw(
					XMConvertToRadians(__tra.rotation.x),
					XMConvertToRadians(__tra.rotation.y),
					XMConvertToRadians(__tra.rotation.z));

				_m.push_back(XMMatrixIdentity() * __rm * __tm);
				++_dd.instanceCount;
			}
			CreateResourceBuffer(_m, _rend.instanceBuffer);
			CreateSRV(_rend.instanceBuffer, _dd.instanceBufferView);

			for (auto& t : _rend.textures)
			{
				int i = 0;
				for (int i = 1; i < Component::Texture2D::name.size(); ++i)
				{
					if (Component::Texture2D::name[i] == t)
					{
						Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
						CreateSRV(Component::Texture2D::DX11Texture[i], srv);
						_dd.psResources.push_back(srv);
						break;
					}
					else ++i;
				}
			}


			int _key = (_vs << 8) | _ps;
			if (m_DrawCache.find(_key) == m_DrawCache.end())
				m_DrawCache.emplace(_key, std::vector<DrawData>());

			_rend.pipelineHandle = (int)m_DrawCache[_key].size();
			m_DrawCache[_key].push_back(_dd);
		}

		void Graphics::AddTexture(const std::filesystem::path& path, const void* data, const int& width, const int& height,
			const DXGI_FORMAT& format, aiTextureType type, const std::string& storageType)
		{
			core->AddComponent<Texture2D>();
			auto _tex = core->GetComponent<Texture2D>(-1);
			_tex.name = UniqueName(path.filename().string() + Caster::Str(type));
			_tex.format = format;
			_tex.width = width;
			_tex.height = height;
			_tex.type = Caster::Str(type);
			_tex.storageType = storageType;

			if (path.extension().string() == ".dds")
			{
				hr = CreateDDSTextureFromFile(m_pDevice.Get(), path.wstring().c_str(), (ID3D11Resource**)_tex.DX11Texture.GetAddressOf(), _tex.DX11View.GetAddressOf());
				LogError(hr, "Creating DDS texture failed.");
			}
			else
			{
				if (storageType == "Embedded")
				{
					hr = CreateWICTextureFromMemory(m_pDevice.Get(), (const uint8_t*)data, width, (ID3D11Resource**)_tex.DX11Texture.GetAddressOf(), _tex.DX11View.GetAddressOf());
					LogError(hr, "Creating WIC Embedded texture failed.");
				}
				else if (storageType == "EmbeddedIndex")
				{
					hr = CreateWICTextureFromMemory(m_pDevice.Get(), (const uint8_t*)data, width, (ID3D11Resource**)_tex.DX11Texture.GetAddressOf(), _tex.DX11View.GetAddressOf());
					LogError(hr, "Creating WIC Indexed texture failed.");
				}
				else
				{
					hr = CreateWICTextureFromFile(m_pDevice.Get(), path.wstring().c_str(), (ID3D11Resource**)_tex.DX11Texture.GetAddressOf(), _tex.DX11View.GetAddressOf());
					LogError(hr, "Creating WIC texture failed.");
				}
			}
		}


		void Graphics::AddCamera(const Entity& e) {
			auto _cam = e.GetComponent<Camera>();

			for (auto& ac : m_activeCameras)
				if (ac == _cam.id) Logger::ThrowBox("AddCamera:\nThis Camera already exists.");

			_cam.rotationMatrix = XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(_cam.rotation.x),
				XMConvertToRadians(_cam.rotation.y),
				XMConvertToRadians(_cam.rotation.z));

			XMVECTOR position = XMLoadFloat3(&_cam.position);

			XMVECTOR focusPoint = XMVector3Transform(Defaults::Vector::Forward, _cam.rotationMatrix);
			focusPoint += position;

			XMVECTOR up = XMVector3Transform(Defaults::Vector::Up, _cam.rotationMatrix);
			_cam.viewMatrix = XMMatrixLookAtLH(position, focusPoint, up);

			XMMATRIX mvp = XMMatrixIdentity() * _cam.viewMatrix * _cam.projectionMatrix;

			CreateConstantBuffer(SingleMatrixBuffer(mvp), _cam.mvpConstantBuffer);

			m_activeCameras.push_back(_cam.id);
		}




		void Graphics::LoadMesh(Entity& e, const std::string& filePath)
		{
			//const size_t meshHandle = ECS_GetHandle(e.GetID(), Mesh)[0];
			//if (!meshHandle) Logger::ThrowBox("Can't load mesh for entity without Mesh Component.");

			Assimp::Importer importer;
			const aiScene* pScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
			if (pScene != nullptr)
			{
				aiNode* root = pScene->mRootNode;
				ASSIMP_LoadMeshRec(e, root, pScene, XMMatrixIdentity());
			}
			else Logger::ThrowBox("LoadModel function failed.");
		}

		void Graphics::LoadTexture(const std::filesystem::path& filePath, Microsoft::WRL::ComPtr<ID3D11Texture2D>& dest)
		{
		}

		void Graphics::ExtractTextures(const std::filesystem::path& filePath)
		{
			Assimp::Importer importer;
			const aiScene* pScene = importer.ReadFile(filePath.string(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
			if (pScene != nullptr)
			{
				int textureCount = 0;
				for (size_t i = 0; i < pScene->mNumMaterials; ++i)
				{
					textureCount += ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_DIFFUSE);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_DIFFUSE_ROUGHNESS);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_AMBIENT);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_AMBIENT_OCCLUSION);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_BASE_COLOR);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_DISPLACEMENT);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_EMISSIVE);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_EMISSION_COLOR);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_HEIGHT);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_LIGHTMAP);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_METALNESS);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_NORMALS);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_NORMAL_CAMERA);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_OPACITY);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_REFLECTION);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_SHININESS);
					ASSIMP_ExtractTextures(filePath, pScene->mMaterials[i], pScene, aiTextureType_SPECULAR);
				}

				if (textureCount == 0)
				{
					aiColor3D aiColor(0.0f, 0.0f, 0.0f);
					pScene->mMaterials[0]->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
					if (aiColor.IsBlack())
					{
						core->AddComponent<Texture2D>();
						auto _tex = core->GetComponent<Texture2D>(-1);
						_tex.name = UniqueName(filePath.filename().string() + "Invalid");
						_tex.format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						_tex.width = 1;
						_tex.height = 1;
						_tex.type = "Invalid";
						_tex.storageType = "Runtime";

						XMFLOAT4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
						CreateTexture<XMFLOAT4>(&color, _tex.width, _tex.height, _tex.DX11Texture, _tex.format);
						CreateSRV(_tex.DX11Texture, _tex.DX11View);
					}
					else
					{
						core->AddComponent<Texture2D>();
						auto _tex = core->GetComponent<Texture2D>(-1);
						_tex.name = UniqueName(filePath.filename().string() + "SolidColor");
						_tex.format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						_tex.width = 1;
						_tex.height = 1;
						_tex.type = "SolidColor";
						_tex.storageType = "Runtime";

						XMFLOAT4 color = { aiColor.r, aiColor.g, aiColor.b, 1.0f };
						CreateTexture<XMFLOAT4>(&color, _tex.width, _tex.height, _tex.DX11Texture, _tex.format);
						CreateSRV(_tex.DX11Texture, _tex.DX11View);
					}

				}
			}
			else Logger::ThrowBox("ExtractTexture function failed.");
		}


		size_t Graphics::GetWidth() { return m_width; }
		size_t Graphics::GetHeight() { return m_height; }

		/*
		size_t Graphics::Calculate_All_Vertices() {
			size_t num_v = 0;
			for (auto & a : ECS::Component::Mesh::vertices)
				for (auto & b : a)
					for (auto & c : b)
						++num_v;
			return num_v;
		}
		*/


		// Graphics

		void Graphics::InitHard()
		{
			hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)m_pFactory.GetAddressOf());
			LogError(hr, "Factory creation failed.");

			std::vector<__COM__<IDXGIAdapter>> adapters;
			int index = 0;
			while (SUCCEEDED(m_pFactory->EnumAdapters(index, m_pAdapter.GetAddressOf())))
			{
				adapters.push_back(m_pAdapter);
				m_pAdapter.Reset();
				index++;
			}

			if (adapters.size() < 1)
				Logger::ThrowBox("No adapter found.");
			else if (adapters.size() > 1)
			{
				std::sort(adapters.begin(), adapters.end(), [](__COM__<IDXGIAdapter> a, __COM__<IDXGIAdapter> b) {

					DXGI_ADAPTER_DESC aDesc, bDesc;
					a->GetDesc(&aDesc);
					b->GetDesc(&bDesc);

					if (aDesc.DedicatedVideoMemory > bDesc.DedicatedVideoMemory)
						return true;
					else
						return false;
					}
				);
				m_pAdapter = adapters.front();
			}
			else
				m_pAdapter = adapters[0];

			hr = m_pAdapter->EnumOutputs(0, m_pOutput.GetAddressOf());
			LogError(hr, "Monitor enumeration failed.");
		}

		void Graphics::InitSoft() {
			RECT rect;
			GetClientRect(m_hWnd, &rect);
			m_width = (size_t)(rect.right - rect.left);
			m_height = (size_t)(rect.bottom - rect.top);

			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			swapChainDesc.BufferCount = 1;
			swapChainDesc.BufferDesc.Width = (UINT)m_width;
			swapChainDesc.BufferDesc.Height = (UINT)m_height;
			swapChainDesc.BufferDesc.RefreshRate.Numerator = m_vSync ? 60 : 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = m_vSync ? 1 : 1;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			swapChainDesc.OutputWindow = m_hWnd;
			swapChainDesc.Windowed = true;

			D3D_FEATURE_LEVEL pFeatureLevels[] =
			{
					D3D_FEATURE_LEVEL_11_1,
					D3D_FEATURE_LEVEL_11_0
			};
			//D3D_FEATURE_LEVEL_10_1,
			//D3D_FEATURE_LEVEL_10_0,
			//D3D_FEATURE_LEVEL_9_3,
			//D3D_FEATURE_LEVEL_9_2,
			//D3D_FEATURE_LEVEL_9_1,

			hr = D3D11CreateDeviceAndSwapChain(
				m_pAdapter.Get(),
				D3D_DRIVER_TYPE_UNKNOWN,
				NULL,
				D3D11_CREATE_DEVICE_DEBUG,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&swapChainDesc,
				m_pSwapChain.GetAddressOf(),
				m_pDevice.GetAddressOf(),
				NULL,
				m_pContext.GetAddressOf());
			LogError(hr, "Swap creation failed.");


			m_RTV_array.push_back(__COM__<ID3D11RenderTargetView>());
			size_t index = m_RTV_array.size() - 1;

			core->AddComponent<Component::Texture2D>();
			auto rtvTex = core->GetComponent<Component::Texture2D>(-1);
			rtvTex.name = "BackBuffer";

			hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)rtvTex.DX11Texture.GetAddressOf());
			LogError(hr, "Getting BackBuffer failed.");

			hr = m_pDevice->CreateRenderTargetView(rtvTex.DX11Texture.Get(), 0, m_RTV_array[index].GetAddressOf());
			LogError(hr, "RTV creation failed.");
		}

		void Graphics::InitShaders()
		{
			CreateInputLayout("default",
				{
					{ "POSITION",   0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,   0,  D3D11_INPUT_PER_VERTEX_DATA,   0 },
					{ "TEXCOORD",   0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  16,  D3D11_INPUT_PER_VERTEX_DATA,   0 },
					{ "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  32,  D3D11_INPUT_PER_VERTEX_DATA,   0 },
					{ "NORMAL",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  48,  D3D11_INPUT_PER_VERTEX_DATA,   0 },

					{ "TRANSFORM_POSITION",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,  1,  64,  D3D11_INPUT_PER_INSTANCE_DATA, 0 },
					{ "TRANSFORM_ROTATION",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,  1,  80,  D3D11_INPUT_PER_INSTANCE_DATA, 0 },
					{ "TRANSFORM_SCALE",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  1,  96,  D3D11_INPUT_PER_INSTANCE_DATA, 0 }
				});

#ifdef _DEBUG
			if (IsDebuggerPresent())
				// Recompile shaders when you launch from VisualStudio to apply possible changes you made in HLSL code
			{
				CompileVS("DefaultVS", "src/HLSL/");
				CompilePS("DefaultPS", "src/HLSL/");
				CompileCS("DefaultCS", "src/HLSL/");
			}
			else
			{
				LoadVS("DefaultVS");
				LoadPS("DefaultPS");
				LoadCS("DefaultCS");
			}
#else
			if (IsDebuggerPresent())
			{
				CompileVS("DefaultVS", "src/HLSL/");
				CompilePS("DefaultPS", "src/HLSL/");
				CompileCS("DefaultCS", "src/HLSL/");
			}
			else
			{
				LoadVS("DefaultVS");
				LoadPS("DefaultPS");
				LoadCS("DefaultCS");
			}
#endif
		}

		void Graphics::InitViews() {
			// Note: First RenderTargetView (with index 0) is the BackBuffer used by SwapChain (created in InitSoft function)
			CreateViewport();            // Utility::VP::Default
			CreateDepthStencilView();    // Utility::DSV::Default

			SetRenderTargets();
			SetViewports();
		}

		void Graphics::InitStates() {
			CreateRasterizerState(1, Fill::Solid, Cull::None);                        // Utility::RS::CW
			CreateRasterizerState(0, Fill::Solid, Cull::Back);                        // Utility::RS::CCW
			CreateDepthStencilState(1, DepthWriteMask::All, Comparison::LessEqual);   // Utility::DSS::Default
			CreateBlendState(1, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add);   // Utility::BS::Default

			SetRasterizerState(RS::CW);
			SetBlendState(BS::Default);
			SetDepthStencilState(DSS::Default);
		}

		void Graphics::InitBuffers() {

		}



		inline void Graphics::Clear()
		{
			for (size_t i = 0; i < m_RTV_array.size(); ++i)
				ClearRTV(i);
			for (size_t i = 0; i < m_DSV_array.size(); ++i)
				ClearDSV(i, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL);
		}

		inline void Graphics::ClearRTV(const size_t rtv, const DirectX::XMFLOAT3& rgb)
		{
			static float color[4];
			color[0] = rgb.x;
			color[1] = rgb.y;
			color[2] = rgb.z;
			color[3] = 1.0f;

			m_pContext->ClearRenderTargetView(m_RTV_array[rtv].Get(), color);
		}

		inline void Graphics::ClearDSV(const size_t dsv, const UINT& clearFlags,
			const FLOAT& depth, const UINT8& stencil) {
			m_pContext->ClearDepthStencilView(m_DSV_array[dsv].Get(), clearFlags, depth, stencil);
		}

		inline void Graphics::Prepare() {
			//PrepareModels();
			PrepareCameras();
		}

		/*
		inline void Graphics::PrepareModels() {
			// Update Vertex and Index buffers if geometry has been edited
			static size_t MeshVersion = 0;
			if (MeshVersion != Component::Mesh::Version[0])
			{
				m_Pipeline.resize(0);
				m_Pipeline = DYNAMIC_ARRAY_04_INIT( size_t, DM::_Count, m_VS_array.size(), m_PS_array.size(), 0 );

				DYNAMIC_ARRAY_05(size_t) temp_indices =
					DYNAMIC_ARRAY_05_INIT(size_t, DM::_Count, m_VS_array.size(), m_PS_array.size(), 0, 0);
				DYNAMIC_ARRAY_05(Vertex) temp_vertices =
					DYNAMIC_ARRAY_05_INIT(Vertex, DM::_Count, m_VS_array.size(), m_PS_array.size(), 0, 0);

				// Initialize for single buffer drawing
				for (size_t dm = 0; dm < DM::_CountSingle; dm++)
					for (size_t vs = 0; vs < m_VS_array.size(); vs++)
						for (size_t ps = 0; ps < m_PS_array.size(); ps++)
						{
							temp_vertices[dm][vs][ps].push_back(std::vector<Vertex>(0));
							temp_indices[dm][vs][ps].push_back(std::vector<size_t>(0));
						}


				// Segregate vertex and index data by DrawMode
				// it allows to merge some geometry into one big vertex buffer and draw it with a single draw call
				size_t indexStride = 0;
				for (size_t i = 0; i < ECS_EntityCount; ++i)
				{
					static size_t index = 0;
					if (index = ECS_GetHandle(i, Mesh))
					{
						for (size_t j = 0; j < Component::Mesh::vertices[index].size(); ++j)
						{
							const size_t vs = Component::Renderer::vertexShader[index][j];
							const size_t ps = Component::Renderer::pixelShader[index][j];
							const size_t dm = Component::Renderer::drawMode[index][j];

							// if DrawMode is Single 4th dimension index is equal 0 because we push everything to 1 buffer
							if (dm < 3)
							{
								for (auto & ind : Component::Mesh::indices[index][j])
									temp_indices[dm][vs][ps][0].push_back(ind + indexStride);

								indexStride = temp_indices[dm][vs][ps][0].size();

								for (auto & ver : Component::Mesh::vertices[index][j])
									temp_vertices[dm][vs][ps][0].push_back(ver);
							}
							else
							{
								m_Pipeline[dm][vs][ps].push_back(DrawInfo(
									Component::Mesh::vertices[index][j],
									Component::Mesh::indices[index][j]
								));
							}
						}
					}
				}

				// Filling DrawInfo structs for single buffer drawing
				for (size_t dm = 0; dm < DM::_CountSingle; dm++)
					for (size_t vs = 0; vs < m_VS_array.size(); vs++)
						for (size_t ps = 0; ps < m_PS_array.size(); ps++)
						{
							if ((temp_vertices[dm][vs][ps].size() == 0) || (temp_indices[dm][vs][ps].size() == 0))
								continue;
							else if ((temp_vertices[dm][vs][ps][0].size() == 0) || (temp_indices[dm][vs][ps][0].size() == 0))
								continue;

							m_Pipeline[dm][vs][ps].push_back(DrawInfo());
							CreateVertexBuffer(temp_vertices[dm][vs][ps][0], m_Pipeline[dm][vs][ps][0].vertexBuffer);
							m_Pipeline[dm][vs][ps][0].vertexStride = sizeof(ECS::System::Graphics::Utility::Vertex);
							CreateIndexBuffer(temp_indices[dm][vs][ps][0], m_Pipeline[dm][vs][ps][0].indexBuffer);
							m_Pipeline[dm][vs][ps][0].indexCount = temp_indices[dm][vs][ps][0].size();
						}

				MeshVersion = Component::Mesh::Version;
			}
		}
		*/

		inline void Graphics::PrepareCameras() {
			for (const auto& ac : m_activeCameras)
			{
				Component::Camera::rotationMatrix[ac] = XMMatrixRotationRollPitchYaw(
					XMConvertToRadians(Component::Camera::rotation[ac].x),
					XMConvertToRadians(Component::Camera::rotation[ac].y),
					XMConvertToRadians(Component::Camera::rotation[ac].z));

				XMVECTOR position = XMLoadFloat3(&Component::Camera::position[ac]);

				XMVECTOR focusPoint = XMVector3Transform(Defaults::Vector::Forward, Component::Camera::rotationMatrix[ac]);
				focusPoint += position;

				XMVECTOR up = XMVector3Transform(Defaults::Vector::Up, Component::Camera::rotationMatrix[ac]);
				Component::Camera::viewMatrix[ac] = XMMatrixLookAtLH(position, focusPoint, up);

				XMMATRIX mvp = XMMatrixIdentity()
					* Component::Camera::viewMatrix[ac]
					* Component::Camera::projectionMatrix[ac];

				SingleMatrixBuffer smb(mvp);
				UpdateConstantBuffer(smb, Component::Camera::mvpConstantBuffer[ac]);
			}
		}

		inline void Graphics::Draw() {
			SetTopology(Topology::TriangleList);

			for (const auto& ac : m_activeCameras) {
				m_pContext->VSSetConstantBuffers(0, 1, Component::Camera::mvpConstantBuffer[ac].GetAddressOf());
				m_pContext->RSSetViewports(1, &m_VP_array[(size_t)Component::Camera::viewport[ac]]);

				for (size_t dm = 0; dm < 1; dm++)
					for (size_t vs = 1; vs < VertexShader::name.size(); ++vs) {
						SetVertexShader(VS(vs));
						for (size_t ps = 1; ps < PixelShader::name.size(); ++ps) {
							SetPixelShader(PS(ps));

							if (Component::VertexShader::DX11ConstantBuffers[vs].size())
								m_pContext->VSSetConstantBuffers(2, Component::VertexShader::DX11ConstantBuffers[vs].size(),
									Component::VertexShader::DX11ConstantBuffers[vs][0].GetAddressOf());

							if (Component::PixelShader::DX11ConstantBuffers[ps].size())
								m_pContext->PSSetConstantBuffers(0, Component::PixelShader::DX11ConstantBuffers[ps].size(),
									Component::PixelShader::DX11ConstantBuffers[ps][0].GetAddressOf());

							int key = (vs << 8) | ps;
							for (auto& dd : m_DrawCache.at(key))
							{
								static const UINT offset = 0;
								const UINT vstride = dd.vertexStride;

								m_pContext->VSSetShaderResources(0, 1, dd.instanceBufferView.GetAddressOf());

								if (dd.psResources.size())
									m_pContext->PSSetShaderResources(0, dd.psResources.size(), dd.psResources[0].GetAddressOf());

								m_pContext->IASetVertexBuffers(0, 1, dd.vertexBuffer.GetAddressOf(), &vstride, &offset);
								m_pContext->IASetIndexBuffer(dd.indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

								m_pContext->DrawIndexedInstanced(dd.indexCount, dd.instanceCount, 0, 0, 0);
							}
						}
					}
			}

			//DrawTransparent();
			//DrawSolid();
		}

		inline void Graphics::DrawTransparent()
		{

		}

		inline void Graphics::DrawSolid()
		{

		}

		inline void Graphics::Present() { m_pSwapChain->Present(m_vSync ? 1 : 0, 0); }

		void Graphics::CreateInputLayout(const std::string& inputLayoutName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& description)
		{
			for (const auto& name : Component::InputLayout::name)
				if (name == inputLayoutName) Logger::ThrowBox("InputLayout with name \"" + name + "\" already exists.");

			core->AddComponent<InputLayout>();
			auto _il = core->GetComponent<InputLayout>(-1);
			_il.name = inputLayoutName;
			_il.description = description;
		}

		void Graphics::CompileVS(const std::string& vsFileName, const std::string& path, const std::string& vsModel,
			const std::string& inputLayoutName, const std::string& entryPoint)
		{
			for (const auto& name : Component::VertexShader::name)
				if (name == vsFileName) Logger::ThrowBox("VertexShader with name \"" + name + "\" already exists.");

			core->AddComponent<VertexShader>();
			auto _vs = core->GetComponent<VertexShader>(-1);
			_vs.name = vsFileName;
			_vs.path = path;
			_vs.model = vsModel;
			_vs.inputLayout = inputLayoutName;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(vsFileName) + L".hlsl");
			std::string errorDisplay("PATH : " + Caster::Str(fullPath) + "\n" +
				"FILENAME : " + vsFileName + "\n"
				"MODEL : " + vsModel + "\n"
				"ENTRYPOINT : " + entryPoint);

			if (SUCCEEDED(hr = D3DCompileFromFile(fullPath.c_str(), NULL, NULL, entryPoint.c_str(), vsModel.c_str(),
				D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0, _vs.blob.GetAddressOf(), NULL)))
			{
				hr = m_pDevice->CreateVertexShader(_vs.blob.Get()->GetBufferPointer(),
					_vs.blob.Get()->GetBufferSize(), NULL, _vs.DX11VertexShader.GetAddressOf());
				LogError(hr, "VS creation failed.");

				int x = 0;
				for (const auto& name : Component::InputLayout::name)
					if (name == inputLayoutName)
					{
						auto __il = Component::InputLayout::Wrapper(x);
						hr = m_pDevice->CreateInputLayout(__il.description.begin()._Ptr, __il.description.size(),
							_vs.blob.Get()->GetBufferPointer(), _vs.blob.Get()->GetBufferSize(),
							_vs.DX11InputLayout.GetAddressOf());
						LogError(hr, "InputLayout creation failed.");
						break;
					}
					else ++x;

				if (x > Component::InputLayout::name.size())
					Logger::ThrowBox("InputLayout with name \"" + inputLayoutName + "\" doesn't exist.");
			}
			else LogError(hr, errorDisplay.c_str());
		}

		void Graphics::CompilePS(const std::string& psFileName, const std::string& path,
			const std::string& psModel, const std::string& entryPoint)
		{
			for (const auto& name : Component::PixelShader::name)
				if (name == psFileName) Logger::ThrowBox("PixelShader with name \"" + name + "\" already exists.");

			core->AddComponent<PixelShader>();
			auto _ps = core->GetComponent<PixelShader>(-1);
			_ps.name = psFileName;
			_ps.path = path;
			_ps.model = psModel;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(psFileName) + L".hlsl");
			std::string errorDisplay("PATH : " + Caster::Str(fullPath) + "\n" +
				"FILENAME : " + psFileName + "\n"
				"MODEL : " + psModel + "\n"
				"ENTRYPOINT : " + entryPoint);

			if (SUCCEEDED(hr = D3DCompileFromFile(fullPath.c_str(), NULL, NULL, entryPoint.c_str(), psModel.c_str(),
				D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0, _ps.blob.GetAddressOf(), NULL)))
			{
				hr = m_pDevice->CreatePixelShader(_ps.blob.Get()->GetBufferPointer(),
					_ps.blob.Get()->GetBufferSize(), NULL, _ps.DX11PixelShader.GetAddressOf());
				LogError(hr, "PS creation failed.");
			}
			else LogError(hr, errorDisplay.c_str());
		}

		void Graphics::CompileCS(const std::string& csFileName, const std::string& path, const std::string& csModel, const std::string& entryPoint)
		{
			for (const auto& name : Component::ComputeShader::name)
				if (name == csFileName) Logger::ThrowBox("ComputeShader with name \"" + name + "\" already exists.");

			core->AddComponent<ComputeShader>();
			auto _cs = core->GetComponent<ComputeShader>(-1);
			_cs.name = csFileName;
			_cs.path = path;
			_cs.model = csModel;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(csFileName) + L".hlsl");
			std::string errorDisplay("PATH : " + Caster::Str(fullPath) + "\n" +
				"FILENAME : " + csFileName + "\n"
				"MODEL : " + csModel + "\n"
				"ENTRYPOINT : " + entryPoint);

			if (SUCCEEDED(hr = D3DCompileFromFile(fullPath.c_str(), NULL, NULL, entryPoint.c_str(), csModel.c_str(),
				D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
				0, _cs.blob.GetAddressOf(), NULL)))
			{
				hr = m_pDevice->CreateComputeShader(_cs.blob.Get()->GetBufferPointer(),
					_cs.blob.Get()->GetBufferSize(), NULL, _cs.DX11ComputeShader.GetAddressOf());
				LogError(hr, "CS creation failed.");
			}
			else LogError(hr, errorDisplay.c_str());
		}

		void Graphics::LoadVS(const std::string& vsFileName, const std::string& path,
			const std::string& inputLayoutName)
		{
			for (const auto& name : Component::VertexShader::name)
				if (name == vsFileName) Logger::ThrowBox("Shader with name \"" + name + "\" already exists.");

			core->AddComponent<VertexShader>();
			auto _vs = core->GetComponent<VertexShader>(-1);
			_vs.name = vsFileName;
			_vs.path = path;
			_vs.inputLayout = inputLayoutName;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(vsFileName) + L".cso");
			hr = D3DReadFileToBlob(fullPath.c_str(), _vs.blob.GetAddressOf());
			LogError(hr, "VS Blob reading failed.");

			hr = m_pDevice->CreateVertexShader(_vs.blob.Get()->GetBufferPointer(),
				_vs.blob.Get()->GetBufferSize(), NULL, _vs.DX11VertexShader.GetAddressOf());
			LogError(hr, "VS creation failed.");

			int x = 0;
			for (const auto& name : Component::InputLayout::name)
				if (name == inputLayoutName)
				{
					auto __il = Component::InputLayout::Wrapper(x);
					hr = m_pDevice->CreateInputLayout(__il.description.begin()._Ptr, __il.description.size(),
						_vs.blob.Get()->GetBufferPointer(), _vs.blob.Get()->GetBufferSize(),
						_vs.DX11InputLayout.GetAddressOf());
					LogError(hr, "InputLayout creation failed.");
					break;
				}
				else ++x;

			if (x > Component::InputLayout::name.size())
				Logger::ThrowBox("InputLayout with name \"" + inputLayoutName + "\" doesn't exist.");
		}

		void Graphics::LoadPS(const std::string& psFileName, const std::string& path)
		{
			for (const auto& name : Component::PixelShader::name)
				if (name == psFileName) Logger::ThrowBox("PixelShader with name \"" + name + "\" already exists.");

			core->AddComponent<PixelShader>();
			auto _ps = core->GetComponent<PixelShader>(-1);
			_ps.name = psFileName;
			_ps.path = path;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(psFileName) + L".cso");
			hr = D3DReadFileToBlob(fullPath.c_str(), _ps.blob.GetAddressOf());
			LogError(hr, "PS Blob reading failed.");

			hr = m_pDevice->CreatePixelShader(_ps.blob.Get()->GetBufferPointer(),
				_ps.blob.Get()->GetBufferSize(), NULL, _ps.DX11PixelShader.GetAddressOf());
			LogError(hr, "PS creation failed.");
		}

		void Graphics::LoadCS(const std::string& csFileName, const std::string& path)
		{
			for (const auto& name : Component::ComputeShader::name)
				if (name == csFileName) Logger::ThrowBox("ComputeShader with name \"" + name + "\" already exists.");

			core->AddComponent<ComputeShader>();
			auto _cs = core->GetComponent<ComputeShader>(-1);
			_cs.name = csFileName;
			_cs.path = path;

			std::wstring fullPath(Caster::Wstr(path) + Caster::Wstr(csFileName) + L".cso");
			hr = D3DReadFileToBlob(fullPath.c_str(), _cs.blob.GetAddressOf());
			LogError(hr, "CS Blob reading failed.");

			hr = m_pDevice->CreateComputeShader(_cs.blob.Get()->GetBufferPointer(),
				_cs.blob.Get()->GetBufferSize(), NULL, _cs.DX11ComputeShader.GetAddressOf());
			LogError(hr, "CS creation failed.");
		}

		void Graphics::CreateViewport(const float& width, const float& height, const float& topLeftX,
			const float& topLeftY, const float& minDepth, const float& maxDepth)
		{
			D3D11_VIEWPORT temp;
			temp.Width = width;
			temp.Height = height;
			temp.TopLeftX = topLeftX;
			temp.TopLeftY = topLeftY;
			temp.MinDepth = minDepth;
			temp.MaxDepth = maxDepth;
			m_VP_array.push_back(temp);
		}

		void Graphics::CreateRenderTargetView()
		{
			m_RTV_array.push_back(__COM__<ID3D11RenderTargetView>());
			size_t index = m_RTV_array.size() - 1;

			core->AddComponent<Texture2D>();
			auto rtvTex = core->GetComponent<Texture2D>(-1);

			hr = m_pDevice->CreateRenderTargetView(rtvTex.DX11Texture.Get(), 0, m_RTV_array[index].GetAddressOf());
			LogError(hr, "RTV creation failed.");
		}

		void Graphics::CreateDepthStencilView(const size_t& width,
			const size_t& height)
		{
			D3D11_TEXTURE2D_DESC desc;
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_D32_FLOAT;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			m_DSV_array.push_back(__COM__<ID3D11DepthStencilView>());
			size_t index = m_DSV_array.size() - 1;

			core->AddComponent<Texture2D>();
			auto dsvTex = core->GetComponent<Texture2D>(-1);
			dsvTex.name = "DepthStencil";

			hr = m_pDevice->CreateTexture2D(&desc, 0, dsvTex.DX11Texture.GetAddressOf());
			LogError(hr, "DSV buffer creation failed.");
			hr = m_pDevice->CreateDepthStencilView(dsvTex.DX11Texture.Get(), 0, m_DSV_array[index].GetAddressOf());
			LogError(hr, "DSV creation failed.");
		}

		void Graphics::CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer)
		{
			D3D11_BUFFER_DESC descBuf;
			ZeroMemory(&descBuf, sizeof(descBuf));
			buffer->GetDesc(&descBuf);

			D3D11_SHADER_RESOURCE_VIEW_DESC descView;
			ZeroMemory(&descView, sizeof(descView));
			descView.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
			descView.BufferEx.FirstElement = 0;
			descView.Format = DXGI_FORMAT_UNKNOWN;
			descView.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			m_SRV_array.push_back(__COM__<ID3D11ShaderResourceView>());
			size_t index = m_SRV_array.size() - 1;

			hr = m_pDevice->CreateShaderResourceView(buffer.Get(), &descView, m_SRV_array[index].GetAddressOf());
			LogError(hr, "ShaderResourceView creation failed.");
		}

		void Graphics::CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& dest)
		{
			D3D11_BUFFER_DESC descBuf;
			ZeroMemory(&descBuf, sizeof(descBuf));
			buffer->GetDesc(&descBuf);

			D3D11_SHADER_RESOURCE_VIEW_DESC descView;
			ZeroMemory(&descView, sizeof(descView));
			descView.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
			descView.BufferEx.FirstElement = 0;
			descView.Format = DXGI_FORMAT_UNKNOWN;
			descView.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			hr = m_pDevice->CreateShaderResourceView(buffer.Get(), &descView, dest.GetAddressOf());
			LogError(hr, "ShaderResourceView creation failed.");
		}

		void Graphics::CreateSRV(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& dest)
		{
			D3D11_TEXTURE2D_DESC descTex;
			ZeroMemory(&descTex, sizeof(descTex));
			texture->GetDesc(&descTex);

			CD3D11_SHADER_RESOURCE_VIEW_DESC descView(
				D3D11_SRV_DIMENSION_TEXTURE2D,
				descTex.Format
			);
			/*ZeroMemory(&descView, sizeof(descView));
			descView.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			descView.Format = descTex.Format;*/

			hr = m_pDevice->CreateShaderResourceView(texture.Get(), &descView, dest.GetAddressOf());
			LogError(hr, "ShaderResourceView creation failed.");
		}

		void Graphics::CreateUAV(Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer)
		{
			D3D11_BUFFER_DESC descBuf;
			ZeroMemory(&descBuf, sizeof(descBuf));
			buffer->GetDesc(&descBuf);

			D3D11_UNORDERED_ACCESS_VIEW_DESC descView;
			ZeroMemory(&descView, sizeof(descView));
			descView.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			descView.Buffer.FirstElement = 0;
			descView.Format = DXGI_FORMAT_UNKNOWN;
			descView.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			m_UAV_array.push_back(__COM__<ID3D11UnorderedAccessView>());
			size_t index = m_UAV_array.size() - 1;

			hr = m_pDevice->CreateUnorderedAccessView(buffer.Get(), &descView, m_UAV_array[index].GetAddressOf());
			LogError(hr, "UnorderedAccessView creation failed.");
		}

		void Graphics::CreateRasterizerState(const D3D11_RASTERIZER_DESC& desc)
		{
			m_RS_array.push_back(__COM__<ID3D11RasterizerState>());
			size_t index = m_RS_array.size() - 1;

			hr = m_pDevice->CreateRasterizerState(&desc, m_RS_array[index].GetAddressOf());
			LogError(hr, "RasterizerState creation failed.");
		}

		void Graphics::CreateRasterizerState(const bool isClockwise, const Fill fillMode,
			const Cull cullMode)
		{
			D3D11_RASTERIZER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
			desc.FillMode = D3D11_FILL_MODE(fillMode);
			desc.CullMode = D3D11_CULL_MODE(cullMode);
			desc.FrontCounterClockwise = !isClockwise;

			m_RS_array.push_back(__COM__<ID3D11RasterizerState>());
			size_t index = m_RS_array.size() - 1;

			hr = m_pDevice->CreateRasterizerState(&desc, m_RS_array[index].GetAddressOf());
			LogError(hr, "RasterizerState creation failed.");
		}

		void Graphics::CreateDepthStencilState(const bool depthEnable, const DepthWriteMask mask,
			const Comparison depthFunc, const bool stencilEnable)
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			desc.DepthEnable = depthEnable;
			desc.StencilEnable = stencilEnable;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(mask);
			desc.DepthFunc = D3D11_COMPARISON_FUNC(depthFunc);

			m_DSS_array.push_back(__COM__<ID3D11DepthStencilState>());
			size_t index = m_DSS_array.size() - 1;

			hr = m_pDevice->CreateDepthStencilState(&desc, m_DSS_array[index].GetAddressOf());
			LogError(hr, "DepthStencilState creation failed.");
		}

		void Graphics::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC& desc)
		{
			m_DSS_array.push_back(__COM__<ID3D11DepthStencilState>());
			size_t index = m_DSS_array.size() - 1;

			hr = m_pDevice->CreateDepthStencilState(&desc, m_DSS_array[index].GetAddressOf());
			LogError(hr, "DepthStencilState creation failed.");
		}

		void Graphics::CreateBlendState(const bool blendEnable, const Blend srcBlend,
			const Blend destBlend, const BlendOp blendOp, const Blend srcBlendAlpha, const Blend destBlendAlpha,
			const BlendOp blendOpAlpha, const ColorWriteMask mask)
		{
			D3D11_RENDER_TARGET_BLEND_DESC desc;
			desc.BlendEnable = blendEnable;
			desc.SrcBlend = D3D11_BLEND(srcBlend);
			desc.DestBlend = D3D11_BLEND(destBlend);
			desc.BlendOp = D3D11_BLEND_OP(blendOp);
			desc.SrcBlendAlpha = D3D11_BLEND(srcBlendAlpha);
			desc.DestBlendAlpha = D3D11_BLEND(destBlendAlpha);
			desc.BlendOpAlpha = D3D11_BLEND_OP(blendOpAlpha);
			desc.RenderTargetWriteMask = (UINT8)mask;

			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
			blendDesc.RenderTarget[0] = desc;

			m_BS_array.push_back(__COM__<ID3D11BlendState>());
			size_t index = m_BS_array.size() - 1;

			hr = m_pDevice->CreateBlendState(&blendDesc, m_BS_array[index].GetAddressOf());
			LogError(hr, "BlendState creation failed.");
		}

		void Graphics::CreateBlendState(const D3D11_RENDER_TARGET_BLEND_DESC& desc)
		{
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
			blendDesc.RenderTarget[0] = desc;

			m_BS_array.push_back(__COM__<ID3D11BlendState>());
			size_t index = m_BS_array.size() - 1;

			hr = m_pDevice->CreateBlendState(&blendDesc, m_BS_array[index].GetAddressOf());
			LogError(hr, "BlendState creation failed.");
		}

		void Graphics::CreateBlendState(const std::vector<D3D11_RENDER_TARGET_BLEND_DESC>& desc)
		{
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
			blendDesc.AlphaToCoverageEnable = 0;
			blendDesc.IndependentBlendEnable = desc.size() > 1 ? 1 : 0;

			for (size_t i = 0; i < desc.size(); ++i)
				blendDesc.RenderTarget[i] = desc[i];

			m_BS_array.push_back(__COM__<ID3D11BlendState>());
			size_t index = m_BS_array.size() - 1;

			hr = m_pDevice->CreateBlendState(&blendDesc, m_BS_array[index].GetAddressOf());
			LogError(hr, "BlendState creation failed.");
		}

		void Graphics::CreateSamplerState()
		{
			D3D11_SAMPLER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
			desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			desc.MinLOD = 0;
			desc.MaxLOD = D3D11_FLOAT32_MAX;

			m_SS_array.push_back(__COM__<ID3D11SamplerState>());
			size_t index = m_SS_array.size() - 1;

			hr = m_pDevice->CreateSamplerState(&desc, m_SS_array[index].GetAddressOf());
			LogError(hr, "SAMPLER ERROR");
		}

		void Graphics::CreateIndexBuffer(const std::vector<unsigned int> indices,
			Microsoft::WRL::ComPtr<ID3D11Buffer>& dest, const Usage usage)
		{
			if (indices.size() == 0)
				Logger::ThrowBox("CreateIndexBuffer funcion failed. The size of vector with Indices is 0.");

			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
			desc.Usage = D3D11_USAGE(usage);
			desc.ByteWidth = sizeof(unsigned int) * indices.size();
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			ZeroMemory(&data, sizeof(data));
			data.pSysMem = indices.begin()._Ptr;

			hr = m_pDevice->CreateBuffer(&desc, &data, dest.GetAddressOf());
			LogError(hr, "IndexBuffer creation failed.");
		}

		inline void Graphics::SetRenderTargets(const RTV renderTargetView, const DSV depthStencilView) {
			m_pContext->OMSetRenderTargets(1, m_RTV_array[(size_t)renderTargetView].GetAddressOf(), m_DSV_array[(size_t)depthStencilView].Get());
		}

		inline void Graphics::SetViewports(const VP viewport) {
			m_pContext->RSSetViewports(1, &m_VP_array[(size_t)viewport]);
		}

		inline void Graphics::SetRasterizerState(const RS rasterizerState) {
			m_pContext->RSSetState(m_RS_array[(size_t)rasterizerState].Get());
		}

		inline void Graphics::SetBlendState(const BS blendState) {
			m_pContext->OMSetBlendState(m_BS_array[(size_t)blendState].Get(), NULL, 0xFFFFFFFF);
		}

		inline void Graphics::SetDepthStencilState(const DSS depthStencilState) {
			m_pContext->OMSetDepthStencilState(m_DSS_array[(size_t)depthStencilState].Get(), 0);
		}

		inline void Graphics::SetStates(const RS rasterizerState, const BS blendState) {
			SetRasterizerState(rasterizerState);
			SetBlendState(blendState);
		}

		inline void Graphics::SetSamplerVS(const SS samplerState) {
			m_pContext->VSSetSamplers(0, 1, m_SS_array[(size_t)samplerState].GetAddressOf());
		}

		inline void Graphics::SetSamplerPS(const SS samplerState) {
			m_pContext->PSSetSamplers(0, 1, m_SS_array[(size_t)samplerState].GetAddressOf());
		}

		inline void Graphics::SetVertexShader(const VS vertexShader) {
			m_pContext->IASetInputLayout(Component::VertexShader::DX11InputLayout[(size_t)vertexShader].Get());
			m_pContext->VSSetShader(Component::VertexShader::DX11VertexShader[(size_t)vertexShader].Get(), 0, 0);
		}

		inline void Graphics::SetPixelShader(const PS pixelShader) {
			m_pContext->PSSetShader(Component::PixelShader::DX11PixelShader[(size_t)pixelShader].Get(), 0, 0);
		}

		inline void Graphics::SetShaders(const VS vertexShader, const PS pixelShader) {
			SetVertexShader(vertexShader);
			SetPixelShader(pixelShader);
		}

		inline void Graphics::SetTopology(const Topology topology) {
			m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(topology));
		}

		void Graphics::ASSIMP_LoadMeshRec(Entity& e, aiNode* pNode, const aiScene* pScene, const DirectX::XMMATRIX& transform)
		{
			XMMATRIX nodeTransformMatrix = XMMatrixTranspose(XMMATRIX(&pNode->mTransformation.a1)) * transform;

			for (size_t i = 0; i < pNode->mNumMeshes; ++i)
			{
				aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];

				std::vector<Vertex> temp_vertices;
				for (size_t j = 0; j < mesh->mNumVertices; ++j)
				{
					if (mesh->mTextureCoords[0])
					{
						temp_vertices.push_back(Vertex(
							{
							mesh->mVertices[j].x,
							mesh->mVertices[j].y,
							mesh->mVertices[j].z
							},
						{
							mesh->mTextureCoords[0][j].x,
							mesh->mTextureCoords[0][j].y,
						},
						{
							0.0f, 0.0f, 1.0f, .4f
						}
						));
					}
					else
					{
						temp_vertices.push_back(Vertex(
							{
							mesh->mVertices[j].x,
							mesh->mVertices[j].y,
							mesh->mVertices[j].z
							},
						{
							0.0f, 0.0f, 1.0f, .4f
						}
						));
					}
				}

				/*
				ECS::Component::Mesh::vertices[meshHandle].insert(
					ECS::Component::Mesh::vertices[meshHandle].end(),
					temp_vertices.begin(), temp_vertices.end());
					*/

				if (temp_vertices.size() != 0)
				{
					e.AddComponent<Mesh>();
					auto meshWrapper = e.GetComponent<Mesh>(-1);
					meshWrapper.vertices = std::move(temp_vertices);

					std::vector<unsigned int> temp_indices;
					for (size_t j = 0; j < mesh->mNumFaces; ++j)
					{
						aiFace face = mesh->mFaces[j];
						for (size_t k = 0; k < face.mNumIndices; ++k)
							temp_indices.push_back(face.mIndices[k]);
					}

					/*ECS::Component::Mesh::indices[meshHandle].insert(
						ECS::Component::Mesh::indices[meshHandle].end(),
						temp_indices.begin(), temp_indices.end());
						*/

					meshWrapper.indices = std::move(temp_indices);
					meshWrapper.fix = nodeTransformMatrix;
				}
			}
			for (size_t i = 0; i < pNode->mNumChildren; ++i)
				Graphics::ASSIMP_LoadMeshRec(e, pNode->mChildren[i], pScene, nodeTransformMatrix);
		}

		void Graphics::ASSIMP_LoadMeshRec(Entity& e, aiNode* pNode, const aiScene* pScene,
			const DirectX::XMFLOAT3& offset, const DirectX::XMFLOAT3& rotation)
		{
			Logger::ThrowBox("OVERLOAD BROKEN");

			for (size_t i = 0; i < pNode->mNumMeshes; ++i)
			{
				aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];

				std::vector<Vertex> temp_vertices;
				for (size_t j = 0; j < mesh->mNumVertices; ++j)
				{
					if (mesh->mTextureCoords[0])
					{
						temp_vertices.push_back(Vertex(
							{
							mesh->mVertices[j].x,
							mesh->mVertices[j].y,
							mesh->mVertices[j].z
							},
						{
							mesh->mTextureCoords[0][j].x,
							mesh->mTextureCoords[0][j].y,
						},
						{
							0.0f, 0.0f, 1.0f, .4f
						}
						));
					}
					else
					{
						temp_vertices.push_back(Vertex(
							{
							mesh->mVertices[j].x,
							mesh->mVertices[j].y,
							mesh->mVertices[j].z
							},
						{
							0.0f, 0.0f, 1.0f, .4f
						}
						));
					}
				}
				XMMATRIX rot_matrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
				for (auto& v : temp_vertices)
				{
					XMVECTOR vec = XMLoadFloat4(&v.position);
					vec = XMVector3Transform(vec, rot_matrix);
					XMStoreFloat4(&v.position, vec);
					v.position.x += offset.x;
					v.position.y += offset.y;
					v.position.z += offset.z;
				}
				/*ECS::Component::Mesh::vertices[meshHandle].insert(
					ECS::Component::Mesh::vertices[meshHandle].end(),
					temp_vertices.begin(), temp_vertices.end());*/

				std::vector<size_t> temp_indices;
				for (size_t j = 0; j < mesh->mNumFaces; ++j)
				{
					aiFace face = mesh->mFaces[j];
					for (size_t k = 0; k < face.mNumIndices; ++k)
						temp_indices.push_back(face.mIndices[k]);
				}
				/*ECS::Component::Mesh::indices[meshHandle].insert(
					ECS::Component::Mesh::indices[meshHandle].end(),
					temp_indices.begin(), temp_indices.end());*/
			}
			for (size_t i = 0; i < pNode->mNumChildren; ++i)
				Graphics::ASSIMP_LoadMeshRec(e, pNode->mChildren[i], pScene, offset, rotation);
		}

		int Graphics::ASSIMP_ExtractTextures(const std::filesystem::path& filePath, aiMaterial* pMaterial,
			const aiScene* pScene, aiTextureType texType)
		{
			int texCount = pMaterial->GetTextureCount(texType);
			if (texCount == 0) return 0;

			for (int i = 0; i < texCount; ++i)
			{
				aiString aiPath;
				pMaterial->GetTexture(texType, i, &aiPath);
				std::string path = filePath.parent_path().string() + "/" + aiPath.C_Str();

				if (path[0] == '*')
				{
					if (pScene->mTextures[0]->mHeight == 0)
					{
						int index = std::stoi(path.substr(1, std::string::npos));
						AddTexture(path, pScene->mTextures[index]->pcData, pScene->mTextures[index]->mWidth,
							pScene->mTextures[index]->mHeight, DXGI_FORMAT_UNKNOWN,
							aiTextureType_DIFFUSE, "EmbeddedIndex");
					}
					else Logger::ThrowBox("Indexed noncompressed textures are not supported.");
				}
				else if (auto pTex = pScene->GetEmbeddedTexture(path.c_str()))
				{
					if (pTex->mHeight == 0)
					{
						AddTexture(path, pTex->pcData, pTex->mWidth, pTex->mHeight, DXGI_FORMAT_UNKNOWN,
							aiTextureType_DIFFUSE, "Embedded");
					}
					else Logger::ThrowBox("Embedded noncompressed textures are not supported.");
				}
				else if (path.find('.') != std::string::npos)
				{
					AddTexture(path, nullptr, 0, 0, DXGI_FORMAT_UNKNOWN,
						texType, "Disc");
				}

			}
			return texCount;
		}

		std::string Graphics::UniqueName(const std::string& name)
		{
			int index = 0;
			std::string newName = name;

			for (int i = 0; i < ECS::Component::Texture2D::name.size(); ++i)
			{
				if (newName == ECS::Component::Texture2D::name[i])
				{
					++index;
					newName = name + std::to_string(index);
					i = -1;
				}
			}
			return newName;
		}
	}

}