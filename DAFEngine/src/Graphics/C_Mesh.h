#pragma once
#include <string>
#include <vector>
#include <DAF_ECS.h>
#include "../Geometry/Vertex.h"



namespace DAF
{
	
	REGISTER_ECSComponent_04(
		Mesh,
		std::vector<std::string>, name,
		std::vector<Geometry::Vertex>, vertices,
		std::vector<unsigned int>, indices,
		DirectX::XMMATRIX, fix
	)

}