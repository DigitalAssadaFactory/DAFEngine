#pragma once
#include <DAF_Geometry.h>



namespace DAF::Geometry {

	struct House : public BaseMesh
	{
		std::vector<std::vector<Prism>> floors;
	};

}