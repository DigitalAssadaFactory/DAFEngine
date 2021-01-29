#pragma once
#define NOMINMAX
#include <Windows.h>
#include <DAF_Utility.h>
#include <DAF_HID.h>
#include <memory>



namespace DAF
{

	class Window {
	public:
		Window();
		~Window();
		HWND InitWindow(const std::string& title, const std::string& className,
			const LONG& width, const LONG& height, const LONG& x, const LONG& y);
		bool ProcessMessages();
		LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		// WindowProcEx allows to separate custom msg handling code from defaults like keyboard and mouse input
		virtual inline LRESULT WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		std::string GetWindowTitle() const;
		std::string GetWindowClassName() const;
		HWND GetWindowHandle() const;
		HINSTANCE GetWindowInstance() const;
		LONG GetWindowWidth() const;
		LONG GetWindowHeight() const;
		LONG GetWindowPosX() const;
		LONG GetWindowPosY() const;
	protected:
		Keyboard        m_keyboard;
		Mouse           m_mouse;

		std::wstring    m_title;
		std::wstring    m_className;
		HWND            m_hWnd;
		HINSTANCE       m_hInstance;
		LONG            m_width;
		LONG            m_height;
		LONG            m_x;
		LONG            m_y;
	};

}