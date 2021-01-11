#pragma once


/*void Engine::StockConfig(const std::string& currencyPair, float minProfit)
{
	DYNAMIC_ARRAY_04(int) aSprint = DYNAMIC_ARRAY_04_INIT(int, 10, 21, 7, 21);

	//           std::string vsize = std::to_string(aSprint.size()) + "\n" +
	//           	std::to_string(aSprint[0].size()) + "\n" +
	//           	std::to_string(aSprint[0][0].size()) + "\n" +
	//           	std::to_string(aSprint[0][0][0].size());
	//           Logger::ThrowBox(vsize);
	//
	//           std::vector < std::vector<std::vector<std::vector<int>>>> aSprint;
	//
	//           aSprint.resize(9);
	//           for (auto& x : aSprint)
	//           	x.resize(21);
	//
	//           for (auto& x : aSprint)
	//           	for (auto& y : x)
	//           		y.resize(7);
	//
	//           for (auto& x : aSprint)
	//           	for (auto& y : x)
	//           		for (auto& z : y)
	//           			z.resize(21);
	//


	for (auto& x : aSprint)
		for (auto& y : x)
			for (auto& z : y)
				for (auto& w : z)
					w = 0;

	std::fstream filePreinit;
	filePreinit.open("ePREINIT.mqh", std::ios::out);
	std::string e_preinit = "";

	std::fstream fileConfig;
	fileConfig.open("eCONFIG.mqh", std::ios::out);
	std::string e_config = "";

	std::fstream fileMacro;
	fileMacro.open("eMACRO.mqh", std::ios::out);
	std::string e_macro = "";

	std::fstream fileLoop;
	fileLoop.open("eLOOP.mqh", std::ios::out);
	std::string e_loop = "for (int i = 0; i < 21 && !m_order.IsOpen(); ++i)\n{\n";



	for (int f = 9; f > 0; --f)
	{
		std::vector<MyResultPrint> out = LoadVectorCache<MyResultPrint>("OUTPUT/" + currencyPair + "/FINAL_RESULT_CACHE_" + std::to_string(f));
		std::string config = "config" + std::to_string(f);

		float t_profit = 0.0f;
		float t_loss = 0.0f;
		int t_counter = 0;
		int t_trades = 0;
		for (const auto& a : out)
		{
			if (a.profit > 0.0007f && a.loss == 0.0f && a.maxLifetime < a.__range * 2)
			{
				if (f == 9 || (f != 9 && aSprint[f + 1][a.__range][a.__huge][a.__aratio] != 108))
				{
					aSprint[f][a.__range][a.__huge][a.__aratio] = 108;
				}

				t_profit += a.profit * 1000;
				t_loss += a.loss * 1000;
				t_trades += a.tradeCount;
				++t_counter;
			}
		}
		//--------------------------------
		//          Logger::ThrowBox(
		//          	"Profit : " + std::to_string(t_profit) +
		//          	"\nLoss : " + std::to_string(t_loss) +
		//          	"\nTrades : " + std::to_string(t_trades) +
		//          	"\nCount : " + std::to_string(t_counter)
		//          );
		//--------------------------------
		//          std::string sprint = "";
		//          for (auto& i : aSprint[0])
		//          {
		//          	for (auto& j : i)
		//          	{
		//          		if (j == 108)
		//          			sprint += "X";
		//          		else sprint += "+";
		//          	}
		//          	sprint += "\n";
		//          }
		//          Logger::ThrowBox(sprint);
		//--------------------------------

		DYNAMIC_ARRAY_02(LargestRect) vRect = DYNAMIC_ARRAY_02_INIT(LargestRect, 21, 0);

		int magicX = 0;
		bool isDirty = true;
		while (isDirty)
		{
			++magicX;
			isDirty = false;
			for (int range_ = 0; range_ < 21; ++range_)
				for (int huge_ = 0; huge_ < 7; ++huge_)
					for (int aratio_ = 0; aratio_ < 21; ++aratio_)
					{
						int aratioChain = -1;
						int hugeChain = -1;

						for (int x = aratio_; x < 21 && aSprint[f][range_][huge_][x] == 108; ++x)
						{
							++aratioChain;
						}
						for (int y = huge_; y < 7 && aSprint[f][range_][y][aratio_] == 108; ++y)
						{
							++hugeChain;
						}

						if (aratioChain < 0 && hugeChain < 0) continue;

						isDirty = true;
						if (aratioChain > hugeChain)
						{
							auto rect = Stock::Rec_LargestRect(aSprint[f][range_],
								{ aratio_, huge_, aratio_ + aratioChain, huge_ },
								ScanType::horizontal);

							vRect[range_].push_back(rect);

							for (int x = rect.x0; x <= rect.x1; ++x)
								for (int y = rect.y0; y <= rect.y1; ++y)
									aSprint[f][range_][y][x] = 0;
						}
						else
						{
							auto rect = Stock::Rec_LargestRect(aSprint[f][range_],
								{ aratio_,huge_, aratio_, huge_ + hugeChain },
								ScanType::vertical);

							vRect[range_].push_back(rect);

							for (int x = rect.x0; x <= rect.x1; ++x)
								for (int y = rect.y0; y <= rect.y1; ++y)
									aSprint[f][range_][y][x] = 0;
						}

					}
		}

		//--------------------------------------------------
		//       int sum = 0;
		//       for (auto& r : vRect)
		//       	for (auto& x : r)
		//       		++sum;
		//
		//       Logger::ThrowBox("sum = " + std::to_string(sum));

		int maxConfig = 0;
		for (auto& r : vRect)
			if (r.size() > maxConfig) maxConfig = r.size();

		//Logger::ThrowBox(std::to_string(maxConfig));
		//--------------------------------------------------

		if (maxConfig != 0)
		{
			e_macro += "#define MAX_CONFIG_" + std::to_string(f) + " " + std::to_string(maxConfig + 1) + "\nint " +
				config + "[21][" + std::to_string(maxConfig + 1) + "];\n";
		}

		for (int i = 0; i < vRect.size(); ++i)
		{
			std::string temp_mql = "";

			temp_mql += config + "[" + std::to_string(i) + "][0] " +
				"= VShape( 0, " + std::to_string(10 + i) + ", 0.05f, 0.3f, 0.5f, 1.0f);\n";

			temp_mql += "if( " + config + "[" + std::to_string(i) + "][0] > 0 )\n{\n";

			int valid_counted = 0;
			for (int j = 0; j < maxConfig; ++j)
			{
				if (j < vRect[i].size())
				{
					float areaMin = 0.5f + vRect[i][j].x0 * 0.1f;
					float areaMax = 0.5f + vRect[i][j].x1 * 0.1f + 0.1f;
					float hugeMin = 0.3f + vRect[i][j].y0 * 0.1f;
					float hugeMax = 0.3f + vRect[i][j].y1 * 0.1f + 0.1f;

					temp_mql += "\t" + config + "[" + std::to_string(i) + "][" + std::to_string(j + 1) + "] " +
						"= AShape( 0, " + std::to_string(10 + i) + ", " + std::to_string(areaMin) + ", " +
						std::to_string(areaMax) + ", " + std::to_string(hugeMin) + ", " + std::to_string(hugeMax) + " );\n";

					++valid_counted;
				}
			}
			temp_mql += "}\n";

			if (valid_counted > 0) e_config += temp_mql;
		}


		for (int i = 0; i < vRect.size(); ++i)
		{
			for (int j = 0; j < maxConfig; ++j)
			{
				if (j >= vRect[i].size())
				{
					e_preinit += config + "[" + std::to_string(i) + "][" + std::to_string(j + 1) + "] = -7;\n";
				}
			}
		}

		if (maxConfig != 0)
		{
			e_loop += "\tif ( " + config + "[i][0] != 0 )\n\t{\n" +
				"\t\tfor (int j = 1; j < MAX_CONFIG_" + std::to_string(f) + " && " + config + "[i][j] != -7; ++j)\n\t\t{\n" +
				"\t\t\tif ( ////////////////////////////\n\t\t\t\t(" + config + "[i][j] == BUY_TOR && " +
				config + "[i][0] == BUY_GREEN)\n\t\t\t\t||\n\t\t\t\t(" + config + "[i][j] == BUY_ENG && " +
				config + "[i][0] == BUY_RED)\n\t\t\t)////////////////////////////\n\t\t\t{\n\t\t\t" +
				"\tif ( m_useMaxSize ) { Buy( Symbol(), MaxLots(), i, " + std::to_string(f) + " ); }" +
				"\n\t\t\t\telse { Buy( Symbol(), m_size, i, " + std::to_string(f) + " ); }\n\t\t\t}\n" +
				"\t\t\telse if ( ////////////////////////////\n\t\t\t\t(" + config + "[i][j] == SELL_TOR && " +
				config + "[i][0] == SELL_RED)\n\t\t\t\t||\n\t\t\t\t(" + config + "[i][j] == SELL_ENG && " +
				config + "[i][0] == SELL_GREEN)\n\t\t\t)////////////////////////////\n\t\t\t{\n\t\t\t\t" +
				"if ( m_useMaxSize ) { Sell( Symbol(), MaxLots(), i, " + std::to_string(f) + " ); }\n\t\t\t\t" +
				"else { Sell( Symbol(), m_size,  i, " + std::to_string(f) + " ); }\n\t\t\t}\n\t\t}\n\t}\n\n\n";
		}
	}
	e_loop += "}";


	fileConfig.write(e_config.c_str(), e_config.length());
	fileConfig.close();

	filePreinit.write(e_preinit.c_str(), e_preinit.length());
	filePreinit.close();

	fileMacro.write(e_macro.c_str(), e_macro.length());
	fileMacro.clear();

	fileLoop.write(e_loop.c_str(), e_loop.length());
	fileLoop.clear();

	Logger::ThrowBox("Task completed");
}*/

