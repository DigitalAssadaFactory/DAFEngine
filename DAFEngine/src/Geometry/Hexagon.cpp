#include "Hexagon.h"



namespace DAF::Geometry {
	using namespace DirectX;

	const std::vector<unsigned int> Hexagon::indices = {
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,1
	};

	Hexagon::Hexagon(const float& radius) {
		vertices.push_back(Vertex(0.0f, 0.0f, 0.0f));
		XMVECTOR vec = { radius, 0.0f, 0.0f, 0.0f };
		constexpr float angle = XMConvertToRadians(60);
		for (uint8_t i = 0; i < 6; ++i) {
			vec = XMVector3Transform(vec, XMMatrixRotationRollPitchYaw(0.0f, 0.0f, angle));
			Vertex vtx(vec);
			vertices.push_back(vtx);
		}
	}

	Hexagon::Hexagon(const float& radius, const DirectX::XMFLOAT3& center) {
		vertices.push_back(Vertex(center));
		XMVECTOR vec = { radius, 0.0f, 0.0f, 0.0f };
		constexpr float angle = XMConvertToRadians(60);
		for (uint8_t i = 0; i < 6; ++i) {
			vec = XMVector3Transform(vec, XMMatrixRotationRollPitchYaw(0.0f, 0.0f, angle));
			vertices.push_back(Vertex(XMVector3Transform(vec, XMMatrixTranslation(center.x, center.y, center.z))));
		}
	}

	Hexagon::Hexagon(const float& radius, const DirectX::XMFLOAT3& center, const DirectX::XMFLOAT3& axis)
	{
		constexpr float angle = XMConvertToRadians(60);
		XMMATRIX m = XMMatrixRotationAxis(XMLoadFloat3(&axis), angle);
		XMFLOAT3 newCenter;
		XMStoreFloat3(&newCenter, XMVector3Transform(XMLoadFloat3(&center), m));
		vertices.push_back(Vertex(newCenter));
		XMVECTOR vec = { radius, 0.0f, 0.0f, 0.0f };
		for (uint8_t i = 0; i < 6; ++i) {
			vec = XMVector3Transform(vec, m);
			vertices.push_back(Vertex(XMVector3Transform(vec, XMMatrixTranslation(center.x, center.y, center.z))));
		}
	}

}