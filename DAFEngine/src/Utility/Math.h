#pragma once
#include <numeric>
#include <random>
#include <DAF_Geometry.h>



namespace DAF {

	std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> MeshFusion(
		std::vector<std::vector<Geometry::Vertex>>& vList, std::vector<std::vector<unsigned int>>& iList);

	void CalculateNormals(std::vector<Geometry::Vertex>& vertices, std::vector<unsigned int>& indices);

	DirectX::XMFLOAT3 Centroid(const std::vector<Geometry::Vertex>& vertices);

	class PerlinNoise {
		std::vector<int> p;
	public:
		PerlinNoise();
		PerlinNoise(unsigned int seed);
		double noise(double x, double y, double z);
	private:
		double fade(double t);
		double lerp(double t, double a, double b);
		double grad(int hash, double x, double y, double z);
	};

}