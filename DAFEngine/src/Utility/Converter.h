#pragma once
#include <string>
#include <vector>
#include <comdef.h>
#include "Logger.h"
//#define BT_NO_SIMD_OPERATOR_OVERLOADS
//#include "../../inc/Bullet/btBulletCollisionCommon.h"
//#include "../../inc/Bullet/btBulletDynamicsCommon.h"
#include <DirectXMath.h>
#include <assimp/scene.h>


/*
template<typename T>
0auto& last(std::vector<T> vec)
{
	if (vec.size()) return vec[vec.size() - 1];
	else Logger::ThrowBox("Last failed. Vector has 0 elements.");
}
*/

namespace DAF
{

	struct To {
		static std::string String(int var);
		static std::string String(unsigned int var);
		static std::string String(float var);
		static std::string String(double var);

		static std::string String(const std::wstring& var);
		static std::string String(const aiTextureType type);

		static std::wstring WString(const char* var);
		static std::wstring WString(const short& var);
		static std::wstring WString(const int& var);
		static std::wstring WString(const unsigned int& var);
		static std::wstring WString(const long& var);
		static std::wstring WString(const float& var);
		static std::wstring WString(const double& var);
		//static std::wstring Wstring(const TCHAR * var);
		static std::wstring WString(const std::string& var);

		template<typename T>
		static std::string CSV(const std::vector<T>& values, const std::string& separator)
		{
			std::string out = "";
			for (int i = 0; i < values.size() - 1; ++i)
				out += To::String(values[i]) + separator;
			out += To::String(values[values.size() - 1]);
			return out;
		}
		static std::string CSV(const DirectX::XMFLOAT2& value, const std::string& separator);
		static std::string CSV(const DirectX::XMFLOAT3& value, const std::string& separator);
		static std::string CSV(const DirectX::XMFLOAT4& value, const std::string& separator);

	};

}