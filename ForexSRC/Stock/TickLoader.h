#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include <mutex>
#include <fstream>
#include <execution>
#include "TickData.h"
#include "../Logger.h"




namespace Stock {

	std::vector<TickData> TickLoading(const std::string& path);
	//void MyLoadTick(std::vector<std::vector<TickData>>* container, const size_t at, const std::string& path);
	void MyLoadTick(std::vector<TickData>& dest, const std::string& path);

	size_t FileSize(const std::string& path);

	struct TickLoader {
		void Load(const std::string& name, const std::string& path);
		void Load(std::vector<TickData>& destination, const std::string& path);
		void Set(const std::string& name, const std::vector<TickData>& data);
		void Reset(const std::string& name);
		void Reverse(const std::string& name);
		std::vector<TickData> & operator[](const std::string & name);

	private:
		std::string ShrinkExtension(std::string & name);

		std::map <
			std::string, std::vector <TickData>
		> m_data;
	};




}