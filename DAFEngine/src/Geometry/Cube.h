#pragma once
#include <vector>
#include "Vertex.h"



namespace DAF::Geometry
{

	struct Cube {
		Cube();
		Cube(Cube& rhs) : vertices(rhs.vertices) {}
		Cube(const float& x, const float& y, const float& z);
		Cube(const float& x, const float& y, const float& z, const DirectX::XMFLOAT3& center);
		Cube(const float& x, const float& y, const float& z, const DirectX::XMFLOAT3& center,
			const DirectX::XMFLOAT3& axis, const float& angle);

		std::vector<Vertex> vertices;
		static const std::vector<unsigned int> indices;
	};

}