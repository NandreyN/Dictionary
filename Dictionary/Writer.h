#pragma once
#include "FileOperator.h"
#include <fstream>
#include <vector>

class Writer :
	public FileOperator
{
public:
	explicit Writer(const std::string& outPath);
	explicit Writer();
	~Writer();
	bool attachFileByLetter(char firstLetter);
	bool writePair(std::vector < std::string > toWrite);
private:
	std::ofstream _ofstream;
};
