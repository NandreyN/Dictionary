#pragma once
#include <string>
#include <map>
#include <vector>
#include "Writer.h"

#define AD "ad"
#define RM "rm"
#define SV "sv"
#define EX	"ex"
#define GT "gt"
#include <thread>

struct AdHandler;
class Shell;

struct Handler
{
	virtual bool execute(std::string line, Shell& obj) = 0;

	virtual ~Handler()
	{
	}
};

class Shell
{
public:
	explicit Shell();
	~Shell();
	void Listen();
	void Stop();
	static std::vector < std::string > splitString(const std::string& line);
	bool pushPairInCollection(const std::vector<std::string>& pair);

private:
	bool _flag;
	std::map<std::string, Handler*> _handlers;
	std::map < std::string, std::string, std::greater < std::string >> _queueToAdd; // pair key - translation
	Writer _writer;

	bool unloadQueue();
	void sortQueue();
	bool checkFilesInWorkspace();

	std::string getCommandFromInputStr(const std::string& input) const;
	bool executeCommand(const std::string& command);
	std::string toLower(std::string str) const;
};
