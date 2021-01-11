#pragma once
#include <vector>
#include "Vertex.h"



namespace DAF::Geometry {

	struct Quad {
		Quad() = default;
		Quad(const DirectX::XMFLOAT3& normal);
		Quad(const Vertex& v1, const Vertex& v2,
			const Vertex& v3, const Vertex& v4);
				
		std::vector<Vertex> vertices;
		static const std::vector<unsigned int> indices;
	};

}