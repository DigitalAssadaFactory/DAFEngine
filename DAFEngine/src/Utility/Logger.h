#pragma once
#include <Windows.h>
#include <typeinfo>
#include <DirectXCollision.h>
#include "Caster.h"


namespace DAF
{

	class Logger
	{
	public:
		static void ThrowBox(const std::string& message);
		static void ThrowBox(const std::wstring& message);
		static void ThrowBox(HRESULT hr, const char* message);
		static void ThrowBox(HRESULT hr, const char* message, const char* function, const char* file, int line);
		static void ThrowBox(HRESULT hr, const wchar_t* message, const char* function, const char* file, int line);
		static void ThrowBox(HRESULT hr, const std::wstring& message, const char* function, const char* file, int line);

#define LogError(hr, msg)\
		Logger::ThrowBox(hr, msg, __FUNCTION__, __FILE__, __LINE__)

		static void Log(const std::string& msg);
		static void Log(const float& f);
		static void Log(const DirectX::XMFLOAT3& f3);
		static void Log(const DirectX::XMFLOAT4& f4);
		//static void Log(const btVector3 & v3);
	};

}