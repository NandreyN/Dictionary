#include "Shell.h"
#include <iostream>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//HANDLERS

struct AdHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "AdHandler" << endl;
		return false;
	}
	~AdHandler() {}
};

struct RmHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "RmHandler" << endl;
		return false;
	}
	~RmHandler() {}
};

struct SvHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "SvHandler" << endl;
		return false;
	}
	~SvHandler() {}
};

struct ExHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "ExHandler" << endl;
		return false;
	}
	~ExHandler() {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////

Shell::Shell()
{
	this->_handlers["ad"] = new AdHandler;
	this->_handlers["rm"] = new RmHandler;
	this->_handlers["sv"] = new SvHandler;
	this->_handlers["ex"] = new ExHandler;
}

Shell::~Shell()
{
	for (auto it = this->_handlers.begin(); it != this->_handlers.end(); ++it)
		delete it->second;
}

void Shell::Listen()
{
	string input;
	getline(cin, input);
	while (this->getCommandFromInputStr(input) != EX)
	{
		string command = this->getCommandFromInputStr(input);
		this->executeCommand(command);
		getline(cin, input);
	}
	// there need to close files
}

static inline std::string ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string trim(std::string &s) {
	return ltrim(rtrim(s));
}


std::string Shell::getCommandFromInputStr(const std::string& input) const
{
	if (input.length() < 2)
		return "";

	string inpCopy = input;
	inpCopy = trim(inpCopy);

	int i = 0;
	while (inpCopy[i] == ' ')
		i++;

	inpCopy = inpCopy.substr(i, 2);
	if (input[i + 2] == ' ' || input[i + 2] == '\0')
		return this->toLower(inpCopy);

	return "";
}

bool Shell::executeCommand(const std::string& command)
{
	auto iterator = this->_handlers.find(command);
	if (iterator == this->_handlers.end())
		return false;

	bool res = this->_handlers[command]->execute(vector<string>());
	return res;
}

std::string Shell::toLower(std::string str) const
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}