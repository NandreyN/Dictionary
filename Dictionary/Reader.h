#pragma once
#include "FileOperator.h"
#include <fstream>

class OpenError{};
class CloseError{};

class Reader :
	public FileOperator
{
public:
	explicit Reader(const std::string &inPath);
	~Reader();
private:
	std::ifstream _ifstream;
};

