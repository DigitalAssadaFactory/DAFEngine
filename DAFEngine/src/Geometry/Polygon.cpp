#include "Polygon.h"
#include <DAF_Utility.h>



namespace DAF::Geometry {
	using namespace DirectX;

	Polygon::Polygon(unsigned int numberOfAngles, float radius)
	{
		if (numberOfAngles < 3) Logger::ThrowBox("Can't make polygon with less than 2 angles, learn math idiot :D");

		XMVECTOR vec = { radius, 0.0f, 0.0f };
		float angle = XMConvertToRadians(360.0f / numberOfAngles);
		if (!(numberOfAngles % 2))
		{
			vec = XMVector3Transform(
				vec,
				XMMatrixRotationRollPitchYaw(
					0.0f,
					0.0f,
					XMConvertToRadians(45))
			);
		}

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		for (int i = 0; i < numberOfAngles; ++i) {
			vec = XMVector3Transform(vec, XMMatrixRotationRollPitchYaw(0.0f, 0.0f, -angle));
			vertices.push_back(vec);
			if (i > 2)
			{
				indices.push_back(0);
				indices.push_back(i - 1);
				indices.push_back(i);
			}
		};

		auto s = Size();
		for (int i = 0; i < vertices.size(); ++i)
			vertices[i].texCoord = vertices[i].position;
	}

	Polygon::Polygon(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}


}