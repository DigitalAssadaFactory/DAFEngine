#include "Prism.h"



namespace DAF::Geometry {
	using namespace DirectX;

	Prism::Prism(unsigned int numberOfAngles)
	{
		Polygon front(numberOfAngles);
		Polygon back(numberOfAngles);
		for (auto& v : back.vertices)
			v.position.z += 4.0f;
		back.InvertIndices();

		std::vector<std::vector<Vertex>> vList = { front.vertices, back.vertices };
		std::vector<std::vector<unsigned int>> iList = { front.indices, back.indices };
		auto fusion = MeshFusion(vList, iList);
		vertices = fusion.first;
		indices = fusion.second;
		
		for (int i = 0; i < numberOfAngles; ++i)
		{
			indices.push_back(i);
			indices.push_back(i + numberOfAngles);
			indices.push_back((i + 1) % numberOfAngles + numberOfAngles);
			indices.push_back(i);
			indices.push_back((i + 1) % numberOfAngles + numberOfAngles);
			indices.push_back((i + 1) % numberOfAngles);
		}
		CalculateNormals();
	}

}