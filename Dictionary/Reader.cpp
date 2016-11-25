#include "Reader.h"

Reader::Reader(const std::string& inPath): _ifstream(inPath)
{
	this->_ifstream.open(inPath);
	if (!this->_ifstream.is_open())
		throw OpenError();
}

Reader::~Reader()
{
	this->_ifstream.close();
	if (this->_ifstream.is_open())
		throw CloseError();
}