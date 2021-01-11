#include "Quad.h"



namespace DAF::Geometry {
	using namespace DirectX;

	const std::vector<unsigned int> Quad::indices = {
		0,1,2,
		2,1,3
	};

	Quad::Quad(const DirectX::XMFLOAT3& normal)
	{
	}

	Quad::Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4)
	{
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		vertices.push_back(v4);
	}

}