#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Logger.h"



using namespace DAF;

template<typename T>
std::vector<T> LoadVectorCache(const std::string& name)
{
	std::fstream _in;
	_in.open(name, std::ios::in | std::ios::binary);

	std::vector<T> temp;
	if (_in.is_open())
	{
		std::streampos _startPos = _in.tellg();
		_in.seekg(0, std::ios::end);
		int _fileSize = _in.tellg() - _startPos;

		const int _tickSize = sizeof(T);
		int _elementCount = _fileSize / _tickSize;

		temp.resize(_elementCount);
		_in.seekg(0);
		_in.read((char*)temp.data(), _fileSize);
		_in.close();
	}
	else Logger::Log("Failed to open file \"" + name + "\"");
	return temp;
}

template<typename T>
void CacheVector(const std::vector<T>& data, const std::string& name)
{
	std::fstream _out;
	_out.open(name, std::ios::out | std::ios::binary);

	_out.write((char*)data.data(), sizeof(T) * data.size());
	_out.close();
}
