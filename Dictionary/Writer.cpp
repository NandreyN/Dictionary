#include "Writer.h"
#include "DirectoryOperator.h"

Writer::Writer(const std::string& outPath) :_ofstream(outPath)
{
	this->_ofstream.open(outPath);
	if (!this->_ofstream.is_open())
		throw OpenError();
}

Writer::Writer() : _ofstream("")
{
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
	std::string path = DirectoryOperator::getWorkspaceDirName() + firstLetter; //+ ".txt";
	this->_ofstream.open(path, std::ios_base::app | std::ios_base::out);

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

bool Writer::close()
{
	try
	{
		this->_ofstream.close();
	}
	catch(...)
	{
		return false;
	}
	return true;
}