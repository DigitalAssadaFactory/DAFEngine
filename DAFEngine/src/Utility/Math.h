#pragma once
#include "DXUtility.h"
#include "../Geometry.h"



namespace DAF {

	std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> MeshFusion(
		std::vector<std::vector<Geometry::Vertex>>& vList,std::vector<std::vector<unsigned int>>& iList);

	void CalculateNormals(std::vector<Geometry::Vertex>& vertices, std::vector<unsigned int>& indices);

	DirectX::XMFLOAT3 Centroid(const std::vector<Geometry::Vertex>& vertices);

}