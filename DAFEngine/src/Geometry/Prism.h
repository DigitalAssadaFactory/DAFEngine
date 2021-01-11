#pragma once
#include "Polygon.h"
#include "BaseMesh.h"
#include "../Utility/Math.h"



namespace DAF::Geometry {

	struct Prism : public BaseMesh
	{
		Prism(unsigned int numberOfAngles);
	};
}