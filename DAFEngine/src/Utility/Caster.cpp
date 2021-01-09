#include "Caster.h"



namespace DAF
{

	//-------------------- STD::STRING --------------------\\

	std::string Caster::Str(const std::wstring& var) {
		std::string s(var.begin(), var.end());
		return s;
	}

	std::string Caster::Str(const aiTextureType type)
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

	std::wstring Caster::Wstr(const char* var) {
		std::string s(var);
		return std::wstring(s.begin(), s.end());
	}
	std::wstring Caster::Wstr(const short& var) {
		return std::to_wstring(var);
	}
	std::wstring Caster::Wstr(const int& var) {
		return std::to_wstring(var);
	}
	std::wstring Caster::Wstr(const unsigned int& var) {
		return std::to_wstring(var);
	}
	std::wstring Caster::Wstr(const long& var) {
		return std::to_wstring(var);
	}
	std::wstring Caster::Wstr(const float& var) {
		return std::to_wstring(var);
	}
	std::wstring Caster::Wstr(const double& var) {
		return std::to_wstring(var);
	}
	/*std::wstring Caster::Wstr(const TCHAR * var) {
		return std::wstring(var);
	}*/
	std::wstring Caster::Wstr(const std::string& var) {
		return std::wstring(var.begin(), var.end());
	}

}