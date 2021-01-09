#include "Chart.h"



namespace Stock {

	Stock::Chart::Chart(const std::string& symbol, const std::vector<TickData>& ticks, const size_t& candleTimeSpan)
	{
		m_symbol = symbol;
		m_displayCount = 100;

		//m_ask_array = DYNAMIC_ARRAY_02_INIT(float, 1, 0);
		m_bid_array = DYNAMIC_ARRAY_02_INIT(float, 1, 0);
		//m_year_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_mon_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_day_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_hour_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_min_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_sec_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_day_of_week_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		//m_day_of_year_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);

		int _min = ticks[0].min;
		int _hour = ticks[0].hour;
		int _sec = ticks[0].sec;
		size_t _inc = 0;
		for (size_t i = 0; i < ticks.size(); ++i)
		{
			if (_min != ticks[i].min) {
				++_inc;
				_min = ticks[i].min;
			}

			if (_inc == candleTimeSpan)
			{
				_inc = 0;
				const size_t at = m_bid_array.size() - 1;
				m_bid_array[at].push_back(ticks[i].bid);
				// previous option ---> m_bid_array.push_back(std::vector<float>(1, ticks[i].bid));

				//m_ask_array.push_back(std::vector<float>(1, ticks[i].ask));

				m_bid_array.push_back(std::vector<float>());

				//m_year_array.push_back(std::vector<int>(1, ticks[i].year));
				//m_mon_array.push_back(std::vector<int>(1, ticks[i].mon));
				//m_day_array.push_back(std::vector<int>(1, ticks[i].day));
				//m_hour_array.push_back(std::vector<int>(1, ticks[i].hour));
				//m_min_array.push_back(std::vector<int>(1, ticks[i].min));
				//m_sec_array.push_back(std::vector<int>(1, ticks[i].sec));
				//m_day_of_week_array.push_back(std::vector<int>(1, ticks[i].day_of_week));
				//m_day_of_year_array.push_back(std::vector<int>(1, ticks[i].day_of_year));
			}
			else
			{
				const size_t at = m_bid_array.size() - 1;
				//m_ask_array[at].push_back(ticks[i].ask);
				m_bid_array[at].push_back(ticks[i].bid);
				//m_year_array[at].push_back(ticks[i].year);
				//m_mon_array[at].push_back(ticks[i].mon);
				//m_day_array[at].push_back(ticks[i].day);
				//m_hour_array[at].push_back(ticks[i].hour);
				//m_min_array[at].push_back(ticks[i].min);
				//m_sec_array[at].push_back(ticks[i].sec);
				//m_day_of_week_array[at].push_back(ticks[i].day_of_week);
				//m_day_of_year_array[at].push_back(ticks[i].day_of_year);
			}
		}

		for (auto& bidsPerCandle : m_bid_array)
		{
			static int anchor = 0;
			m_open_array.push_back(bidsPerCandle[0]);
			m_close_array.push_back(bidsPerCandle[bidsPerCandle.size() - 1]);
			m_high_array.push_back(MakeHigh(bidsPerCandle));
			m_low_array.push_back(MakeLow(bidsPerCandle));
			if (anchor == 1)
			{
				//Logger::ThrowBox(std::to_string(bidsPerCandle.size()));
			}
			++anchor;
		}
	}

	/*
	Stock::Chart::Chart(const std::string& symbol, const std::vector<TickData>& ticks, const size_t& numCandles, const size_t& candleTimeSpan)
	{
		m_symbol = symbol;
		m_displayCount = 100;

		m_ask_array = DYNAMIC_ARRAY_02_INIT(float, 1, 0);
		m_bid_array = DYNAMIC_ARRAY_02_INIT(float, 1, 0);
		m_year_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_mon_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_day_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_hour_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_min_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_sec_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_day_of_week_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);
		m_day_of_year_array = DYNAMIC_ARRAY_02_INIT(int, 1, 0);

		int _min = ticks[0].min;
		int _hour = ticks[0].hour;
		int _sec = ticks[0].sec;
		size_t _inc = 0;
		size_t _total = 0;
		for (size_t i = 0; i < ticks.size(); ++i)
		{
			if (_total >= numCandles) break;
			//if (_min == ticks[i].min && ticks[i].sec < _sec) continue;
			if (_min != ticks[i].min) ++_inc;

			_sec = ticks[i].sec;
			if (_inc >= candleTimeSpan)
			{
				_min = ticks[i].min;
				_hour = ticks[i].hour;
				_inc = 0;
				++_total;
				if (_total >= numCandles) break;
				m_ask_array.push_back(std::vector<float>(1, ticks[i].ask));
				m_bid_array.push_back(std::vector<float>(1, ticks[i].bid));
				m_year_array.push_back(std::vector<int>(1, ticks[i].year));
				m_mon_array.push_back(std::vector<int>(1, ticks[i].mon));
				m_day_array.push_back(std::vector<int>(1, ticks[i].day));
				m_hour_array.push_back(std::vector<int>(1, ticks[i].hour));
				m_min_array.push_back(std::vector<int>(1, ticks[i].min));
				m_sec_array.push_back(std::vector<int>(1, ticks[i].sec));
				m_day_of_week_array.push_back(std::vector<int>(1, ticks[i].day_of_week));
				m_day_of_year_array.push_back(std::vector<int>(1, ticks[i].day_of_year));
			}
			else
			{
				const size_t at = m_ask_array.size() - 1;
				m_ask_array[at].push_back(ticks[i].ask);
				m_bid_array[at].push_back(ticks[i].bid);
				m_year_array[at].push_back(ticks[i].year);
				m_mon_array[at].push_back(ticks[i].mon);
				m_day_array[at].push_back(ticks[i].day);
				m_hour_array[at].push_back(ticks[i].hour);
				m_min_array[at].push_back(ticks[i].min);
				m_sec_array[at].push_back(ticks[i].sec);
				m_day_of_week_array[at].push_back(ticks[i].day_of_week);
				m_day_of_year_array[at].push_back(ticks[i].day_of_year);
			}
		}

		for (auto& bidsPerCandle : m_bid_array)
		{
			m_open_array.push_back(bidsPerCandle[bidsPerCandle.size() - 1]);
			m_close_array.push_back(bidsPerCandle[0]);
			m_high_array.push_back(MakeHigh(bidsPerCandle));
			m_low_array.push_back(MakeLow(bidsPerCandle));
		}

		
		m_candles.push_back(Candle(ticksPerCandle));

		for (int i = 0; i < m_candles.size(); ++i)
		{
			for (int j = 0; j < m_candles[0].m_top.vertices.size(); ++j)
			{
				m_candles[i].m_top.vertices[j].position.x -= stride * i;
				m_candles[i].m_mid.vertices[j].position.x -= stride * i;
				m_candles[i].m_bot.vertices[j].position.x -= stride * i;
			}
		}
	}
	*/


