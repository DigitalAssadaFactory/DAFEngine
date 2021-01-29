#pragma once
#include <vector>
#include "Vertex.h"



namespace DAF::Geometry {

	struct BaseMesh {
		void Append(const BaseMesh& mesh);
		void AppendVertices(std::vector<Vertex> new_vertices);
		void AppendIndices(std::vector<unsigned int> new_indices);
		void Rotate(float x, float y, float z);
		void Translate(float x, float y, float z);
		void Translate(DirectX::XMFLOAT3 offset);
		void CalculateNormals();
		DirectX::XMFLOAT3 Centroid();
		void InvertIndices();
		void Center();
		void Subtract(BaseMesh& shape);
		void Replicate(int number, float offset, DirectX::XMFLOAT3 direction);
		DirectX::XMFLOAT3 Size(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}