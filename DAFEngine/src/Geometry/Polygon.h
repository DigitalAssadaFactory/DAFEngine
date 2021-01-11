#pragma once
#include "BaseMesh.h"
#include "../Utility.h"



namespace DAF::Geometry {

	struct Polygon : public BaseMesh
	{
		Polygon(unsigned int numberOfAngles);
	};

}