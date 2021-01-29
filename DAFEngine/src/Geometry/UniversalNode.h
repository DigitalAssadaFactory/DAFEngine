#pragma once
#include "Vertex.h"
#include <bitset>



namespace DAF::Geometry {

	enum class UNodeType : uint32_t {
		Unknown = 0,
		Wood = 1,
		Soil = 2,
		Sand = 3,
		Stone = 4,
		Metal = 5,
		Glass = 6,
		Cloth = 7,
	};

	struct UniversalNode
	{
		// Row Major from top left corner (first 9 are z=-1.0f, second 9 z=0.0f and last 9 z=1.0f)
		UniversalNode(std::bitset<27> config, std::bitset<5> type);
		std::string Get();
		UNodeType GetType();
		std::string GetConfigString();
		uint32_t GetCoreUINT();
		std::vector<Vertex> GetVertices();
		std::vector<uint32_t> GetIndices();
	private:
		void MakeTriangle(uint32_t a, uint32_t b, uint32_t c);

		std::bitset<32> core;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

}