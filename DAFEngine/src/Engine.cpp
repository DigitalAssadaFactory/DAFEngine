#include "Engine.h"



namespace DAF
{
	using namespace ECS;
	using namespace ECS::System;
	using namespace ECS::Component;
	using namespace ECS::Utility::Graphics;
	using namespace Geometry;
	using namespace DirectX;

	Engine::Engine(std::string title, size_t width, size_t height)
		: m_hInstance(GetModuleHandle(nullptr))
	{
		if (FAILED(CoInitialize(0)))
			Logger::ThrowBox("Coinitialize failed.");

		static bool instanced = false;
		if (instanced) Logger::ThrowBox("Only one instance of Engine class allowed.");
		else instanced = true;

		float posX = Defaults::FULL_SCREEN_WIDTH * 0.5f - width * 0.5f;
		float posY = Defaults::FULL_SCREEN_HEIGHT * 0.5f - height * 0.5f;

		InitWindow(title, "MainWindow", (LONG)width, (LONG)height, (LONG)posX, (LONG)posY);

		ShowWindow(m_hWnd, SW_SHOW);
	}

	void Engine::StartUp()
	{
		System::Graphics::Init(m_hWnd);
		//System::Physics::Init();
		Time::Hourglass timer;

		//std::default_random_engine my_seed;
		//std::normal_distribution<float> dist(-10, 10);
		//std::normal_distribution<float> dist2(0, 1.0f);

		std::string currencyPair = "USDCAD";

		//StockConfig(currencyPair, 0.0f);
		//Logger::ThrowBox("safe break");

		//---------------------------------------------------
		//                 Loading Cache
		//---------------------------------------------------
		/*
		std::future<std::vector<int>>   fBarID = std::async(std::launch::async, LoadVectorCache<int>,    "cache/"+currencyPair+"_Cache/barIDCache");
		std::future<std::vector<float>> fOpen = std::async(std::launch::async, LoadVectorCache<float>,   "cache/"+currencyPair+"_Cache/openCache");
		std::future<std::vector<float>> fClose = std::async(std::launch::async, LoadVectorCache<float>,  "cache/"+currencyPair+"_Cache/closeCache");
		std::future<std::vector<float>> fHigh = std::async(std::launch::async, LoadVectorCache<float>,   "cache/"+currencyPair+"_Cache/highCache");
		std::future<std::vector<float>> fLow = std::async(std::launch::async, LoadVectorCache<float>,    "cache/"+currencyPair+"_Cache/lowCache");
		std::future<std::vector<float>> fAsk = std::async(std::launch::async, LoadVectorCache<float>,    "cache/"+currencyPair+"_Cache/askCache");
		std::future<std::vector<float>> fBid = std::async(std::launch::async, LoadVectorCache<float>,    "cache/"+currencyPair+"_Cache/bidCache");
		std::future<std::vector<int>>   fYear = std::async(std::launch::async, LoadVectorCache<int>,     "cache/"+currencyPair+"_Cache/yearCache");
		std::future<std::vector<int>>   fMon = std::async(std::launch::async, LoadVectorCache<int>,      "cache/"+currencyPair+"_Cache/monCache");
		std::future<std::vector<int>>   fDay = std::async(std::launch::async, LoadVectorCache<int>,      "cache/"+currencyPair+"_Cache/dayCache");
		std::future<std::vector<int>>   fHour = std::async(std::launch::async, LoadVectorCache<int>,     "cache/"+currencyPair+"_Cache/hourCache");
		std::future<std::vector<int>>   fMin = std::async(std::launch::async, LoadVectorCache<int>,      "cache/"+currencyPair+"_Cache/minCache");
		std::future<std::vector<int>>   fSec = std::async(std::launch::async, LoadVectorCache<int>,      "cache/"+currencyPair+"_Cache/secCache");
		std::future<std::vector<int>>   fDow = std::async(std::launch::async, LoadVectorCache<int>,      "cache/"+currencyPair+"_Cache/dowCache");

		std::vector<int>   myBarID = fBarID.get();
		std::vector<float> myOpen = fOpen.get();
		std::vector<float> myClose = fClose.get();
		std::vector<float> myHigh = fHigh.get();
		std::vector<float> myLow = fLow.get();
		std::vector<float> myAsk = fAsk.get();
		std::vector<float> myBid = fBid.get();
		std::vector<int>   myYear = fYear.get();
		std::vector<int>   myMon = fMon.get();
		std::vector<int>   myDay = fDay.get();
		std::vector<int>   myHour = fHour.get();
		std::vector<int>   myMin = fMin.get();
		std::vector<int>   mySec = fSec.get();
		std::vector<int>   myDow = fDow.get();
		*/

		//------------------------------------------------
		// CREATE BARS IF NECESSARY \/\/\/
		//------------------------------------------------
	 /*
		std::vector<float> myOpen;
		std::vector<float> myClose;
		std::vector<float> myHigh;
		std::vector<float> myLow;
		std::vector<int> myBarID;

		int minute = -1;
		int barID = -1;
		float HH = -99999.9f;
		float LL = 99999.9f;
		for (int i = 0; i < myBid.size(); ++i)
		{
			if (minute != myMin[i])
			{
				minute = myMin[i];
				myOpen.push_back(myBid[i]);
				if (i) {
					myClose.push_back(myBid[i - 1]);
					myHigh.push_back(HH);
					myLow.push_back(LL);
				}
				HH = -99999.9f;
				LL = 99999.9f;
				++barID;
			}

			if (myBid[i] > HH) HH = myBid[i];
			if (myBid[i] < LL) LL = myBid[i];
			myBarID.push_back(barID);
		}

		CacheVector(myBarID, "cache/" + currencyPair + "_Cache/barIDCache");
		CacheVector(myOpen, "cache/" + currencyPair + "_Cache/openCache");
		CacheVector(myClose, "cache/" + currencyPair + "_Cache/closeCache");
		CacheVector(myHigh, "cache/" + currencyPair + "_Cache/highCache");
		CacheVector(myLow, "cache/" + currencyPair + "_Cache/lowCache");

		Logger::ThrowBox("READY");


		System::Graphics::Dispatch(
			currencyPair,
			myAsk,
			myBid,
			myOpen,
			myClose,
			myHigh,
			myLow,
			myYear,
			myMon,
			myDay,
			myHour,
			myMin,
			mySec,
			myDow,
			myBarID
		);
		*/


		e.resize(1);

		//camera stuff
		e[0].AddComponent<Camera>();
		auto _camera = e[0].GetComponent<Camera>();
		_camera.renderTargetView = RTV::BackBuffer;
		_camera.depthStencilView = DSV::Default;
		_camera.position = { 0.0f,0.0f,-1.0f };
		_camera.rotation = { 0,0,0 };
		_camera.projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(90),
			(float)System::Graphics::GetWidth() / (float)System::Graphics::GetHeight(), 0.01f, 1000.0f);
		_camera.viewport = VP::Default;

