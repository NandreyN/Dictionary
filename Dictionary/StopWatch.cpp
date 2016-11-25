#include "StopWatch.h"
using namespace std;
using namespace chrono;

StopWatch::StopWatch() : _isFirstFixed(false), _isSecondFixed(false)
{

}

void StopWatch::fixFirst()
{
	if (!this->_isFirstFixed)
	{
		this->_isFirstFixed = true;
		this->_one = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}
	else
	{
		cerr << "First in still fixed" << endl;
	}
}

void StopWatch::fixSecond()
{
	if (!this->_isSecondFixed)
	{
		this->_isSecondFixed = true;
		this->_two = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	}
	else
	{
		cerr << "Second is still fixed" << endl;
	}
}

long StopWatch::getMilliseconds()
{
	this->_isSecondFixed = false;
	this->_isFirstFixed = false;
	auto result = this->_two - this->_one;
	return result.count();
}