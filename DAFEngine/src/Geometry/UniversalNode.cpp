#include "UniversalNode.h"
#include <DAF_Utility.h>



namespace DAF::Geometry {

	UniversalNode::UniversalNode(std::bitset<27> config, std::bitset<5> type)
	{
		vertices.resize(27);
		core = std::bitset<32>(type.to_string() + config.to_string());

		for (int z = 0; z < 3; ++z)
			for (int y = 0; y < 3; ++y)
				for (int x = 0; x < 3; ++x)
				{
					if (config[26 - (z * 9 + y * 3 + x)])
						vertices[z * 9 + y * 3 + x].position = { x*1.0f - 1.0f,y*-1.0f + 1.0f,z*1.0f - 1.0f,0.0f };
					else
						vertices[z * 9 + y * 3 + x].position = { 0,0,0,0 };
				}

		MakeTriangle(4, 1, 0);
		MakeTriangle(4, 0, 3);
		MakeTriangle(4, 3, 6);
		MakeTriangle(4, 6, 7);
		MakeTriangle(4, 7, 8);
		MakeTriangle(4, 8, 5);
		MakeTriangle(4, 5, 2);
		MakeTriangle(4, 2, 1);

		MakeTriangle(12, 9, 18);
		MakeTriangle(12, 18, 21);
		MakeTriangle(12, 21, 24);
		MakeTriangle(12, 24, 15);
		MakeTriangle(12, 15, 6);
		MakeTriangle(12, 6, 3);
		MakeTriangle(12, 3, 0);
		MakeTriangle(12, 0, 9);

		MakeTriangle(22, 19, 20);
		MakeTriangle(22, 20, 23);
		MakeTriangle(22, 23, 26);
		MakeTriangle(22, 26, 25);
		MakeTriangle(22, 25, 24);
		MakeTriangle(22, 24, 21);
		MakeTriangle(22, 21, 18);
		MakeTriangle(22, 18, 19);

		MakeTriangle(14, 11, 2);
		MakeTriangle(14, 2, 5);
		MakeTriangle(14, 5, 8);
		MakeTriangle(14, 8, 17);
		MakeTriangle(14, 17, 26);
		MakeTriangle(14, 26, 23);
		MakeTriangle(14, 23, 20);
		MakeTriangle(14, 20, 11);

		MakeTriangle(10, 1, 2);
		MakeTriangle(10, 2, 11);
		MakeTriangle(10, 11, 20);
		MakeTriangle(10, 20, 19);
		MakeTriangle(10, 19, 18);
		MakeTriangle(10, 18, 9);
		MakeTriangle(10, 9, 0);
		MakeTriangle(10, 0, 1);

		MakeTriangle(16, 7, 6);
		MakeTriangle(16, 6, 15);
		MakeTriangle(16, 15, 24);
		MakeTriangle(16, 24, 25);
		MakeTriangle(16, 25, 26);
		MakeTriangle(16, 26, 17);
		MakeTriangle(16, 17, 8);
		MakeTriangle(16, 8, 7);
	}

	UNodeType UniversalNode::GetType()
	{
		return UNodeType(
			((core & std::bitset<32>("11111000000000000000000000000000")) >> 27).to_ulong()
		);
	}

	std::string UniversalNode::Get()
	{
		return core.to_string();
	}

	std::string UniversalNode::GetConfigString()
	{
		return (core & std::bitset<32>("00000111111111111111111111111111")).to_string();
	}

	uint32_t UniversalNode::GetCoreUINT()
	{
		return core.to_ulong();
	}

	std::vector<Vertex> UniversalNode::GetVertices()
	{
		return vertices;
	}

	std::vector<uint32_t> UniversalNode::GetIndices()
	{
		return indices;
	}

	void UniversalNode::MakeTriangle(uint32_t a, uint32_t b, uint32_t c)
	{
		if (vertices[a].position != vertices[b].position
			&&
			vertices[a].position != vertices[c].position
			&&
			vertices[b].position != vertices[c].position)
		{
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}
	}

}