		System::Graphics::AddCamera(e[0]);
		


		/*Hexagon h(6.0);
		for (auto& v : h.vertices)
			v.color = { .0f,.0f,1.0f,.5f };*/

			//e[0].AddComponent<Mesh>();
		//e[0].AddComponent<Renderer>();
		//e[0].AddComponent<Transform>(2);
		//
		//auto _rend = e[0].GetComponent<Renderer>();
		//_rend.vertexShader = "DefaultVS";
		//_rend.pixelShader = "DefaultPS";
		//_rend.textures.push_back("YellowTexture");

		/*static std::vector<DirectX::XMFLOAT4> vf;
		for (int i = 0; i < 4096; ++i)
		{
			vf.push_back(
				{ (float)(i % 2), (float)(i % 2), (float)(i % 2), 1.0f }
			);
		}

		std::vector<DirectX::XMFLOAT4> tex1 = { { 1.0f, 0.0f, 0.0f, 1.0f} };
		std::vector<DirectX::XMFLOAT4> tex2 = { { 1.0f, 1.0f, 0.0f, 1.0f} };
		System::Graphics::AddTexture<XMFLOAT4>(
			"RedTexture", tex1.data(), 64, 64,
			DXGI_FORMAT_R32G32B32A32_FLOAT
			);
		System::Graphics::AddTexture<XMFLOAT4>(
			"YellowTexture", tex2.data(), 64, 64,
			DXGI_FORMAT_R32G32B32A32_FLOAT
			);
		*/
		   
