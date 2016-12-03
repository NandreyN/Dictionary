#pragma once
#include "FileOperator.h"
#include <fstream>
#include <vector>
#include <ios>
#include <iostream>

class Writer :
	public FileOperator
{
public:
	explicit Writer(const std::string& outPath);
	explicit Writer();
	~Writer();
	bool attachFileByLetter(char firstLetter);
	bool writePair(std::vector < std::string > toWrite);
	bool close();
private:
	std::ofstream _ofstream;
};
