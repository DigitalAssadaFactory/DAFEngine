#include "BasicFunctions.h"



using namespace DAF;

namespace Stock {

	std::vector<float> MergeAsk(const std::vector<TickData>& ticks) {
		std::vector<float> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].ask);
		}
		return out;
	}
	std::vector<float> MergeBid(const std::vector<TickData>& ticks) {
		std::vector<float> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back((float)ticks[i].bid);
		}
		return out;
	}
	std::vector<int> MergeYear(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].year);
		}
		return out;
	}
	std::vector<int> MergeMon(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].mon);
		}
		return out;
	}
	std::vector<int> MergeDay(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].day);
		}
		return out;
	}
	std::vector<int> MergeHour(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].hour);
		}
		return out;
	}
	std::vector<int> MergeMin(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].min);
		}
		return out;
	}
	std::vector<int> MergeSec(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].sec);
		}
		return out;
	}
	std::vector<int> MergeDow(const std::vector<TickData>& ticks) {
		std::vector<int> out;
		for (int i = 0; i < ticks.size(); ++i) {
			out.push_back(ticks[i].day_of_week);
		}
		return out;
	}

	std::vector<int> MergeBarID(const std::vector<TickData>& ticks, const size_t& barMinutes) {
		std::vector<int> out;
		int incrementCandle = 0;
		for (int i = 0; i < ticks.size(); ++i)
		{
			static int min = ticks[0].min;
			static int inc = 0;
			if (ticks[i].min != min)
			{
				++inc;
				min = ticks[i].min;
			}
			if( inc == barMinutes )
			{
				inc = 0;
				++incrementCandle;
			}
			out.push_back(incrementCandle);
		}
		return out;
	}

	std::vector<std::string> MakePathList(const std::string & currencyPair, int yearFrom, int yearTo)
	{
		std::vector<std::string> pathList;
		pathList.resize(60);
		for (size_t i = 0; yearFrom + i <= yearTo; ++i)
		{
			pathList[0 + i * 12] = currencyPair + "_Jan" + std::to_string(yearFrom + i);
			pathList[1 + i * 12] = currencyPair + "_Feb" + std::to_string(yearFrom + i);
			pathList[2 + i * 12] = currencyPair + "_Mar" + std::to_string(yearFrom + i);
			pathList[3 + i * 12] = currencyPair + "_Apr" + std::to_string(yearFrom + i);
			pathList[4 + i * 12] = currencyPair + "_May" + std::to_string(yearFrom + i);
			pathList[5 + i * 12] = currencyPair + "_Jun" + std::to_string(yearFrom + i);
			pathList[6 + i * 12] = currencyPair + "_Jul" + std::to_string(yearFrom + i);
			pathList[7 + i * 12] = currencyPair + "_Aug" + std::to_string(yearFrom + i);
			pathList[8 + i * 12] = currencyPair + "_Sep" + std::to_string(yearFrom + i);
			pathList[9 + i * 12] = currencyPair + "_Oct" + std::to_string(yearFrom + i);
			pathList[10 + i * 12] = currencyPair + "_Nov" + std::to_string(yearFrom + i);
			pathList[11 + i * 12] = currencyPair + "_Dec" + std::to_string(yearFrom + i);
		}
		return pathList;
	}

	double MakeHigh(const std::vector<float>& ticks)
	{
		double _high = -999999;
		for (auto& tick : ticks)
			if (tick > _high) _high = tick;
		return _high;
	}

	double MakeLow(const std::vector<float>& ticks)
	{
		double _low = 999999;
		for (auto& tick : ticks)
			if (tick < _low) _low = tick;
		return _low;
	}

	float MovingAverage(const std::vector<Candle>& bars, const size_t& from, const size_t& period)
	{
		if (from > bars.size() || from < 0) Logger::ThrowBox("MovingAverage:\nInvalid \"from\" value.");
		if (from - period < 0) Logger::ThrowBox("MovingAverage:\nInvalid \"period\" value.");

		float ma = 0.0f;
		for (size_t i = from - period; i <= from; ++i)
			ma += bars[i].m_close;

		return ma / period;
	}

	int ShrinkDigits(const std::string& symbol, const float& value)
	{
		if (symbol == "GBPJPY") return value * std::pow(10, 3);
		if (symbol == "USDJPY") return value * std::pow(10, 3);
		if (symbol == "GBPUSD") return value * std::pow(10, 5);
		if (symbol == "USDCAD") return value * std::pow(10, 5);
		if (symbol == "EURNZD") return value * std::pow(10, 5);
		if (symbol == "EURAUD") return value * std::pow(10, 5);
		return 0;
	}

	int Ogonek(int from, int to, float tail, float body,
		const std::vector<float>& Open,
		const std::vector<float>& Close,
		const std::vector<float>& High,
		const std::vector<float>& Low
		)
	{
		// 0 none
		// 1 green buy
		// 2 red buy
		// 3 green sell
		// 4 red sell

		if (from <= 0 || to <= 0)
			return 0;

		if (from < to)
		{
			int temp = from;
			from = to;
			to = temp;
		}

		float _open = Open[from];
		float _close = Close[to];
		float _high = -999999.9;
		float _low = 999999.9;

		for (int i = to; i <= from; ++i)
		{
			if (High[i] > _high)
			{
				_high = High[i];
			}
			if (Low[i] < _low)
			{
				_low = Low[i];
			}
		}

		if (_close > _open)
		{
			if ((_close - _open) >= body * (_high - _low))
			{
				if ((_high - _close) >= tail * (_high - _low))
				{
					return 3;
				}
				if ((_open - _low) >= tail * (_high - _low))
				{
					return 1;
				}
			}
			return 0;
		}
		else
		{
			if ((_open - _close) >= body * (_high - _low))
			{
				if ((_high - _open) >= tail * (_high - _low))
				{
					return 4;
				}
				if ((_close - _low) >= tail * (_high - _low))
				{
					return 2;
				}
			}
			return 0;
		}
	}

	MyResult DoHomework( std::vector<MyOutput> data)
	{
		MyResult out;
		out.maxLifetime = 0;
		out.tradeCount = 0;
		out.profit = 0.0f;
		out.loss = 0.0f;

		for (int i = 0; i < data.size(); ++i)
		{
			if (data[i].orderType != 0 && data[i].closeID > i)
			{
				if (data[i].lifetime > out.maxLifetime)
				{
					out.maxLifetime = data[i].lifetime;
				}

				if (data[i].profit > 0.0f)
				{
					out.profit += data[i].profit;
				}
				else
				{
					out.loss += data[i].profit;
				}

				++out.tradeCount;
				i = data[i].closeID;
			}
		}
		return out;
	}

	LargestRect Rec_LargestRect(const std::vector<std::vector<int>>& grid, LargestRect rect, ScanType st)
	{
		if (rect.y1 == grid.size()) return rect;
		
		if ( st == ScanType::horizontal)
		{
			int _left = -1;
			int _right = -1;
			
			for (int i = rect.x0; i <= rect.x1 && grid[rect.y1 + 1][i] == 108; ++i)
			{
				++_left;
			}
			for (int i = rect.x1; i >= rect.x0 && grid[rect.y1 + 1][i] == 108; --i)
			{
				++_right;
			}

			if (_left < 1 && _right < 1) return rect;

			if (_right > _left)
			{
				Rec_LargestRect(grid, { rect.x1 - _right, rect.y0, rect.x1, rect.y1 + 1 }, st);
			}
			else
			{
				Rec_LargestRect(grid, { rect.x0, rect.y0, rect.x0 + _left, rect.y1 + 1 }, st);
			}

		}
		else
		{
			int _up = -1;
			int _down = -1;

			for (int i = rect.y0; i <= rect.y1 && grid[i][rect.x1 + 1] == 108; ++i)
			{
				++_up;
			}
			for (int i = rect.y1; i >= rect.y0 && grid[i][rect.x1 + 1] == 108; --i)
			{
				++_down;
			}

			if (_up < 1 && _down < 1) return rect;

			if (_down > _up)
			{
				Rec_LargestRect(grid, { rect.x0, rect.y1 - _down, rect.x1 + 1, rect.y1 }, st);
			}
			else
			{
				Rec_LargestRect(grid, { rect.x0, rect.y0, rect.x1 + 1, rect.y0 + _up }, st);
			}
		}
	}

}