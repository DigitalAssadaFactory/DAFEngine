#pragma once
#include "../ECS.h"
#include "../DYNAMIC_ARRAY_MACRO.h"
#include "Candle.h"
#include "BasicFunctions.h"


/*
namespace Stock {

	struct MA_Plane {
		MA_Plane(const std::vector<Candle>& bars, const int& from,
			const int& length, const int& depth, const int& periodStride );
		void LoadGraphics();

		float scaleX = 1.0f;
		float scaleZ = 1.0f;
		float scaleY = 0.1f;
	private:
		DYNAMIC_ARRAY_02(float) m_data;

		std::vector<Quad> m_quads;
		std::vector<ECS::Entity> m_entities;
	};

}
*/