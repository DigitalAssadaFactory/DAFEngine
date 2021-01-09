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

	class Caster {
	public:
		static std::string Str(const std::wstring& var);
		static std::string Str(const aiTextureType type);

		static std::wstring Wstr(const char* var);
		static std::wstring Wstr(const short& var);
		static std::wstring Wstr(const int& var);
		static std::wstring Wstr(const unsigned int& var);
		static std::wstring Wstr(const long& var);
		static std::wstring Wstr(const float& var);
		static std::wstring Wstr(const double& var);
		//static std::wstring Wstr(const TCHAR * var);
		static std::wstring Wstr(const std::string& var);
	};

}