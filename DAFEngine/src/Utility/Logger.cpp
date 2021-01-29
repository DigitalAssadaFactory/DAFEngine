#include "Logger.h"


namespace DAF
{

	void Logger::ThrowBox(const std::string& message)
	{
		MessageBoxW(NULL, To::WString(message).c_str(), L"Error", MB_ICONERROR);
		exit(0);
	}

	void Logger::ThrowBox(const std::wstring& message)
	{
		MessageBoxW(NULL, message.c_str(), L"Error", MB_ICONERROR);
		exit(0);
	}

	void Logger::ThrowBox(HRESULT hr, const char* message)
	{
		if (FAILED(hr))
		{
			_com_error e(hr);
			std::wstring msg(L"Error : " + std::wstring(e.ErrorMessage()) + L"\n"
				+ L"Note : " + To::WString(message));

			MessageBoxW(NULL, msg.c_str(), L"Error", MB_ICONERROR);
			exit(0);
		}
	}

	void Logger::ThrowBox(HRESULT hr, const char* message, const char* function, const char* file, int line)
	{
		if (FAILED(hr))
		{
			_com_error e(hr);
			std::wstring msg(L"Error : " + std::wstring(e.ErrorMessage()) + L"\n"
				+ L"Function : " + To::WString(function) + L"\n"
				+ L"File : " + To::WString(file) + L"\n"
				+ L"Line : " + To::WString(line) + L"\n"
				+ L"Note : " + To::WString(message));

			MessageBoxW(NULL, msg.c_str(), L"Error", MB_ICONERROR);
			exit(0);
		}
	}

	void Logger::ThrowBox(HRESULT hr, const wchar_t* message, const char* function, const char* file, int line)
	{
		if (FAILED(hr))
		{
			_com_error e(hr);
			std::wstring msg(L"Error : " + std::wstring(e.ErrorMessage()) + L"\n"
				+ L"Function : " + To::WString(function) + L"\n"
				+ L"File : " + To::WString(file) + L"\n"
				+ L"Line : " + To::WString(line) + L"\n"
				+ L"Note : " + std::wstring(message));

			MessageBoxW(NULL, msg.c_str(), L"Error", MB_ICONERROR);
			exit(0);
		}
	}

	void Logger::ThrowBox(HRESULT hr, const std::wstring& message, const char* function, const char* file, int line)
	{
		if (FAILED(hr))
		{
			_com_error e(hr);
			std::wstring msg(L"Error : " + std::wstring(e.ErrorMessage()) + L"\n"
				+ L"Function : " + To::WString(function) + L"\n"
				+ L"File : " + To::WString(file) + L"\n"
				+ L"Line : " + To::WString(line) + L"\n"
				+ L"Note : " + message);

			MessageBoxW(NULL, msg.c_str(), L"Error", MB_ICONERROR);
			exit(0);
		}
	}


	void Logger::Log(const std::string& msg)
	{
		OutputDebugStringA(msg.c_str());
	}

	void Logger::Log(const float& f)
	{
		std::wstring ws(To::WString(f) + L"\n");
		OutputDebugString(ws.c_str());
	}

	void Logger::Log(const DirectX::XMFLOAT3& f3)
	{
		std::wstring ws(To::WString(f3.x) + L" | " + To::WString(f3.y) + L" | " + To::WString(f3.z) + L"\n");
		OutputDebugString(ws.c_str());
	}

	void Logger::Log(const DirectX::XMFLOAT4& f4)
	{
		std::wstring ws(To::WString(f4.x) + L" | " + To::WString(f4.y) + L" | " + To::WString(f4.z) + L" | " + To::WString(f4.w) + L"\n");
		OutputDebugString(ws.c_str());
	}

	/*void Logger::Log(const btVector3 & v3)
	{
		std::wstring ws(To::WString(v3.getX()) + L" | " + To::WString(v3.getY()) + L" | " + To::WString(v3.getZ()) + L"\n");
		OutputDebugString(ws.c_str());
	}*/

}