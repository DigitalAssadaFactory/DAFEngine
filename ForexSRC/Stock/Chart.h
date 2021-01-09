#pragma once
#include "../ECS.h"
#include "Candle.h"
#include "../DYNAMIC_ARRAY_MACRO.h"



namespace Stock {

	struct Chart
	{
		Chart() = default;
		Chart( const std::string& symbol, const std::vector<TickData>& ticks, const size_t& candleTimeSpan);
		//Chart( const std::string& symbol, const std::vector<TickData>& ticks, const size_t & numCandles, const size_t& candleTimeSpan);
		void SetDisplayCount(const size_t& count);
		//void SetPosition(const DirectX::XMFLOAT3& pos);
		//void LoadGraphics();

		const std::string& Symbol() const;
		const float& Open(const size_t& at) const;
		const float& Close(const size_t& at) const;
		const float& High(const size_t& at) const;
		const float& Low(const size_t& at) const;
		const std::vector<float>& Ask(const size_t& at) const;
		const std::vector<float>& Bid(const size_t& at) const;
		const std::vector<int>& Year(const size_t& at) const;
		const std::vector<int>& Mon(const size_t& at) const;
		const std::vector<int>& Day(const size_t& at) const;
		const std::vector<int>& Hour(const size_t& at) const;
		const std::vector<int>& Min(const size_t& at) const;
		const std::vector<int>& Sec(const size_t& at) const;
		const std::vector<int>& DayOfWeek(const size_t& at) const;
		const std::vector<int>& DayOfYear(const size_t& at) const;

		const size_t& Size() const;

		const std::vector<float>& GetOpenArray() const;
		const std::vector<float>& GetCloseArray() const;
		const std::vector<float>& GetHighArray() const;
		const std::vector<float>& GetLowArray() const;
	private:
		std::string m_symbol;
		size_t m_displayCount;
		float stride = 1.5f;
		float scaleY = 100.0f;

		//std::vector<Candle> m_candles;
		//std::vector<ECS::Entity> m_entities;

		DYNAMIC_ARRAY_02(float) m_ask_array;
		DYNAMIC_ARRAY_02(float) m_bid_array;
		DYNAMIC_ARRAY_02(int) m_year_array;
		DYNAMIC_ARRAY_02(int) m_mon_array;
		DYNAMIC_ARRAY_02(int) m_day_array;
		DYNAMIC_ARRAY_02(int) m_hour_array;
		DYNAMIC_ARRAY_02(int) m_min_array;
		DYNAMIC_ARRAY_02(int) m_sec_array;
		DYNAMIC_ARRAY_02(int) m_day_of_week_array;
		DYNAMIC_ARRAY_02(int) m_day_of_year_array;

		std::vector<float> m_open_array;
		std::vector<float> m_close_array;
		std::vector<float> m_high_array;
		std::vector<float> m_low_array;
	};

}