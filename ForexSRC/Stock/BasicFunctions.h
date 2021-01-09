#pragma once
#include "../Logger.h"
#include "Candle.h"

enum class ScanType {
	horizontal,
	vertical
};

struct LargestRect {
	int x0, y0, x1, y1;
};

struct MyOutput
{
	int orderType;
	int closeID;
	int lifetime;
	float profit;
};
struct MyResult {
	int maxLifetime;
	int tradeCount;
	float profit;
	float loss;
};

struct MyResultPrint {
	int maxLifetime;
	int tradeCount;
	int __tp;
	int __aratio;
	int __range;
	int __huge;
	float profit;
	float loss;
};

namespace Stock {

	std::vector<float> MergeAsk(const std::vector<TickData>& ticks);
	std::vector<float> MergeBid(const std::vector<TickData>& ticks);
	std::vector<int> MergeYear(const std::vector<TickData>& ticks);
	std::vector<int> MergeMon(const std::vector<TickData>& ticks);
	std::vector<int> MergeDay(const std::vector<TickData>& ticks);
	std::vector<int> MergeHour(const std::vector<TickData>& ticks);
	std::vector<int> MergeMin(const std::vector<TickData>& ticks);
	std::vector<int> MergeSec(const std::vector<TickData>& ticks);
	std::vector<int> MergeDow(const std::vector<TickData>& ticks);
	std::vector<int> MergeBarID(const std::vector<TickData>& ticks, const size_t& barMinutes);

	std::vector<std::string> MakePathList(const std::string& currencyPair, int yearFrom, int yearTo);

	double MakeHigh(const std::vector<float>& ticks);
	double MakeLow(const std::vector<float>& ticks);

	float MovingAverage(const std::vector<Candle>& bars, const size_t& from, const size_t& period);

	int ShrinkDigits(const std::string& symbol, const float& value);

	int Ogonek(int from, int to, float tail, float body,
		const std::vector<float>& Open,
		const std::vector<float>& Close,
		const std::vector<float>& High,
		const std::vector<float>& Low
		);

	
	MyResult DoHomework( std::vector<MyOutput> data);

	LargestRect Rec_LargestRect(const std::vector<std::vector<int>>& grid, LargestRect rect, ScanType st);

}