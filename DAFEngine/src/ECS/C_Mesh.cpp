#include "C_Mesh.h"



namespace DAF
{

	INIT_ECSComponent_04(
		Mesh,
		std::vector<std::string>, name,
		std::vector<Geometry::Vertex>, vertices,
		std::vector<unsigned int>, indices,
		DirectX::XMMATRIX, fix
	)

}