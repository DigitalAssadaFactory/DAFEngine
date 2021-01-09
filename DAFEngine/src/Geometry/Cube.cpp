#include "Cube.h"



namespace DAF::Geometry {
	using namespace DirectX;

	const std::vector<unsigned int> Cube::indices = {
	4,5,6,
	6,5,7,
	7,5,1,
	7,1,3,
	3,1,0,
	3,0,2,
	2,0,4,
	2,4,6,
	4,0,1,
	4,1,5,
	2,6,7,
	2,7,3
	};

	Cube::Cube()
	{
		float hx = 0.5f;
		float hy = 0.5f;
		float hz = 0.5f;

		vertices.push_back(Vertex(-hx, hy, hz));
		vertices.push_back(Vertex(hx, hy, hz));
		vertices.push_back(Vertex(-hx, -hy, hz));
		vertices.push_back(Vertex(hx, -hy, hz));
		vertices.push_back(Vertex(-hx, hy, -hz));
		vertices.push_back(Vertex(hx, hy, -hz));
		vertices.push_back(Vertex(-hx, -hy, -hz));
		vertices.push_back(Vertex(hx, -hy, -hz));


		// for normals
		//Quad _top;
		//Quad _bot;
		//Quad _left;
		//Quad _right;
		//Quad _back;
		//Quad _front;

	}

	Cube::Cube(const float& x, const float& y, const float& z)
	{
		float hx = x * 0.5f;
		float hy = y * 0.5f;
		float hz = z * 0.5f;

		vertices.push_back(Vertex(-hx, hy, hz));
		vertices.push_back(Vertex(hx, hy, hz));
		vertices.push_back(Vertex(-hx, -hy, hz));
		vertices.push_back(Vertex(hx, -hy, hz));
		vertices.push_back(Vertex(-hx, hy, -hz));
		vertices.push_back(Vertex(hx, hy, -hz));
		vertices.push_back(Vertex(-hx, -hy, -hz));
		vertices.push_back(Vertex(hx, -hy, -hz));
	}

	Cube::Cube(const float& x, const float& y, const float& z, const DirectX::XMFLOAT3& center)
	{
		float hx = x * 0.5f;
		float hy = y * 0.5f;
		float hz = z * 0.5f;

		vertices.push_back(Vertex(-hx, hy, hz));
		vertices.push_back(Vertex(hx, hy, hz));
		vertices.push_back(Vertex(-hx, -hy, hz));
		vertices.push_back(Vertex(hx, -hy, hz));
		vertices.push_back(Vertex(-hx, hy, -hz));
		vertices.push_back(Vertex(hx, hy, -hz));
		vertices.push_back(Vertex(-hx, -hy, -hz));
		vertices.push_back(Vertex(hx, -hy, -hz));

		for (auto& v : vertices)
		{
			v.position.x += center.x;
			v.position.y += center.y;
			v.position.z += center.z;
		}
	}

	Cube::Cube(const float& x, const float& y, const float& z, const DirectX::XMFLOAT3& center,
		const DirectX::XMFLOAT3& axis, const float& angle)
	{
		float hx = x * 0.5f;
		float hy = y * 0.5f;
		float hz = z * 0.5f;

		vertices.push_back(Vertex(-hx, hy, hz));
		vertices.push_back(Vertex(hx, hy, hz));
		vertices.push_back(Vertex(-hx, -hy, hz));
		vertices.push_back(Vertex(hx, -hy, hz));
		vertices.push_back(Vertex(-hx, hy, -hz));
		vertices.push_back(Vertex(hx, hy, -hz));
		vertices.push_back(Vertex(-hx, -hy, -hz));
		vertices.push_back(Vertex(hx, -hy, -hz));

		XMMATRIX m = XMMatrixRotationAxis(XMLoadFloat3(&axis), angle);
		for (auto& v : vertices)
		{
			XMVECTOR vec = XMLoadFloat4(&v.position);
			XMStoreFloat4(&v.position, XMVector3Transform(vec, m));
		}

		for (auto& v : vertices)
		{
			v.position.x += center.x;
			v.position.y += center.y;
			v.position.z += center.z;
		}

	}

}