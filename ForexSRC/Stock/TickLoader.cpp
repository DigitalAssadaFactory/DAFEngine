#include "TickLoader.h"



using namespace DAF;

namespace Stock {

	void TickLoader::Load(const std::string & name, const std::string & path) {
		std::fstream fs;

		std::string fullpath;
		if (IsDebuggerPresent()) fullpath = "res/data/" + path;
		else fullpath = path;

		fs.open(fullpath, std::ios::in | std::ios::binary);

		if (fs.is_open())
		{
			std::streampos _startPos = fs.tellg();
			fs.seekg(0, std::ios::end);
			int _fileSize = fs.tellg() - _startPos;

			// m_data is std::map<std::string, std::vector<TickData>>
			//if (m_data.find(name) != m_data.end()) m_data[name].resize(0);
			//else m_data.emplace(name, std::vector<TickData>(0));

			if (m_data.find(name) == m_data.end()) m_data.emplace(name, std::vector<TickData>(0));

			const int _tickSize = sizeof(TickData);

			char _buffer[_tickSize];
			for (size_t i = 0; i < (_fileSize / _tickSize); ++i)
			{
				fs.seekg(i * _tickSize);
				fs.read(_buffer, _tickSize);
				m_data[name].push_back( *((TickData*)_buffer) );
			}

			fs.close();
			return;
			//return true;
		}
		//else return false;
	}

	void TickLoader::Load(std::vector<TickData>& destination, const std::string& path)
	{
		std::fstream fs;

		std::string fullpath;
		if (IsDebuggerPresent()) fullpath = "res/data/" + path;
		else fullpath = path;

		fs.open(fullpath, std::ios::in | std::ios::binary);

		if (fs.is_open())
		{
			std::streampos _startPos = fs.tellg();
			fs.seekg(0, std::ios::end);
			int _fileSize = fs.tellg() - _startPos;

			const int _tickSize = sizeof(TickData);

			char _buffer[_tickSize];
			std::vector<TickData> temp;
			for (size_t i = 0; i < (_fileSize / _tickSize); ++i)
			{
				fs.seekg(i * _tickSize);
				fs.read(_buffer, _tickSize);
				temp.push_back(*((TickData*)_buffer));
			}

			fs.close();
			static std::mutex __localMutex;
			//std::lock_guard<std::mutex> lock(__localMutex);
			__localMutex.lock();
			destination.resize(temp.size());
			destination = std::move(temp);
			__localMutex.unlock();
		}
	}

	void TickLoader::Set(const std::string& name, const std::vector<TickData>& data)
	{
		if (m_data.find(name) == m_data.end()) m_data.emplace(name, data);
	}

	void TickLoader::Reset(const std::string& name)
	{
		if (m_data.find(name) != m_data.end()) m_data[name].resize(0);
	}

	void TickLoader::Reverse(const std::string& name)
	{
		if (m_data[name].size() == 0) Logger::ThrowBox(name + " doesn't exist.");
		std::reverse( m_data[name].begin(), m_data[name].end());
	}

	std::vector<TickData>& TickLoader::operator[](const std::string& name)
	{
		if (m_data[name].size() == 0) Logger::ThrowBox(name + " doesn't exist.");
		return m_data.at(name);
	}

	std::string TickLoader::ShrinkExtension(std::string& name) {
		size_t lastdot = name.find_last_of(".");
		if (lastdot == std::string::npos) return name;
		return name.substr(0, lastdot);
	}

	std::vector<TickData> TickLoading(const std::string& path)
	{
		std::fstream fs;

		std::string fullpath;
		if (IsDebuggerPresent()) fullpath = "res/data/" + path;
		else fullpath = path;

		fs.open(fullpath, std::ios::in | std::ios::binary);

		std::vector<Stock::TickData> temp;
		if (fs.is_open())
		{
			std::streampos _startPos = fs.tellg();
			fs.seekg(0, std::ios::end);
			int _fileSize = fs.tellg() - _startPos;

			const int _tickSize = sizeof(Stock::TickData);

			int _elementCount = _fileSize / _tickSize;
			temp.reserve(_elementCount);
			char _buffer[_tickSize];
			for (size_t i = 0; i < _elementCount; ++i)
			{
				fs.seekg(i * _tickSize);
				fs.read(_buffer, _tickSize);
				temp.push_back(*((Stock::TickData*)_buffer));
			}

			fs.close();
		}
		//std::reverse(temp.begin(), temp.end());
		return temp;
	}

	/*void MyLoadTick(std::vector<TickData>& dest, const std::string& path)
	{
		std::fstream fs;

		std::string fullpath;
		if (IsDebuggerPresent()) fullpath = "res/data/" + path;
		else fullpath = path;

		fs.open(fullpath, std::ios::in | std::ios::binary);

		if (fs.is_open())
		{
			std::streampos _startPos = fs.tellg();
			fs.seekg(0, std::ios::end);
			int _fileSize = fs.tellg() - _startPos;

			const int _tickSize = sizeof(Stock::TickData);

			int _elementCount = _fileSize / _tickSize;
			dest.reserve(_elementCount);
			char _buffer[_tickSize];
			for (size_t i = 0; i < _elementCount; ++i)
			{
				fs.seekg(i * _tickSize);
				fs.read(_buffer, _tickSize);
				dest.push_back( *((Stock::TickData*)_buffer) );
			}

			fs.close();
		}
	}

	size_t FileSize(const std::string& path)
	{
		std::fstream fs;
		fs.open(path, std::ios::in | std::ios::binary);
		std::streampos _startPos = fs.tellg();
		fs.seekg(0, std::ios::end);
		return fs.tellg() - _startPos;
	}

	
	void MyLoadTick(std::vector<std::vector<TickData>>* container, const size_t at, const std::string& path)
	{
		std::fstream fs;

		std::string fullpath;
		if (IsDebuggerPresent()) fullpath = "res/data/" + path;
		else fullpath = path;

		fs.open(fullpath, std::ios::in | std::ios::binary);

		std::vector<Stock::TickData> temp;
		if (fs.is_open())
		{
			std::streampos _startPos = fs.tellg();
			fs.seekg(0, std::ios::end);
			int _fileSize = fs.tellg() - _startPos;

			const int _tickSize = sizeof(Stock::TickData);

			char _buffer[_tickSize];
			for (size_t i = 0; i < (_fileSize / _tickSize); ++i)
			{
				fs.seekg(i * _tickSize);
				fs.read(_buffer, _tickSize);
				temp.push_back(*((Stock::TickData*)_buffer));
			}

			fs.close();
		}
		
		static std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		(container + at) = std::move(temp);
	}
	*/
}