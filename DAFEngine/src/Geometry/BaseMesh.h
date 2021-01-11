#pragma once
#include <vector>
#include "Vertex.h"
#include "../Utility/DXUtility.h"



namespace DAF::Geometry {

	struct BaseMesh {
		void Rotate(float x, float y, float z);
		void Translate(float x, float y, float z);
		void CalculateNormals();
		DirectX::XMFLOAT3 Centroid();
		void InvertIndices();

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}