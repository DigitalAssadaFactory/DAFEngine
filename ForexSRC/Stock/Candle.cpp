#include "Candle.h"



using namespace DAF::Geometry;

namespace Stock {

	Candle::Candle(const float& open, const float& close, const float& high, const float& low)
	{
		m_open = open;
		m_close = close;
		m_high = high;
		m_low = low;

		float topHeight = abs(m_high - std::max(m_open, m_close));
		float midHeight = std::abs(m_open - m_close);
		float botHeight = abs(std::min(m_open, m_close) - m_low);

		if (m_close > m_open)
		{
			m_top = Cube(1.0f, topHeight, 0.3f, { 0.0f, m_close + 0.5f * topHeight, 0.0f });
			m_mid = Cube(1.0f, midHeight, 0.3f, { 0.0f, m_close - 0.5f * midHeight, 0.0f });
			m_bot = Cube(1.0f, botHeight, 0.3f, { 0.0f, m_close - midHeight - 0.5f * botHeight, 0.0f });
			for (auto& v : m_mid.vertices) v.color = { 1.0f, 1.0f, 0.0f, 1.0f };
		}
		else
		{
			m_top = Cube(1.0f, topHeight, 0.3f, { 0.0f, m_close + midHeight + 0.5f * topHeight, 0.0f });
			m_mid = Cube(1.0f, midHeight, 0.3f, { 0.0f, m_close + 0.5f * midHeight, 0.0f });
			m_bot = Cube(1.0f, botHeight, 0.3f, { 0.0f, m_close - 0.5f * botHeight, 0.0f });
			for (auto& v : m_mid.vertices) v.color = { 1.0f, 0.0f, 0.0f, 1.0f };
		}

		for (auto& v : m_top.vertices) v.color = { 1.0f, 1.0f, 0.0f, 0.2f };
		for (auto& v : m_bot.vertices) v.color = { 1.0f, 0.0f, 0.0f, 0.2f };
	}

	Candle::Candle(const std::vector<float>& ticks)
	{
		m_open = ticks[0];
		m_close = ticks[ticks.size() - 1];
		m_high = -999999.9f;
		m_low = 999999.9f;
		for (auto& t : ticks)
		{
			if (t > m_high) m_high = t;
			if (t < m_low) m_low = t;
		}

		float topHeight = abs(m_high - std::max(m_open, m_close));
		float midHeight = std::abs(m_open - m_close);
		float botHeight = abs(std::min(m_open, m_close) - m_low);

		if (m_close > m_open)
		{
			m_top = Cube(1.0f, topHeight, 0.3f, { 0.0f, m_close + 0.5f * topHeight, 0.0f });
			m_mid = Cube(1.0f, midHeight, 0.3f, { 0.0f, m_close - 0.5f * midHeight, 0.0f });
			m_bot = Cube(1.0f, botHeight, 0.3f, { 0.0f, m_close - midHeight - 0.5f * botHeight, 0.0f });
			for (auto& v : m_mid.vertices) v.color = { 1.0f, 1.0f, 0.0f, 1.0f };
		}
		else
		{
			m_top = Cube(1.0f, topHeight, 0.3f, { 0.0f, m_close + midHeight + 0.5f * topHeight, 0.0f });
			m_mid = Cube(1.0f, midHeight, 0.3f, { 0.0f, m_close + 0.5f * midHeight, 0.0f });
			m_bot = Cube(1.0f, botHeight, 0.3f, { 0.0f, m_close - 0.5f * botHeight, 0.0f });
			for (auto& v : m_mid.vertices) v.color = { 1.0f, 0.0f, 0.0f, 1.0f };
		}

		for (auto& v : m_top.vertices) v.color = { 1.0f, 1.0f, 1.0f, 0.1f };
		for (auto& v : m_bot.vertices) v.color = { 1.0f, 1.0f, 1.0f, 0.1f };
	}

}