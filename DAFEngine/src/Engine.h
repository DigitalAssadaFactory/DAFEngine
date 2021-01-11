#pragma once
#include <random>
#include <future>
#include "ECS.h"
#include "Window.h"
#include "JobSystem.h"
#include "Geometry.h"
#include "Graphics.h"




namespace DAF
{

	class Engine : public Window
	{
	public:
		Engine(std::string title, size_t width, size_t height);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine& operator=(Engine&&) = delete;

		void StartUp();
		void Run();
		void ShutDown();

	private:
		void CameraCode(float moveSpeed, float rotSpeed);

		std::vector<ECS::Entity> e;
		LRESULT     WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		HINSTANCE   m_hInstance;
	};

}