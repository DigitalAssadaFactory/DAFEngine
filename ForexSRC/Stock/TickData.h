#pragma once
#include <iostream>
#include <iomanip>
#include <string>


namespace Stock {

	struct TickData {
		double bid;
		double ask;
		int year;
		int mon;
		int day;
		int hour;
		int min;
		int sec;
		int day_of_week;
		int day_of_year;
	};

}
