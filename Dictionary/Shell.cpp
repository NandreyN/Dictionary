#include "Shell.h"
#include <iostream>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include "DirectoryOperator.h"
#include <consoleapi.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//HANDLERS
// As for params:
// 1st parameter - key word
// 2nd - translation

struct AdHandler : public Handler
{
	bool execute(string line, Shell& obj) override
	{
		cout << "AdHandler" << endl;
		// Here I need to call parseTranslation
		auto data = obj.splitString(line);
		return obj.pushPairInCollection(data);
	}

	~AdHandler()
	{
	}
};

struct RmHandler : public Handler
{
	bool execute(string line, Shell& obj) override
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
	bool execute(string line, Shell& obj) override
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
	bool execute(string line, Shell& obj) override
	{
		cout << "ExHandler" << endl;
		obj.Stop();
		return false;
	}

	~ExHandler()
	{
	}
};

struct GtHandler : public Handler
{
	bool execute(string line, Shell& obj) override
	{
		cout << "GtHandler" << endl;
		return false;
	}

	~GtHandler()
	{
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

Shell::Shell() : _writer()
{
	this->_flag = true;
	this->_handlers[AD] = new AdHandler;
	this->_handlers[RM] = new RmHandler;
	this->_handlers[SV] = new SvHandler;
	this->_handlers[EX] = new ExHandler;
	this->_handlers[GT] = new GtHandler;
	this->checkFilesInWorkspace();
	setlocale(LC_CTYPE, "rus");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);
}

// trim from both ends
static inline std::string trim(std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

Shell::~Shell()
{
	for (auto it = this->_handlers.begin(); it != this->_handlers.end(); ++it)
		delete it->second;
	if (this->_queueToAdd.size() != 0)
		this->unloadQueue();
	this->_writer.close();
}

void Shell::Listen()
{
	string input;
	do
	{
		getline(cin, input);
		this->executeCommand(input);
		if (this->_queueToAdd.size() > 2)
			this->unloadQueue();

	} while (this->_flag);
}

void Shell::Stop()
{
	this->_flag = false;
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

	int i = 0, j = 0;
	while(i < line.length())
	{
		if (line[i] == ' ')
		{
			++i;
			continue;
		}
		while(line[i] != ' ' && i < line.length())
		{
			i++;
		}
		result.push_back(trim(line.substr(j,i - j)));
		j = i;
		i++;
	}
	return result;
}

bool Shell::pushPairInCollection(const std::vector<std::string>& pair)
{
	if (pair.size() != 2)
		return false;
	if (pair[0] == "" || pair[1] == "")
		return false;
	this->_queueToAdd[pair[0]] = pair[1];
	return true;
}

bool Shell::unloadQueue()
{
	//this->sortQueue();
	char filePrefix = 0;
	for (map<string, string> ::iterator iter = this->_queueToAdd.begin(); iter != this->_queueToAdd.end(); ++iter)
	{
		string key = iter->first;
		string value = iter->second;
		if (filePrefix != key[0])
		{
			filePrefix = key[0];
			this->_writer.close();
			this->_writer.attachFileByLetter(filePrefix);
		}
		vector<string> dataPass(0);
		dataPass.push_back(key);
		dataPass.push_back(value);
		this->_writer.writePair(dataPass);
	}
	this->_queueToAdd.clear();
	this->_writer.close();
	return true;
}

void Shell::sortQueue()
{
	//std::stable_sort(this->_queueToAdd.begin(), this->_queueToAdd.end());
}

bool Shell::checkFilesInWorkspace()
{
	// 65 - 90
	string path = DirectoryOperator::getWorkspaceDirName();
	DirectoryOperator dOperator;
	if (!dOperator.isExist(path))
	{
		dOperator.createFolder(path);
		for (char i = 'A'; i <= 'Z'; i++)
		{
			string fname = "22";
			fname[0] = i;
			fname[1] = '\0';
			dOperator.createFileInDir(path,fname);
		}
	}

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

	if (line.length() >= 2)
	{
		auto commandCopy = line;
		trim(commandCopy);

		commandCopy = commandCopy.substr(2, commandCopy.length() - 2);

		trim(commandCopy);

		res = this->_handlers[command]->execute(commandCopy, *this);
	}
	return res;
}

std::string Shell::toLower(std::string str) const
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
