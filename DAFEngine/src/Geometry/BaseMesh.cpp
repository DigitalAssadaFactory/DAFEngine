#include "BaseMesh.h"


namespace DAF::Geometry {
	using namespace DirectX;

	void BaseMesh::Rotate(float x, float y, float z)
	{
		for (auto& v : vertices)
		{
			XMVECTOR result = XMVector3Transform(
				XMLoadFloat4(&v.position),
				XMMatrixRotationRollPitchYaw(
					XMConvertToRadians(x),
					XMConvertToRadians(y),
					XMConvertToRadians(z)
				)
			);
			XMStoreFloat4(&v.position, result);
		}
	}

	void BaseMesh::Translate(float x, float y, float z)
	{
		for (auto& v : vertices)
		{
			XMVECTOR result = XMVector3Transform(
				XMLoadFloat4(&v.position),
				XMMatrixTranslation(x, y, z)
			);
			XMStoreFloat4(&v.position, result);
		}
	}
	void BaseMesh::CalculateNormals()
	{
		XMFLOAT3 centroid = Centroid();
		XMFLOAT4 zero = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (auto& v : vertices)
			v.normal = zero;

		for (int j = 0; j < indices.size(); j += 3)
		{
			int index0 = indices[j];
			int index1 = indices[j + 1];
			int index2 = indices[j + 2];
			// v1 = clockwise from 1st to 2nd (a-b subtraction means what b have to do to become a)
			XMFLOAT4 v1 = (vertices[index1].position - centroid) - (vertices[index0].position - centroid);
			// v2 = clockwise from 2nd to 3rd
			XMFLOAT4 v2 = (vertices[index2].position - centroid) - (vertices[index1].position - centroid);
			XMVECTOR cross = XMVector3Cross(XMLoadFloat4(&v1), XMLoadFloat4(&v2));

			size_t at = index0;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
			at = index1;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
			at = index2;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
		}
	}
	DirectX::XMFLOAT3 BaseMesh::Centroid()
	{
		float x, y, z;
		x = y = z = 0.0f;
		for (const auto& v : vertices)
		{
			x += v.position.x;
			y += v.position.y;
			z += v.position.z;
		}
		return { x / vertices.size(), y / vertices.size(),z / vertices.size() };
	}
	void BaseMesh::InvertIndices()
	{
		for (int i = 0; i < indices.size(); i += 3)
			std::swap(indices[i], indices[i + 2]);
	}
}