	void Chart::SetDisplayCount(const size_t& count)
	{
		m_displayCount = count;
	}

	/*
	void Chart::SetPosition(const DirectX::XMFLOAT3& pos)
	{
		for (auto& candle : m_candles)
		{
			for (auto& v : candle.m_bot.vertices) v.position = v.position + pos;
			for (auto& v : candle.m_mid.vertices) v.position = v.position + pos;
			for (auto& v : candle.m_top.vertices) v.position = v.position + pos;
		}
	}


	void Stock::Chart::LoadGraphics()
	{
		using namespace ECS;
		using namespace ECS::Component;

		size_t _counter = 0;
		for (auto& c : m_candles)
		{
			if (_counter >= m_displayCount) break;

			Entity e1, e2, e3;

			e1.AddComponent<Mesh>();
			e1.AddComponent<Renderer>();
			e2.AddComponent<Mesh>();
			e2.AddComponent<Renderer>();
			e3.AddComponent<Mesh>();
			e3.AddComponent<Renderer>();

			auto& _mesh1 = e1.GetComponent<Mesh>();
			auto& _rend1 = e1.GetComponent<Renderer>();
			auto& _mesh2 = e2.GetComponent<Mesh>();
			auto& _rend2 = e2.GetComponent<Renderer>();
			auto& _mesh3 = e3.GetComponent<Mesh>();
			auto& _rend3 = e3.GetComponent<Renderer>();

			_mesh1.vertices = c.m_top.vertices;
			_mesh1.indices = Cube::indices;
			_mesh2.vertices = c.m_mid.vertices;
			_mesh2.indices = Cube::indices;
			_mesh3.vertices = c.m_bot.vertices;
			_mesh3.indices = Cube::indices;

			_rend1.drawMode = DM::SingleSolid;
			_rend2.drawMode = DM::SingleSolid;
			_rend3.drawMode = DM::SingleSolid;
			_rend1.vertexShader = VS::Default;
			_rend2.vertexShader = VS::Default;
			_rend3.vertexShader = VS::Default;
			_rend1.pixelShader = PS::Default;
			_rend2.pixelShader = PS::Default;
			_rend3.pixelShader = PS::Default;

			System::Graphics::AddModel(e1);
			System::Graphics::AddModel(e2);
			System::Graphics::AddModel(e3);

			m_entities.push_back(std::move(e1));
			m_entities.push_back(std::move(e2));
			m_entities.push_back(std::move(e3));

			++_counter;
		}
	}
	*/

	const std::string& Chart::Symbol() const { return m_symbol; }
	const float& Chart::Open(const size_t& at) const { return m_open_array[at]; }
	const float& Chart::Close(const size_t& at) const { return m_close_array[at]; }
	const float& Chart::High(const size_t& at) const { return m_high_array[at]; }
	const float& Chart::Low(const size_t& at) const { return m_low_array[at]; }
	const std::vector<float>& Chart::Ask(const size_t& at) const { return m_ask_array[at]; }
	const std::vector<float>& Chart::Bid(const size_t& at) const { return m_bid_array[at]; }
	const std::vector<int>& Chart::Year(const size_t& at) const { return m_year_array[at]; }
	const std::vector<int>& Chart::Mon(const size_t& at) const { return m_mon_array[at]; }
	const std::vector<int>& Chart::Day(const size_t& at) const { return m_day_array[at]; }
	const std::vector<int>& Chart::Hour(const size_t& at) const { return m_hour_array[at]; }
	const std::vector<int>& Chart::Min(const size_t& at) const { return m_min_array[at]; }
	const std::vector<int>& Chart::Sec(const size_t& at) const { return m_sec_array[at]; }
	const std::vector<int>& Chart::DayOfWeek(const size_t& at) const { return m_day_of_week_array[at]; }
	const std::vector<int>& Chart::DayOfYear(const size_t& at) const { return m_day_of_year_array[at]; }
	const size_t& Chart::Size() const { return m_open_array.size(); }

	const std::vector<float>& Chart::GetOpenArray() const { return m_open_array; }
	const std::vector<float>& Chart::GetCloseArray() const { return m_close_array; }
	const std::vector<float>& Chart::GetHighArray() const { return m_high_array; }
	const std::vector<float>& Chart::GetLowArray() const { return m_low_array; }

}