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
		CalculateNormals();
	}

	void Quad::CalculateNormals()
	{
		auto a = vertices[2].position - vertices[0].position;
		auto b = vertices[0].position - vertices[1].position;
		XMStoreFloat4(&vertices[0].normal, XMVector3Cross(XMLoadFloat4(&a), XMLoadFloat4(&b)));

		a = vertices[3].position - vertices[1].position;
		b = vertices[0].position - vertices[1].position;
		XMStoreFloat4(&vertices[1].normal, XMVector3Cross(XMLoadFloat4(&a), XMLoadFloat4(&b)));

		a = vertices[2].position - vertices[0].position;
		b = vertices[2].position - vertices[3].position;
		XMStoreFloat4(&vertices[2].normal, XMVector3Cross(XMLoadFloat4(&a), XMLoadFloat4(&b)));

		a = vertices[3].position - vertices[1].position;
		b = vertices[2].position - vertices[3].position;
		XMStoreFloat4(&vertices[3].normal, XMVector3Cross(XMLoadFloat4(&a), XMLoadFloat4(&b)));
	}

}