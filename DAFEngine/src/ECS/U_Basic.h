#pragma once
#include "ECSCore.h"
#include <DirectXMath.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <filesystem>



namespace DirectX {
	bool operator==(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	bool operator!=(const XMFLOAT3& lhs, const XMFLOAT3& rhs);

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT2& rhs);

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	
	
	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT3& rhs);

}
