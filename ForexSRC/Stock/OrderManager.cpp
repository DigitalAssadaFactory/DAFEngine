#include "OrderManager.h"


namespace Stock {

	void OrderManager::Update(const float& ask, const float& bid)
	{
		m_ask = ask;
		m_bid = bid;

		for (int i = 0; i < m_lifetime_array.size(); ++i)
		{
			if (m_isOpen_array[i])
			{
				++m_lifetime_array[i];
				if (m_type_array[i] == OrderType::Buy) m_pip_array[i] = ShrinkDigits(m_symbol_array[i], bid - m_ask_array[i]);
				else if (m_type_array[i] == OrderType::Sell) m_pip_array[i] = ShrinkDigits(m_symbol_array[i], m_bid_array[i] - ask);
			}
		}
	}

	bool OrderManager::Buy(const std::string& symbol, const float& size)
	{
		if (m_ask_array.size() >= 4096) return false;
		m_symbol_array.push_back(symbol);
		m_ask_array.push_back(m_ask);
		m_bid_array.push_back(m_bid);
		m_size_array.push_back(size);
		m_type_array.push_back(OrderType::Buy);
		m_isOpen_array[ m_type_array.size() - 1 ] = true;
		m_lifetime_array.push_back(0);
		m_pip_array.push_back( ShrinkDigits(symbol, m_bid - m_ask) );
		return true;
	}

	bool OrderManager::Sell(const std::string& symbol, const float& size)
	{
		if (m_ask_array.size() >= 4096) return false;
		m_symbol_array.push_back(symbol);
		m_ask_array.push_back(m_ask);
		m_bid_array.push_back(m_bid);
		m_size_array.push_back(size);
		m_type_array.push_back(OrderType::Sell);
		m_isOpen_array[ m_type_array.size() - 1 ] = true;
		m_lifetime_array.push_back(0);
		m_pip_array.push_back( ShrinkDigits(symbol, m_bid - m_ask) );
		return true;
	}

	bool OrderManager::Close(const size_t& at)
	{
		if (!m_isOpen_array[at]) return false;
		m_isOpen_array[at] = false;
		m_pipTotal += m_pip_array[at];
		return true;
	}

	const int& OrderManager::PipTotal() const { return m_pipTotal; }
	const float& OrderManager::CashTotal() const { return m_cashTotal; }
	const size_t& OrderManager::Count() const { return m_ask_array.size(); }

	const bool& OrderManager::IsOpen(const size_t& at) const { return m_isOpen_array[at]; }
	const float& OrderManager::Ask(const size_t& at) const { return m_ask_array[at]; }
	const float& OrderManager::Bid(const size_t& at) const { return m_bid_array[at]; }
	const std::string& OrderManager::Symbol(const size_t& at) const { return m_symbol_array[at]; }
	const int& OrderManager::Pip(const size_t& at) const { return m_pip_array[at]; }
	const float& OrderManager::Size(const size_t& at) const { return m_size_array[at]; }
	const int& OrderManager::Lifetime(const size_t& at) const { return m_lifetime_array[at]; }
	const OrderType& OrderManager::Type(const size_t& at) const { return m_type_array[at]; }

}