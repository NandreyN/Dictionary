#pragma once
#include "FileOperator.h"
#include <fstream>

class Writer :
	public FileOperator
{
public:
	explicit Writer(const std::string& outPath);
	~Writer();
	bool attachFileByLetter(char firstLetter);
	bool writeString(std::string toWrite);
private:
	std::ofstream _ofstream;
};
