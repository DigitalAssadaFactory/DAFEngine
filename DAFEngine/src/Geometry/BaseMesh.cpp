#include "BaseMesh.h"
#include <DAF_Utility.h>



namespace DAF::Geometry {
	using namespace DirectX;

	void BaseMesh::Append(const BaseMesh& mesh)
	{
		AppendIndices(mesh.indices);
		AppendVertices(mesh.vertices);
	}

	void BaseMesh::AppendVertices(std::vector<Vertex> new_vertices)
	{
		vertices.insert(vertices.end(), new_vertices.begin(), new_vertices.end());
	}

	void BaseMesh::AppendIndices(std::vector<unsigned int> new_indices)
	{
		for (auto& i : new_indices)
			i += vertices.size();
		indices.insert(indices.end(), new_indices.begin(), new_indices.end());
	}

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

	void BaseMesh::Translate(DirectX::XMFLOAT3 offset)
	{
		Translate(offset.x, offset.y, offset.z);
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

	void BaseMesh::Center()
	{
		auto centroid = Centroid();
		for (auto& v : vertices)
			v.position = v.position - centroid;
	}

	void BaseMesh::Subtract(BaseMesh& shape)
	{
		XMFLOAT3 centroid = Centroid();
		XMVECTOR vCentroid = XMLoadFloat3(&centroid);
		float result, length;
		for (auto& v : vertices)
		{
			XMVECTOR vPoint = XMLoadFloat4(&v.position);
			for (int i = 0; i < shape.indices.size(); i += 3)
			{
				int index0 = shape.indices[i];
				int index1 = shape.indices[i + 1];
				int index2 = shape.indices[i + 2];

				if (TriangleTests::Intersects(
					vCentroid,
					XMVector3Normalize(vPoint),
					XMLoadFloat4(&shape.vertices[index0].position),
					XMLoadFloat4(&shape.vertices[index1].position),
					XMLoadFloat4(&shape.vertices[index2].position),
					result)
					)
				{
					XMStoreFloat(&length, XMVector3Length(vPoint));
					if (length > result)
					{
						XMStoreFloat4(
							&v.position,
							XMVector3ClampLength(vPoint, result, result)
						);
					}
				}
			}
		}
	}


	/*std::string out;
	XMFLOAT3 vec, shrinked;
	XMStoreFloat3(&vec, vPoint);
	XMStoreFloat3(&shrinked, XMVector3ClampLength(vPoint, result, result));

	out += std::to_string(vec.x) + " | " + std::to_string(vec.y) + " | " + std::to_string(vec.z) + "\n";
	out += std::to_string(shrinked.x) +
		" | " + std::to_string(shrinked.y) +
		" | " + std::to_string(shrinked.z) + "\n";*/


	void BaseMesh::Replicate(int number, float offset, XMFLOAT3 direction)
	{
		XMVECTOR dir = XMLoadFloat3(&direction);

		Size(direction.x, direction.y, direction.z);

		dir = XMVector3ClampLength(dir, offset, offset);
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, dir);

		auto new_vertices = vertices;
		auto new_indices = indices;
		for (int i = 0; i < number; ++i)
		{
			for (auto& v : new_vertices)
				v.position = v.position + f3;

			AppendIndices(new_indices);
			AppendVertices(new_vertices);
		}
	}

	DirectX::XMFLOAT3 BaseMesh::Size(float x, float y, float z)
	{
		float minX, maxX, minY, maxY, minZ, maxZ;
		minX = minY = minZ = 999999.9f;
		maxX = maxY = maxZ = -999999.9f;
		if ((x + y + z) != 0.0f)
		{
			XMMATRIX m = XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(x),
				XMConvertToRadians(y),
				XMConvertToRadians(z)
			);
			for (const auto& v : vertices)
			{
				XMFLOAT3 f3;
				XMStoreFloat3(
					&f3,
					XMVector3Transform(XMLoadFloat4(&v.position), m)
				);
				if (f3.x < minX) minX = f3.x;
				if (f3.x > maxX) maxX = f3.x;
				if (f3.y < minY) minY = f3.y;
				if (f3.y > maxY) maxY = f3.y;
				if (f3.z < minZ) minZ = f3.z;
				if (f3.z > maxZ) maxZ = f3.z;
			}
		}
		else
		{
			for (const auto& v : vertices)
			{
				if (v.position.x < minX) minX = v.position.x;
				if (v.position.x > maxX) maxX = v.position.x;
				if (v.position.y < minY) minY = v.position.y;
				if (v.position.y > maxY) maxY = v.position.y;
				if (v.position.z < minZ) minZ = v.position.z;
				if (v.position.z > maxZ) maxZ = v.position.z;
			}
		}
		return { maxX - minX, maxY - minY, maxZ - minZ };
	}

}