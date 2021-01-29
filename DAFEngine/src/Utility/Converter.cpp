#include "Converter.h"



namespace DAF
{

	//-------------------- STD::STRING --------------------\\

	std::string To::String(int var)
	{
		return std::to_string(var);
	}

	std::string To::String(unsigned int var)
	{
		return std::to_string(var);
	}

	std::string To::String(float var)
	{
		return std::to_string(var);
	}

	std::string To::String(double var)
	{
		return std::to_string(var);
	}

	std::string To::String(const std::wstring& var) {
		std::string s(var.begin(), var.end());
		return s;
	}

	std::string To::String(const aiTextureType type)
	{
		switch (type)
		{
		case aiTextureType_DIFFUSE: return "Diffuse";
		case aiTextureType_DIFFUSE_ROUGHNESS: return "DiffuseRoughness";
		case aiTextureType_AMBIENT: return "Ambient";
		case aiTextureType_AMBIENT_OCCLUSION: return "AmbientOcclusion";
		case aiTextureType_BASE_COLOR: return "BaseColor";
		case aiTextureType_DISPLACEMENT: return "Displacement";
		case aiTextureType_EMISSIVE: return "Emissive";
		case aiTextureType_EMISSION_COLOR: return "EmissiveColor";
		case aiTextureType_HEIGHT: return "Height";
		case aiTextureType_LIGHTMAP: return "Lightmap";
		case aiTextureType_METALNESS: return "Metalness";
		case aiTextureType_NORMALS: return "Normals";
		case aiTextureType_NORMAL_CAMERA: return "NormalCamera";
		case aiTextureType_OPACITY: return "Opacity";
		case aiTextureType_REFLECTION: return "Reflection";
		case aiTextureType_SHININESS: return "Shininess";
		case aiTextureType_SPECULAR: return "Specular";
		case aiTextureType_NONE: return "None";
		case aiTextureType_UNKNOWN: return "";
		default: return "";
		}
	}



	//-------------------- STD::WSTRING --------------------\\

	std::wstring To::WString(const char* var) {
		std::string s(var);
		return std::wstring(s.begin(), s.end());
	}
	std::wstring To::WString(const short& var) {
		return std::to_wstring(var);
	}
	std::wstring To::WString(const int& var) {
		return std::to_wstring(var);
	}
	std::wstring To::WString(const unsigned int& var) {
		return std::to_wstring(var);
	}
	std::wstring To::WString(const long& var) {
		return std::to_wstring(var);
	}
	std::wstring To::WString(const float& var) {
		return std::to_wstring(var);
	}
	std::wstring To::WString(const double& var) {
		return std::to_wstring(var);
	}
	/*std::wstring To::WString(const TCHAR * var) {
		return std::wstring(var);
	}*/
	std::wstring To::WString(const std::string& var) {
		return std::wstring(var.begin(), var.end());
	}

	//-------------------- Coma Separated Values --------------------\\

	std::string To::CSV(const DirectX::XMFLOAT2& value, const std::string& separator)
	{
		return std::to_string(value.x)
			+ separator
			+ std::to_string(value.y);
	}

	std::string To::CSV(const DirectX::XMFLOAT3& value, const std::string& separator)
	{
		return std::to_string(value.x)
			+ separator
			+ std::to_string(value.y)
			+ separator
			+ std::to_string(value.z);
	}

	std::string To::CSV(const DirectX::XMFLOAT4& value, const std::string& separator)
	{
		return std::to_string(value.x)
			+ separator
			+ std::to_string(value.y)
			+ separator
			+ std::to_string(value.z)
			+ separator
			+ std::to_string(value.w);
	}



}