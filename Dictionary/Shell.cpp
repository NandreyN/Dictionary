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
// As for params:
// 1st parameter - key word
// 2nd - translation

struct AdHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "AdHandler" << endl;
		return false;
	}

	~AdHandler()
	{
	}
};

struct RmHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "RmHandler" << endl;
		return false;
	}

	~RmHandler()
	{
	}
};

struct SvHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "SvHandler" << endl;
		return false;
	}

	~SvHandler()
	{
	}
};

struct ExHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "ExHandler" << endl;
		return false;
	}

	~ExHandler()
	{
	}
};

struct GtHandler : public Handler
{
	bool execute(vector<string> params) override
	{
		cout << "GtHandler" << endl;
		return false;
	}

	~GtHandler()
	{
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

Shell::Shell()
{
	this->_handlers[AD] = new AdHandler;
	this->_handlers[RM] = new RmHandler;
	this->_handlers[SV] = new SvHandler;
	this->_handlers[EX] = new ExHandler;
	this->_handlers[GT] = new GtHandler;
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
		this->executeCommand(input);
		getline(cin, input);
	}
	// there need to close files
}


inline bool space(char c) {
	return std::isspace(c);
}

inline bool notspace(char c) {
	return !std::isspace(c);
}

std::vector<std::string> Shell::splitString(const std::string& line)
{
	vector<string> result;
	typedef std::string::const_iterator iter;

	iter i = line.begin();
	while(i != line.end())
	{
		i = std::find_if(i, line.end(), notspace);
		iter j = std::find_if(i, line.end(), space);
		if (i != line.end())
		{
			result.push_back(string(i, j));
			i = j;
		}
	}
	return result;
}

static inline std::string ltrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
	                                std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string rtrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(),
	                     std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string trim(std::string& s)
{
	auto trimmedRigth = rtrim(s);
	return ltrim(trimmedRigth);
}


bool Shell::parseTranslation(const std::string& input)
{
	string key = "", translation = "";
	auto collection = Shell::splitString(input);
	if (collection.size() != 2)
		return false;
	key = collection[0];
	translation = collection[1];
	this->_queueToAdd[key] = translation;
	return true;
}

string Shell::getCommandFromInputStr(const std::string& input) const
{
	if (input.length() < 2)
		return "";

	string inpCopy = input;
	inpCopy = trim(inpCopy);

	int i = 0;
	while (input[i] == ' ')
		++i;

	inpCopy = inpCopy.substr(0, 2);
	if (input[i + 2] == ' ' || input[i + 2] == '\0')
		return this->toLower(inpCopy);

	return "";
}

bool Shell::executeCommand(const std::string& line)
{
	string command = this->getCommandFromInputStr(line);

	auto iterator = this->_handlers.find(command);
	if (iterator == this->_handlers.end())
		return false;

	bool res = false;

	if(line.length() > 2) 
	{
		auto commandCopy = line;
		trim(commandCopy);

		commandCopy = commandCopy.substr(2, commandCopy.length() - 2);

		trim(commandCopy);

		this->parseTranslation(commandCopy); // additional checks are needed
		res = this->_handlers[command]->execute(vector<string>());
	}
	return res;
}

std::string Shell::toLower(std::string str) const
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
