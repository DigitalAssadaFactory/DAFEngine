#include "Polygon.h"


namespace DAF::Geometry {
	using namespace DirectX;

	Polygon::Polygon(unsigned int numberOfAngles)
	{
		if (numberOfAngles < 3) Logger::ThrowBox("Can't make polygon with less than 2 angles, learn math idiot :D");

		XMVECTOR vec = { 1.0f, 0.0f, 0.0f, 0.0f };
		float angle = XMConvertToRadians(360.0f / numberOfAngles);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		for (uint8_t i = 0; i < numberOfAngles; ++i) {
			vec = XMVector3Transform(vec, XMMatrixRotationRollPitchYaw(0.0f, 0.0f, angle));
			vertices.push_back(vec);
			if (i > 2)
			{
				indices.push_back(0);
				indices.push_back(i - 1);
				indices.push_back(i);
			}
		};

		for (auto& v : vertices)
			v.normal = { 0.0f, 0.0f, -1.0f, 0.0f };
	}

}