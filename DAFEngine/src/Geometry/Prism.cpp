#include "Prism.h"
#include <DAF_Utility.h>



namespace DAF::Geometry {
	using namespace DirectX;
		
	Prism::Prism(unsigned int numberOfAngles, float radius, float height,
		DirectX::XMFLOAT3 slideTop, bool smoothWall)
	{
		Polygon top(numberOfAngles, radius);
		Polygon bot(numberOfAngles, radius);
		top.Rotate(90, 0, 0);
		bot.Rotate(90, 0, 0);
		for (auto& v : top.vertices)
			v.position.y += 0.5 * height;
		for (auto& v : bot.vertices)
			v.position.y -= 0.5*height;
		bot.InvertIndices();
		top.Translate(slideTop);

		if (smoothWall)
		{
			std::vector<std::vector<Vertex>> vList = { top.vertices, bot.vertices };
			std::vector<std::vector<unsigned int>> iList = { top.indices, bot.indices };
			auto fusion = MeshFusion(vList, iList);
			vertices = fusion.first;
			indices = fusion.second;

			// optimization to compute it just once
			unsigned int optimization = vertices.size() + numberOfAngles;
			for (int i = vertices.size(); i < optimization; ++i)
			{
				indices.push_back(i);
				indices.push_back(i + numberOfAngles);
				indices.push_back((i + 1) % numberOfAngles + optimization);
				indices.push_back(i);
				indices.push_back((i + 1) % numberOfAngles + optimization);
				indices.push_back((i + 1) % numberOfAngles + vertices.size());
			}
			vertices.insert(vertices.end(), fusion.first.begin(), fusion.first.end());
		}
		else
		{
			std::vector<Polygon> walls;
			for (int i = 0; i < numberOfAngles; ++i)
			{
				std::vector<Vertex> wallVertices = {
					top.vertices[i],
					bot.vertices[i],
					bot.vertices[(i + 1) % numberOfAngles],
					top.vertices[(i + 1) % numberOfAngles]
				};
				wallVertices[0].texCoord = { 0,1,0,0 };
				wallVertices[1].texCoord = { 0,0,0,0 };
				wallVertices[2].texCoord = { 1,0,0,0 };
				wallVertices[3].texCoord = { 1,1,0,0 };

				std::vector<unsigned int> wallIndices = { 0,1,2,0,2,3 };
				walls.push_back(Polygon(wallVertices, wallIndices));
			}
			

			std::vector<std::vector<Vertex>> vList;
			vList.push_back(top.vertices);
			vList.push_back(bot.vertices);
			for (auto& w : walls) vList.push_back(w.vertices);
			std::vector<std::vector<unsigned int>> iList;
			iList.push_back(top.indices);
			iList.push_back(bot.indices);
			for (auto& w : walls) iList.push_back(w.indices);
			auto fusion = MeshFusion(vList, iList);
			vertices = fusion.first;
			indices = fusion.second;
		}
	}


}