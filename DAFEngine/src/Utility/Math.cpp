#include "Math.h"



namespace DAF {
	using namespace DirectX;


	std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> MeshFusion(
		std::vector<std::vector<Geometry::Vertex>>& vList, std::vector<std::vector<unsigned int>>& iList)
	{
		if (vList.size() != iList.size()) Logger::ThrowBox("vList.size() and iList.size() must be equal.");

		std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> out;
		for (int i = 0; i < vList.size(); ++i)
		{
			for (auto& index : iList[i])
				out.second.push_back(index + out.first.size());

			for (auto& vertex : vList[i])
				out.first.push_back(vertex);
		}
		return out;
	}

	void CalculateNormals(std::vector<Geometry::Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		XMFLOAT3 centroid = Centroid(vertices);
		XMFLOAT4 zero = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (auto& v : vertices)
			v.normal = zero;

		for (int j = 0; j < indices.size(); j += 3)
		{
			int index0 = indices[j];
			int index1 = indices[j+1];
			int index2 = indices[j+2];
			// v1 = clockwise from 1st to 2nd (a-b subtraction means what b have to do to become a)
			XMFLOAT4 v1 = (vertices[index1].position - centroid) - (vertices[index0].position - centroid);
			// v2 = clockwise from 2nd to 3rd
			XMFLOAT4 v2 = (vertices[index2].position - centroid) - (vertices[index1].position - centroid);
			v1 = { 0.0f, 0.0f, 1.0f, 1.0f };
			v2 = { 1.0f, 0.0f, 0.0f, 1.0f };
			XMVECTOR cross = XMVector3Cross(XMLoadFloat4(&v1), XMLoadFloat4(&v2));
			XMFLOAT4 tempresult;
			XMStoreFloat4(&tempresult, XMVector3Normalize( cross ));
			std::string outp = std::to_string(tempresult.x) + "   ";
			outp += std::to_string(tempresult.y) + "   ";
			outp += std::to_string(tempresult.z);
			//Logger::ThrowBox(outp);

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

	XMFLOAT3 Centroid(const std::vector<Geometry::Vertex>& vertices)
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

}