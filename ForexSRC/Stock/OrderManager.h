#pragma once
#include <bitset>
#include <vector>
#include "BasicFunctions.h"



namespace Stock {

	enum OrderType { None = 0, Buy, Sell };

	struct OrderManager {
		void Update(const float& ask, const float& bid);

		bool Buy(const std::string& symbol, const float& size);
		bool Sell(const std::string& symbol, const float& size);
		bool Close(const size_t& at);

		const int& PipTotal() const;
		const float& CashTotal() const;
		const size_t& Count() const;

		const bool& IsOpen(const size_t& at) const;
		const float& Ask(const size_t& at) const;
		const float& Bid(const size_t& at) const;
		const std::string& Symbol(const size_t& at) const;
		const int& Pip(const size_t& at) const;
		const float& Size(const size_t& at) const;
		const int& Lifetime(const size_t& at) const;
		const OrderType& Type(const size_t& at) const;	

	private:
		float m_ask;
		float m_bid;
		int m_pipTotal = 0;
		float m_cashTotal = 0;

		std::bitset<4096> m_isOpen_array;
		std::vector<float> m_ask_array;
		std::vector<float> m_bid_array;
		std::vector<std::string> m_symbol_array;
		std::vector<int> m_pip_array;
		std::vector<float> m_size_array;
		std::vector<int> m_lifetime_array;
		std::vector<OrderType> m_type_array;
	};

}