/*void Engine::Trash() {

	std::vector<int>            myCandle;
	std::vector<float>          myAsk;
	std::vector<float>          myBid;
	static Stock::TickLoader    loader;


	{
		//---------------------------------------------------
		//        FILE_NAMES      FUTURES      TICK_DATA
		//---------------------------------------------------
		std::string currencyPair = "AUDCAD";
		std::vector<std::string> fileNameList = Stock::MakePathList(currencyPair, 2015, 2019);
		std::vector<std::future<std::vector<Stock::TickData> > > _futures;
		_futures.resize(fileNameList.size());
		std::vector<std::vector<Stock::TickData>> _tickData;
		_tickData.resize(fileNameList.size());

		//---------------------------------------------------
		//           Loading Ticks from disc
		//---------------------------------------------------
		for (size_t i = 0; i < fileNameList.size(); ++i)
			_futures[i] = std::async(std::launch::async, LoadVectorCache<Stock::TickData>, "res/data/" + currencyPair + "/" + fileNameList[i]);

		for (size_t i = 0; i < fileNameList.size(); ++i)
			_tickData[i] = _futures[i].get();

		//---------------------------------------------------
		//                 Merging months
		//---------------------------------------------------
		std::vector<Stock::TickData> _convergence;
		for (int i = 0; i < _tickData.size(); ++i) {
			_convergence.reserve(_tickData[i].size());
			_convergence.insert(_convergence.end(), _tickData[i].begin(), _tickData[i].end());
		}
		loader.Set("GBPJPY", _convergence);



		std::future<std::vector<float>> fAsk = std::async(std::launch::async, Stock::MergeAsk, _convergence);
		std::future<std::vector<float>> fBid = std::async(std::launch::async, Stock::MergeBid, _convergence);
		std::future<std::vector<int>>   fYear = std::async(std::launch::async, Stock::MergeYear, _convergence);
		std::future<std::vector<int>>   fMon = std::async(std::launch::async, Stock::MergeMon, _convergence);
		std::future<std::vector<int>>   fDay = std::async(std::launch::async, Stock::MergeDay, _convergence);
		std::future<std::vector<int>>   fHour = std::async(std::launch::async, Stock::MergeHour, _convergence);
		std::future<std::vector<int>>   fMin = std::async(std::launch::async, Stock::MergeMin, _convergence);
		std::future<std::vector<int>>   fSec = std::async(std::launch::async, Stock::MergeSec, _convergence);
		std::future<std::vector<int>>   fDow = std::async(std::launch::async, Stock::MergeDow, _convergence);

		myAsk = fAsk.get();
		myBid = fBid.get();
		std::vector<int> myYear = fYear.get();
		std::vector<int> myMon = fMon.get();
		std::vector<int> myDay = fDay.get();
		std::vector<int> myHour = fHour.get();
		std::vector<int> myMin = fMin.get();
		std::vector<int> mySec = fSec.get();
		std::vector<int> myDow = fDow.get();

		CacheVector(myYear, "yearCache");
		CacheVector(myMon, "monCache");
		CacheVector(myDay, "dayCache");
		CacheVector(myHour, "hourCache");
		CacheVector(mySec, "secCache");
		CacheVector(myDow, "dowCache");

		Logger::ThrowBox("EXIT");

		myCandle = Stock::MergeBarID(_convergence, 1);
	}

	//---------------------------------------------------
	//                 Making Chart
	//---------------------------------------------------
	static Stock::Chart chart("GBPJPY", loader["GBPJPY"], 1);
}*/
