#pragma once
#include "Polygon.h"



namespace DAF::Geometry {

	struct Prism : public BaseMesh
	{
		Prism(unsigned int numberOfAngles, float radius = 1.0f, float height = 1.0f,
			DirectX::XMFLOAT3 slideTop = { 0,0,0 }, bool smoothWall = false);
	};
}