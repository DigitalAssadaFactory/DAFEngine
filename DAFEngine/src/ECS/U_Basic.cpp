#include "U_Basic.h"



namespace DirectX {

	bool operator==(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}
	bool operator!=(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z + rhs.z;
		_output.w = lhs.w + rhs.w;
		return _output;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z - rhs.z;
		_output.w = lhs.w - rhs.w;
		return _output;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z + rhs.z;
		_output.w = lhs.w;
		return _output;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z - rhs.z;
		_output.w = lhs.w;
		return _output;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z;
		_output.w = lhs.w;
		return _output;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z;
		_output.w = lhs.w;
		return _output;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z + rhs.z;
		return _output;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z - rhs.z;
		return _output;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z + rhs.z;
		return _output;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z - rhs.z;
		return _output;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		_output.z = lhs.z;
		return _output;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		_output.z = lhs.z;
		return _output;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		return _output;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		return _output;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		return _output;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		return _output;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x + rhs.x;
		_output.y = lhs.y + rhs.y;
		return _output;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 _output;
		_output.x = lhs.x - rhs.x;
		_output.y = lhs.y - rhs.y;
		return _output;
	}

}
