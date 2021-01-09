#include "Window.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace DAF
{

	Window::Window()
	{
		static bool raw_input_initialized = false;
		if (raw_input_initialized == false)
		{
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;

			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				HRESULT hresult = (HRESULT)GetLastError();
				LogError(hresult, "RegisterRawInputDevices failed.");
			}
			raw_input_initialized = true;
		}
	}

	LRESULT CALLBACK RedirectedProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		default:
			Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			return pWindow->WindowProc(hWnd, message, wParam, lParam);
		}
	}

	LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_NCCREATE)
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
			if (pWindow == 0)
				Logger::ThrowBox("WM_NCCREATE critical error.");
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(RedirectedProc));
			return pWindow->WindowProc(hWnd, message, wParam, lParam);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
		
	// ImGui was here
	LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
			return true;

		switch (message)
		{
		case WM_CHAR:
		{
			if (m_keyboard.IsCharAutorepeat())
				m_keyboard.InputChar(static_cast <unsigned char> (wParam));
			else if (!(lParam & 0x40000000))
				m_keyboard.InputChar(static_cast <unsigned char> (wParam));
			else
				return 0;
			break;
		}
		case WM_KEYDOWN:
		{
			if (m_keyboard.IsKeyAutorepeat())
				m_keyboard.Press(static_cast <unsigned char> (wParam));
			else if (!(lParam & 0x40000000))
				m_keyboard.Press(static_cast <unsigned char> (wParam));
			else
				return 0;
			break;
		}
		case WM_SYSKEYDOWN:
		{
			if (m_keyboard.IsKeyAutorepeat())
				m_keyboard.Press(static_cast <unsigned char> (wParam));
			else if (!(lParam & 0x40000000))
				m_keyboard.Press(static_cast <unsigned char> (wParam));
			else
				return 0;
			break;
		}
		case WM_KEYUP:
		{
			m_keyboard.Release(static_cast <unsigned char> (wParam));
			break;
		}
		case WM_MOUSEMOVE:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnMove(position.x, position.y);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnLeftDown(position.x, position.y);
			break;
		}
		case WM_LBUTTONUP:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnLeftUp(position.x, position.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnRightDown(position.x, position.y);
			break;
		}
		case WM_RBUTTONUP:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnRightUp(position.x, position.y);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnMidDown(position.x, position.y);
			break;
		}
		case WM_MBUTTONUP:
		{
			const POINTS position = MAKEPOINTS(lParam);
			m_mouse.OnMidUp(position.x, position.y);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const POINTS position = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				m_mouse.OnScrollUp(position.x, position.y);
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
				m_mouse.OnScrollDown(position.x, position.y);
			else
				return 0;
			break;
		}
		case WM_INPUT:
		{
			UINT dataSize;
			GetRawInputData(reinterpret_cast <HRAWINPUT> (lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

			if (dataSize > 0)
			{
				std::unique_ptr <BYTE[]> rawdata = std::make_unique <BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast <HRAWINPUT> (lParam), RID_INPUT, rawdata.get(),
					&dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					RAWINPUT* raw = reinterpret_cast <RAWINPUT*> (rawdata.get());
					if (raw->header.dwType == RIM_TYPEMOUSE)
					{
						m_mouse.OnRawMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_KILLFOCUS:
			m_keyboard.ClearState();
			break;
		default:
			return WindowProcEx(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	inline LRESULT Window::WindowProcEx(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	bool Window::ProcessMessages() {
		MSG msg = {};
		while (PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == 0 && !IsWindow(m_hWnd))
			return 0;
		return 1;
	}

	HWND Window::InitWindow(const std::string& title, const std::string& className,
		const LONG& width, const LONG& height, const LONG& x, const LONG& y)
	{
		m_title = Caster::Wstr(title);
		m_className = Caster::Wstr(className);
		m_width = width;
		m_height = height;
		m_x = x;
		m_y = y;

		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_OWNDC;
		wcex.lpfnWndProc = MainProc;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = 0; //(HICON)(LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_PNG1), IMAGE_ICON, 32, 32, 0));
		wcex.hCursor = LoadCursor(0, IDC_ARROW);
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = m_className.c_str();
		wcex.hIconSm = 0; //(HICON)(LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_PNG1), IMAGE_ICON, 16, 16, 0));


		if (!RegisterClassEx(&wcex))
			Logger::ThrowBox("WindowClassEx Registration Failed.");


		RECT rect = { 0,0, m_width, m_height };
		AdjustWindowRect(&rect, WS_OVERLAPPED, FALSE);
		m_hWnd = CreateWindowEx(
			0,
			m_className.c_str(),
			m_title.c_str(),
			WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST,
			m_x,
			m_y,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			m_hInstance,
			this
		);

		if (m_hWnd == 0)
			Logger::ThrowBox("Window Creation Failed.");

		return m_hWnd;
	}

	Window::~Window() {
		UnregisterClass(m_className.c_str(), m_hInstance);
	}


	//-------------------- Getters & Setters --------------------\\



	std::string Window::GetWindowTitle() const {
		return Caster::Str(m_title);
	}

	std::string Window::GetWindowClassName() const {
		return Caster::Str(m_className);
	}

	HWND Window::GetWindowHandle() const {
		return m_hWnd;
	}

	HINSTANCE Window::GetWindowInstance() const {
		return m_hInstance;
	}

	LONG Window::GetWindowWidth() const {
		return m_width;
	}

	LONG Window::GetWindowHeight() const {
		return m_height;
	}

	LONG Window::GetWindowPosX() const {
		return m_x;
	}

	LONG Window::GetWindowPosY() const {
		return m_y;
	}

}