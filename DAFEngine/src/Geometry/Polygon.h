#pragma once
#include "BaseMesh.h"



namespace DAF::Geometry {

	struct Polygon : public BaseMesh
	{
		Polygon(unsigned int numberOfAngles, float radius = 1.0f);
		Polygon(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	};

}