#pragma once
#include "../Geometry.h"
#include "TickData.h"



namespace Stock {

	struct Candle {
		Candle() = default;
		Candle(const float& open, const float& close, const float& high, const float& low);
		Candle(const std::vector<float>& ticks);

		float m_open;
		float m_close;
		float m_high;
		float m_low;

		DAF::Geometry::Cube m_top;
		DAF::Geometry::Cube m_mid;
		DAF::Geometry::Cube m_bot;
	};

}
