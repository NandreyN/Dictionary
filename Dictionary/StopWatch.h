#pragma once
#include<iostream>
#include<chrono>

class StopWatch
{
public:
	explicit StopWatch();
	void fixFirst();
	void fixSecond();
	long getMilliseconds();
private:
	std::chrono::milliseconds _one, _two;
	bool _isFirstFixed, _isSecondFixed;
};

