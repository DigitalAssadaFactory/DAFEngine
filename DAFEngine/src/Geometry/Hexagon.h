#pragma once
#include <vector>
#include "Vertex.h"



namespace DAF::Geometry {

	struct Hexagon {
		Hexagon() = delete;
		Hexagon(const float& radius);
		Hexagon(const float& radius, const DirectX::XMFLOAT3& center);
		Hexagon(const float& radius, const DirectX::XMFLOAT3& center, const DirectX::XMFLOAT3& axis);

		std::vector<Vertex> vertices;
		static const std::vector<unsigned int> indices;
	};

}