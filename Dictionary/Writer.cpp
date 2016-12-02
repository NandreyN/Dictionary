#include "Writer.h"
#include "DirectoryOperator.h"

Writer::Writer(const std::string& outPath) :_ofstream(outPath)
{
	this->_ofstream.open(outPath);
	if (!this->_ofstream.is_open())
		throw OpenError();
}

Writer::~Writer()
{
	this->_ofstream.close();
	if (this->_ofstream.is_open())
		throw CloseError();
}

bool Writer::attachFileByLetter(char firstLetter)
{
	this->_ofstream.close();
	if (this->_ofstream.is_open())
		return false;

	this->_ofstream.clear();
	std::string path = DirectoryOperator::getWorkspaceDirName() + firstLetter + ".txt";
	this->_ofstream.open(path);
	if (this->_ofstream.is_open())
		return true;
	return false;
}

bool Writer::writePair(std::vector<std::string> toWrite)
{
	if (!this->_ofstream.is_open())
		return false;
	this->_ofstream << toWrite[0] << '\t' << toWrite[1] << std::endl;
	return true;
}