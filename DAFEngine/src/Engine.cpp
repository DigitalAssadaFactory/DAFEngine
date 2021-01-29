#include "Engine.h"
#include "Game/CageWall.h"


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
		e.resize(2);

		//camera stuff
		e[0].AddComponent<Camera>();
		auto _camera = e[0].GetComponent<Camera>();
		_camera.renderTargetView = RTV::BackBuffer;
		_camera.depthStencilView = DSV::Default;
		_camera.position = { 0.0f,0.0f,-1.0f };
		_camera.rotation = { 0,0,0 };
		_camera.projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60),
			(float)System::Graphics::GetWidth() / (float)System::Graphics::GetHeight(), 0.01f, 1000.0f);
		_camera.viewport = VP::Default;
		System::Graphics::AddCamera(e[0]);

		e[0].AddComponent<Mesh>();
		e[0].AddComponent<Renderer>();
		auto _rend = e[0].GetComponent<Renderer>();
		_rend.vertexShader = "DefaultVS";
		_rend.pixelShader = "DefaultPS";
		_rend.textures.push_back("NormalMap");
		e[0].AddComponent<Transform>();

		e[1].AddComponent<Light>(2);
		e[1].AddComponent<Transform>();
		auto l1 = e[1].GetComponent<Light>();
		auto l2 = e[1].GetComponent<Light>(1);
		l1.position = { -100,100,-1000 };
		l1.color = { 0,0,1 };
		l1.intensity = .5f;
		l1.type = LightType::Directional;
		l2.position = { 100,-100,0 };
		l2.color = { 1,0,0 };
		l2.intensity = 1.0f;
		l2.type = LightType::Directional;

		Prism prism(4, 2, 2);

		std::bitset<27> config("000000000000000000110100000");
		std::bitset<5> type("11111");
		UniversalNode unode(config, type);

		std::vector<Vertex> vts = unode.GetVertices();
		std::vector<unsigned int> ids = unode.GetIndices();

		System::Graphics::AddModel(e[0], vts, ids);
		System::Graphics::AddModel(e[0], prism.vertices, prism.indices);
		System::Graphics::AddLight(e[1]);
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
		{
			System::Graphics::Resize();
			return 0;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}




	void Engine::CameraCode(float moveSpeed, float rotSpeed)
	{
		static Camera::Wrapper camera = e[0].GetComponent<Camera>();
		auto kEvent = m_keyboard.ReadEvent();
		auto mEvent = m_mouse.ReadEvent();

		if (kEvent.GetKeyCode() == VK_F1)
		{
			System::Graphics::Fullscreen();
		}

		if (m_keyboard.IsKeyDown('S')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, 0.0f, -moveSpeed * (float)Time::DeltaTime }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('W')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, 0.0f, moveSpeed * (float)Time::DeltaTime }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('Q')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ -moveSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('E')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ moveSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown(VK_SPACE)) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, moveSpeed * (float)Time::DeltaTime, 0.0f }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}
		if (m_keyboard.IsKeyDown('Z')) {
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Transform({ 0.0f, -moveSpeed * (float)Time::DeltaTime, 0.0f }, camera.rotationMatrix));
			camera.position.x += _dir.x;
			camera.position.y += _dir.y;
			camera.position.z += _dir.z;
		}

		if (m_mouse.IsRightDown())
		{
			if (m_keyboard.IsKeyDown('A')) {
				XMFLOAT3 _dir;
				XMStoreFloat3(&_dir, XMVector3Transform({ -moveSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, camera.rotationMatrix));
				camera.position.x += _dir.x;
				camera.position.y += _dir.y;
				camera.position.z += _dir.z;
			}
			if (m_keyboard.IsKeyDown('D')) {
				XMFLOAT3 _dir;
				XMStoreFloat3(&_dir, XMVector3Transform({ moveSpeed * (float)Time::DeltaTime, 0.0f, 0.0f }, camera.rotationMatrix));
				camera.position.x += _dir.x;
				camera.position.y += _dir.y;
				camera.position.z += _dir.z;
			}

			camera.rotation.y += 10 * m_mouse.GetRawX() * rotSpeed * (float)Time::DeltaTime;
			camera.rotation.x += 10 * m_mouse.GetRawY() * rotSpeed * (float)Time::DeltaTime;

		}
		else
		{
			if (m_keyboard.IsKeyDown('A'))
				camera.rotation.y -= rotSpeed * (float)Time::DeltaTime;
			if (m_keyboard.IsKeyDown('D'))
				camera.rotation.y += rotSpeed * (float)Time::DeltaTime;
		}
		m_mouse.ResetRaw();
	}

}