		Prism prism1(100);
		prism1.Rotate(90, 0, 0);

		Prism prism2(100);
		prism2.Translate(5, 5, 5);

		Prism prism3(100);
		prism3.Rotate(45, 0, 0);
		prism3.Translate(-5, -5, -5);
				
		e[0].AddComponent<Mesh>();
		e[0].AddComponent<Renderer>();
		auto _rend = e[0].GetComponent<Renderer>();
		_rend.vertexShader = "DefaultVS";
		_rend.pixelShader = "DefaultPS";
		e[0].AddComponent<Transform>();

		//std::vector<Geometry::Vertex> vtx = { Vertex(0,0,0), Vertex(0,1,0), Vertex(1,1,0) };
		//std::vector<unsigned int> idx = { 0,1,2 };
		//System::Graphics::AddModel(e[0], vtx, idx);
		System::Graphics::AddModel(e[0], prism1.vertices, prism1.indices);
		System::Graphics::AddModel(e[0], prism2.vertices, prism2.indices);
		System::Graphics::AddModel(e[0], prism3.vertices, prism3.indices);
	}

	void Engine::Run()
	{
		Time::Hourglass frameTime;
		while (ProcessMessages())
		{
			if (m_keyboard.IsKeyDown(VK_ESCAPE)) exit(0);
			frameTime.Start();

			CameraCode(10, 100);

			//System::Physics::Update();
			System::Graphics::Update();

			frameTime.End();
			Time::DeltaTime = frameTime.GetDelta();
			Time::FPS = frameTime.GetTick();
		}
	}

	void Engine::ShutDown()
	{
		System::Graphics::Exit();
		//System::Physics::Exit();
		CoUninitialize();
	}

	LRESULT Engine::WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
			OutputDebugStringA("RESIZE\n");
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}




	void Engine::CameraCode(float moveSpeed, float rotSpeed)
	{
		float cameraSpeed = moveSpeed;
		auto ev = m_keyboard.ReadEvent();
		if (m_keyboard.IsKeyDown('S')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, 0.0f, -cameraSpeed * (float)Time::DeltaTime }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('W')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, 0.0f, cameraSpeed * (float)Time::DeltaTime }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('Q')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ -cameraSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('E')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ cameraSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown(VK_SPACE)) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, cameraSpeed * (float)Time::DeltaTime, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('Z')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, -cameraSpeed * (float)Time::DeltaTime, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
			e[0].GetComponent<Camera>().position.x += _dir.x;
			e[0].GetComponent<Camera>().position.y += _dir.y;
			e[0].GetComponent<Camera>().position.z += _dir.z;
		}

		if (m_mouse.IsRightDown())
		{
			if (m_keyboard.IsKeyDown('A')) {
				XMFLOAT3 _dir;
				XMStoreFloat3(&_dir, XMVector3Transform({ -cameraSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
				e[0].GetComponent<Camera>().position.x += _dir.x;
				e[0].GetComponent<Camera>().position.y += _dir.y;
				e[0].GetComponent<Camera>().position.z += _dir.z;
			}
			if (m_keyboard.IsKeyDown('D')) {
				XMFLOAT3 _dir;
				XMStoreFloat3(&_dir, XMVector3Transform({ cameraSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, e[0].GetComponent<Camera>().rotationMatrix));
				e[0].GetComponent<Camera>().position.x += _dir.x;
				e[0].GetComponent<Camera>().position.y += _dir.y;
				e[0].GetComponent<Camera>().position.z += _dir.z;
			}
		}
		else
		{
			if (m_keyboard.IsKeyDown('A')) {
				e[0].GetComponent<Camera>().rotation.y -= rotSpeed * (float)Time::DeltaTime;
			}
			if (m_keyboard.IsKeyDown('D')) {
				e[0].GetComponent<Camera>().rotation.y += rotSpeed * (float)Time::DeltaTime;
			}
		}
	}

}