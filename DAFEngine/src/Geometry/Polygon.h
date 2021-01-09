#pragma once
#include "Vertex.h"
#include <vector>
#include "../Utility.h"



namespace DAF::Geometry {

	struct Polygon {
		Polygon(unsigned int numberOfAngles);

					
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}