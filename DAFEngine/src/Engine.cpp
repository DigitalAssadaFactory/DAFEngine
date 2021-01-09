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
		   
		Polygon h(8);
		e[0].AddComponent<Mesh>();
		e[0].AddComponent<Renderer>();
		auto _rend = e[0].GetComponent<Renderer>();
		_rend.vertexShader = "DefaultVS";
		_rend.pixelShader = "DefaultPS";
		//_rend.textures.push_back("YellowTexture");
		e[0].AddComponent<Transform>();
				

		System::Graphics::AddModel(e[0], h.vertices, h.indices);



		//System::Graphics::ExtractTextures("res/Model/Samples/dodge_challenger.fbx");

		/*std::string outstring = "";

		for(int i = 0; i < Texture2D::name.size(); ++i)
			outstring += Texture2D::name[i] + "\t" + Texture2D::storageType[i] +  "\n";

		Logger::ThrowBox(outstring);*/

		//_rend.textures.push_back("orange.fbxDiffuse");

		/*float step = 0.0f;
		float stepZ = 0.0f;
		for (int i = 0; i < 1; ++i)
		{
			if (i % 10 == 0) step += 20.0f;
			if (i % 100 == 0) step = 0.0f;
			if (i % 1000 == 0) stepZ += 20.0f;

			auto _tra = e[0].GetComponent<Transform>(i);
			_tra.position.x = 15 * (i % 100) - 15 * 50 + step;

			_tra.position.z = 15 * floor(i / 100) + stepZ;
		}

		System::Graphics::LoadMesh(e[0], "res/Model/Samples/dodge_challenger.fbx");
		//System::Graphics::LoadMesh(e[0], "res/Model/Human.obj");

		System::Graphics::AddModel(e[0]);

		/*
		for (int i = 0; i < 14; ++i)
		{
			auto _rend = e[0].GetComponent<Renderer>(i);
			_rend.vertexShader = "DefaultVS";
			_rend.pixelShader = "DefaultPS";
		}

		auto t0 = e[0].GetComponent<Transform>(0);
		auto t1 = e[0].GetComponent<Transform>(1);
		auto t2 = e[0].GetComponent<Transform>(2);
		auto t3 = e[0].GetComponent<Transform>(3);
		auto t4 = e[0].GetComponent<Transform>(4);
		auto t5 = e[0].GetComponent<Transform>(5);
		auto t6 = e[0].GetComponent<Transform>(6);
		auto t7 = e[0].GetComponent<Transform>(7);
		auto t8 = e[0].GetComponent<Transform>(8);
		auto t9 = e[0].GetComponent<Transform>(9);
		auto t10 = e[0].GetComponent<Transform>(10);
		auto t11 = e[0].GetComponent<Transform>(11);
		auto t12 = e[0].GetComponent<Transform>(12);
		auto t13 = e[0].GetComponent<Transform>(13);

		t0.position = { -5.0f, 5.0f, 5.0f };
		t1.position = { 5.0f, 5.0f, 5.0f };
		t2.position = { -5.0f, 5.0f, -5.0f };
		t3.position = { 5.0f, 5.0f, -5.0f };
		t4.position = { -5.0f, -5.0f, 5.0f };
		t5.position = { 5.0f, -5.0f, 5.0f };
		t6.position = { -5.0f, -5.0f, -5.0f };
		t7.position = { 5.0f, -5.0f, -5.0f };

		float sqr = 8.5f;
		t8.position = {0.0f, 0.0f, sqr};
		t9.position = {sqr, 0.0f, 0.0f};
		t10.position = {0.0f, 0.0f, -sqr};
		t11.position = {-sqr, 0.0f, 0.0f};
		t12.position = {0.0f, sqr, 0.0f};
		t13.position = {0.0f, -sqr, 0.0f};

		t0.rotation = { -45,-45,0 };
		t1.rotation = { -45,45,0 };
		t2.rotation = { 45,45,0 };
		t3.rotation = { 45,-45,0 };
		t4.rotation = { 45,-45,0 };
		t5.rotation = { 45,45,0 };
		t6.rotation = { -45,45,0 };
		t7.rotation = { -45,-45,0 };

		t8.rotation = {0,0,45};
		t9.rotation = {0, 90,45 };
		t10.rotation ={0,0,45};
		t11.rotation ={0,90,45};
		t12.rotation = { 90,0,45 };
		t13.rotation ={90,0,45};

		for (int i = 0; i < 8; ++i)
			System::Graphics::AddModel(e[0], h.vertices, h.indices, i);

		for (int i = 7; i < 14; ++i)
			System::Graphics::AddModel(e[0], q.vertices, q.indices, i);
		*/
	}

	void Engine::Run()
	{
		Time::Hourglass frameTime;
		while (ProcessMessages())
		{
			if (m_keyboard.IsKeyDown(VK_ESCAPE)) exit(0);
			frameTime.Start();

			CameraCode(10, 30);

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


	/*void Engine::StockConfig(const std::string& currencyPair, float minProfit)
	{
		DYNAMIC_ARRAY_04(int) aSprint = DYNAMIC_ARRAY_04_INIT(int, 10, 21, 7, 21);

		//           std::string vsize = std::to_string(aSprint.size()) + "\n" +
		//           	std::to_string(aSprint[0].size()) + "\n" +
		//           	std::to_string(aSprint[0][0].size()) + "\n" +
		//           	std::to_string(aSprint[0][0][0].size());
		//           Logger::ThrowBox(vsize);
		//           
		//           std::vector < std::vector<std::vector<std::vector<int>>>> aSprint;
		//           
		//           aSprint.resize(9);
		//           for (auto& x : aSprint)
		//           	x.resize(21);
		//           
		//           for (auto& x : aSprint)
		//           	for (auto& y : x)
		//           		y.resize(7);
		//           
		//           for (auto& x : aSprint)
		//           	for (auto& y : x)
		//           		for (auto& z : y)
		//           			z.resize(21);
		//           


		for (auto& x : aSprint)
			for (auto& y : x)
				for (auto& z : y)
					for (auto& w : z)
						w = 0;

		std::fstream filePreinit;
		filePreinit.open("ePREINIT.mqh", std::ios::out);
		std::string e_preinit = "";

		std::fstream fileConfig;
		fileConfig.open("eCONFIG.mqh", std::ios::out);
		std::string e_config = "";

		std::fstream fileMacro;
		fileMacro.open("eMACRO.mqh", std::ios::out);
		std::string e_macro = "";

		std::fstream fileLoop;
		fileLoop.open("eLOOP.mqh", std::ios::out);
		std::string e_loop = "for (int i = 0; i < 21 && !m_order.IsOpen(); ++i)\n{\n";



		for (int f = 9; f > 0; --f)
		{
			std::vector<MyResultPrint> out = LoadVectorCache<MyResultPrint>("OUTPUT/" + currencyPair + "/FINAL_RESULT_CACHE_" + std::to_string(f));
			std::string config = "config" + std::to_string(f);

			float t_profit = 0.0f;
			float t_loss = 0.0f;
			int t_counter = 0;
			int t_trades = 0;
			for (const auto& a : out)
			{
				if (a.profit > 0.0007f && a.loss == 0.0f && a.maxLifetime < a.__range * 2)
				{
					if (f == 9 || (f != 9 && aSprint[f + 1][a.__range][a.__huge][a.__aratio] != 108))
					{
						aSprint[f][a.__range][a.__huge][a.__aratio] = 108;
					}

					t_profit += a.profit * 1000;
					t_loss += a.loss * 1000;
					t_trades += a.tradeCount;
					++t_counter;
				}
			}
			//--------------------------------
			//          Logger::ThrowBox(
			//          	"Profit : " + std::to_string(t_profit) +
			//          	"\nLoss : " + std::to_string(t_loss) +
			//          	"\nTrades : " + std::to_string(t_trades) +
			//          	"\nCount : " + std::to_string(t_counter)
			//          );
			//--------------------------------
			//          std::string sprint = "";
			//          for (auto& i : aSprint[0])
			//          {
			//          	for (auto& j : i)
			//          	{
			//          		if (j == 108)
			//          			sprint += "X";
			//          		else sprint += "+";
			//          	}
			//          	sprint += "\n";
			//          }
			//          Logger::ThrowBox(sprint);
			//--------------------------------

			DYNAMIC_ARRAY_02(LargestRect) vRect = DYNAMIC_ARRAY_02_INIT(LargestRect, 21, 0);

			int magicX = 0;
			bool isDirty = true;
			while (isDirty)
			{
				++magicX;
				isDirty = false;
				for (int range_ = 0; range_ < 21; ++range_)
					for (int huge_ = 0; huge_ < 7; ++huge_)
						for (int aratio_ = 0; aratio_ < 21; ++aratio_)
						{
							int aratioChain = -1;
							int hugeChain = -1;

							for (int x = aratio_; x < 21 && aSprint[f][range_][huge_][x] == 108; ++x)
							{
								++aratioChain;
							}
							for (int y = huge_; y < 7 && aSprint[f][range_][y][aratio_] == 108; ++y)
							{
								++hugeChain;
							}

							if (aratioChain < 0 && hugeChain < 0) continue;

							isDirty = true;
							if (aratioChain > hugeChain)
							{
								auto rect = Stock::Rec_LargestRect(aSprint[f][range_],
									{ aratio_, huge_, aratio_ + aratioChain, huge_ },
									ScanType::horizontal);

								vRect[range_].push_back(rect);

								for (int x = rect.x0; x <= rect.x1; ++x)
									for (int y = rect.y0; y <= rect.y1; ++y)
										aSprint[f][range_][y][x] = 0;
							}
							else
							{
								auto rect = Stock::Rec_LargestRect(aSprint[f][range_],
									{ aratio_,huge_, aratio_, huge_ + hugeChain },
									ScanType::vertical);

								vRect[range_].push_back(rect);

								for (int x = rect.x0; x <= rect.x1; ++x)
									for (int y = rect.y0; y <= rect.y1; ++y)
										aSprint[f][range_][y][x] = 0;
							}

						}
			}

			//--------------------------------------------------
			//       int sum = 0;
			//       for (auto& r : vRect)
			//       	for (auto& x : r)
			//       		++sum;
			//       
			//       Logger::ThrowBox("sum = " + std::to_string(sum));
			
			int maxConfig = 0;
			for (auto& r : vRect)
				if (r.size() > maxConfig) maxConfig = r.size();

			//Logger::ThrowBox(std::to_string(maxConfig));
			//--------------------------------------------------

			if (maxConfig != 0)
			{
				e_macro += "#define MAX_CONFIG_" + std::to_string(f) + " " + std::to_string(maxConfig + 1) + "\nint " +
					config + "[21][" + std::to_string(maxConfig + 1) + "];\n";
			}

			for (int i = 0; i < vRect.size(); ++i)
			{
				std::string temp_mql = "";

				temp_mql += config + "[" + std::to_string(i) + "][0] " +
					"= VShape( 0, " + std::to_string(10 + i) + ", 0.05f, 0.3f, 0.5f, 1.0f);\n";

				temp_mql += "if( " + config + "[" + std::to_string(i) + "][0] > 0 )\n{\n";

				int valid_counted = 0;
				for (int j = 0; j < maxConfig; ++j)
				{
					if (j < vRect[i].size())
					{
						float areaMin = 0.5f + vRect[i][j].x0 * 0.1f;
						float areaMax = 0.5f + vRect[i][j].x1 * 0.1f + 0.1f;
						float hugeMin = 0.3f + vRect[i][j].y0 * 0.1f;
						float hugeMax = 0.3f + vRect[i][j].y1 * 0.1f + 0.1f;

						temp_mql += "\t" + config + "[" + std::to_string(i) + "][" + std::to_string(j + 1) + "] " +
							"= AShape( 0, " + std::to_string(10 + i) + ", " + std::to_string(areaMin) + ", " +
							std::to_string(areaMax) + ", " + std::to_string(hugeMin) + ", " + std::to_string(hugeMax) + " );\n";

						++valid_counted;
					}
				}
				temp_mql += "}\n";

				if (valid_counted > 0) e_config += temp_mql;
			}


			for (int i = 0; i < vRect.size(); ++i)
			{
				for (int j = 0; j < maxConfig; ++j)
				{
					if (j >= vRect[i].size())
					{
						e_preinit += config + "[" + std::to_string(i) + "][" + std::to_string(j + 1) + "] = -7;\n";
					}
				}
			}

			if (maxConfig != 0)
			{
				e_loop += "\tif ( " + config + "[i][0] != 0 )\n\t{\n" +
					"\t\tfor (int j = 1; j < MAX_CONFIG_" + std::to_string(f) + " && " + config + "[i][j] != -7; ++j)\n\t\t{\n" +
					"\t\t\tif ( ////////////////////////////\n\t\t\t\t(" + config + "[i][j] == BUY_TOR && " +
					config + "[i][0] == BUY_GREEN)\n\t\t\t\t||\n\t\t\t\t(" + config + "[i][j] == BUY_ENG && " +
					config + "[i][0] == BUY_RED)\n\t\t\t)////////////////////////////\n\t\t\t{\n\t\t\t" +
					"\tif ( m_useMaxSize ) { Buy( Symbol(), MaxLots(), i, " + std::to_string(f) + " ); }" +
					"\n\t\t\t\telse { Buy( Symbol(), m_size, i, " + std::to_string(f) + " ); }\n\t\t\t}\n" +
					"\t\t\telse if ( ////////////////////////////\n\t\t\t\t(" + config + "[i][j] == SELL_TOR && " +
					config + "[i][0] == SELL_RED)\n\t\t\t\t||\n\t\t\t\t(" + config + "[i][j] == SELL_ENG && " +
					config + "[i][0] == SELL_GREEN)\n\t\t\t)////////////////////////////\n\t\t\t{\n\t\t\t\t" +
					"if ( m_useMaxSize ) { Sell( Symbol(), MaxLots(), i, " + std::to_string(f) + " ); }\n\t\t\t\t" +
					"else { Sell( Symbol(), m_size,  i, " + std::to_string(f) + " ); }\n\t\t\t}\n\t\t}\n\t}\n\n\n";
			}
		}
		e_loop += "}";


		fileConfig.write(e_config.c_str(), e_config.length());
		fileConfig.close();

		filePreinit.write(e_preinit.c_str(), e_preinit.length());
		filePreinit.close();

		fileMacro.write(e_macro.c_str(), e_macro.length());
		fileMacro.clear();

		fileLoop.write(e_loop.c_str(), e_loop.length());
		fileLoop.clear();

		Logger::ThrowBox("Task completed");
	}*/

	/*void Engine::Trash() {

		std::vector<int>            myCandle;
		std::vector<float>          myAsk;
		std::vector<float>          myBid;
		static Stock::TickLoader    loader;


		{
			//---------------------------------------------------
			//        FILE_NAMES      FUTURES      TICK_DATA
			//---------------------------------------------------
			std::string currencyPair = "AUDCAD";
			std::vector<std::string> fileNameList = Stock::MakePathList(currencyPair, 2015, 2019);
			std::vector<std::future<std::vector<Stock::TickData> > > _futures;
			_futures.resize(fileNameList.size());
			std::vector<std::vector<Stock::TickData>> _tickData;
			_tickData.resize(fileNameList.size());

			//---------------------------------------------------
			//           Loading Ticks from disc
			//---------------------------------------------------
			for (size_t i = 0; i < fileNameList.size(); ++i)
				_futures[i] = std::async(std::launch::async, LoadVectorCache<Stock::TickData>, "res/data/" + currencyPair + "/" + fileNameList[i]);

			for (size_t i = 0; i < fileNameList.size(); ++i)
				_tickData[i] = _futures[i].get();

			//---------------------------------------------------
			//                 Merging months
			//---------------------------------------------------
			std::vector<Stock::TickData> _convergence;
			for (int i = 0; i < _tickData.size(); ++i) {
				_convergence.reserve(_tickData[i].size());
				_convergence.insert(_convergence.end(), _tickData[i].begin(), _tickData[i].end());
			}
			loader.Set("GBPJPY", _convergence);



			std::future<std::vector<float>> fAsk = std::async(std::launch::async, Stock::MergeAsk, _convergence);
			std::future<std::vector<float>> fBid = std::async(std::launch::async, Stock::MergeBid, _convergence);
			std::future<std::vector<int>>   fYear = std::async(std::launch::async, Stock::MergeYear, _convergence);
			std::future<std::vector<int>>   fMon = std::async(std::launch::async, Stock::MergeMon, _convergence);
			std::future<std::vector<int>>   fDay = std::async(std::launch::async, Stock::MergeDay, _convergence);
			std::future<std::vector<int>>   fHour = std::async(std::launch::async, Stock::MergeHour, _convergence);
			std::future<std::vector<int>>   fMin = std::async(std::launch::async, Stock::MergeMin, _convergence);
			std::future<std::vector<int>>   fSec = std::async(std::launch::async, Stock::MergeSec, _convergence);
			std::future<std::vector<int>>   fDow = std::async(std::launch::async, Stock::MergeDow, _convergence);

			myAsk = fAsk.get();
			myBid = fBid.get();
			std::vector<int> myYear = fYear.get();
			std::vector<int> myMon = fMon.get();
			std::vector<int> myDay = fDay.get();
			std::vector<int> myHour = fHour.get();
			std::vector<int> myMin = fMin.get();
			std::vector<int> mySec = fSec.get();
			std::vector<int> myDow = fDow.get();

			CacheVector(myYear, "yearCache");
			CacheVector(myMon, "monCache");
			CacheVector(myDay, "dayCache");
			CacheVector(myHour, "hourCache");
			CacheVector(mySec, "secCache");
			CacheVector(myDow, "dowCache");

			Logger::ThrowBox("EXIT");

			myCandle = Stock::MergeBarID(_convergence, 1);
		}

		//---------------------------------------------------
		//                 Making Chart
		//---------------------------------------------------
		static Stock::Chart chart("GBPJPY", loader["GBPJPY"], 1);
	}*/

}